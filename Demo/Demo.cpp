#include "Demo.hpp"
#include "Tree/Game.hpp"
#include "Tree/Log.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/Butler.hpp"
#include "Tree/Sprite.hpp"
#include "Tree/LogHelper.hpp"
#include "Box2D/Box2D.h"

#include <boost/foreach.hpp>

b2Vec2 vec[4];

Demo::Demo() : poly( vec, 4, b2Color( 1.0, 1.0, 1.0 ) )
{
    fnt = BUTLER->GetFont( "fnt/arial10.fnt" );
    TWEAKS->Load( "magic_numbers.lua" );

    LOGHELPER->SetLogKey( HGEK_L );

    poly.ps.clear();
    poly.ps.push_back( b2Vec2( 100, 100 ) );
    poly.ps.push_back( b2Vec2( 200, 100 ) );
    poly.ps.push_back( b2Vec2( 200, 200 ) );
    poly.ps.push_back( b2Vec2( 100, 200 ) );

    SETTINGS->Register<int>( "test", 4 );

    BUTLER->LoadSprites( "sprites.lua" );

    dude = BUTLER->GetSprite( "dude" );
    girl = BUTLER->GetSprite( "girl" );

    tex.Load( "gfx/dude.png" );
    spr.reset( new hgeSprite( tex, 0, 0, 800, 600 ) );

    t.Start();
    st.Start();

    bag.reset( new Tree::ShuffleBag<int>() );

    for( int i = 0; i < TWEAKS->GetDouble( "boxes" ); i++ ) {
        bag->Add( i );
    }
    ShuffleNext();

    //set bounding box
    b2AABB worldAABB;
    worldAABB.lowerBound.Set( 0.0f, 0.0f );
    worldAABB.upperBound.Set( 800.0f, 600.0f );

    b2Vec2 gravity( 0.0f, 10.0f );

    //set if bodies can sleep when they come to rest
    bool doSleep = true;

    world.reset( new b2World( worldAABB, gravity, doSleep ) );

    //define the ground body
    //it will be static by default (no mass) and statics do not
    //collide with other statics and they cannot move
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set( 400.0f, 600.0f );

    //use the world to create a body
    //note: does not need to be deleted, the world manages memory
    groundBody = world->CreateBody( &groundBodyDef );

    //definition for a basic polygon
    b2PolygonDef groundShapeDef;

    //transform into a box which will become 800x40 big
    groundShapeDef.SetAsBox( 400.0f, 20.0f );

    //copy the box defenition into our ground
    groundBody->CreateShape( &groundShapeDef );

    //create the dynamic body
    b2BodyDef bodyDef;
    for( int i = 0; i < TWEAKS->GetDouble( "boxes" ); ++i ) {
        float x = math::frandom( 400, 420 );
        float y = 40 + i * 5;
        bodyDef.position.Set( x, y );
        bodies.push_back( world->CreateBody( &bodyDef ) );
    }

    //define the dynamic body
    b2PolygonDef shapeDef;
    shapeDef.SetAsBox( 4.0f, 4.0f );
    shapeDef.density = 1.0f;
    shapeDef.friction = 0.3f;

    BOOST_FOREACH( b2Body *b, bodies ) {
        b->CreateShape( &shapeDef );
        //note that you can set multiple shapes to a body
        b->SetMassFromShapes();
    }

    ///note: never heap allocate bodies, shapes or joints with box2D
    ///always have b2World on heap

    //set flags for debug drawer
    uint32 flags = 0;
    flags += 1 * b2DebugDraw::e_shapeBit; //draw shapes
    flags += 1 * b2DebugDraw::e_jointBit; //draw joints
    flags += 1 * b2DebugDraw::e_coreShapeBit; //core shapes
    flags += 1 * b2DebugDraw::e_aabbBit; //aabbs
    flags += 1 * b2DebugDraw::e_obbBit; //obbs
    flags += 1 * b2DebugDraw::e_pairBit; //pairs
    flags += 1 * b2DebugDraw::e_centerOfMassBit; //coms

    debug_drawer.SetFlags( flags );

    world->SetDebugDraw( &debug_drawer );

    b2BodyDef dude_def;
    dude_def.position.Set( 200, 20 );
    dude_body = world->CreateBody( &dude_def );

    b2PolygonDef shape_def;
    shape_def.SetAsBox( 10, 10 );
    shape_def.density = 0.5;
    shape_def.friction = 0.3;
    dude_body->CreateShape( &shape_def );
    dude_body->SetMassFromShapes();
}

bool Demo::HandleEvent( hgeInputEvent &event )
{
    if( event.type == INPUT_KEYDOWN ) {
        switch( event.key ) {
            case HGEK_F4: Tree::Game::Instance()->Pop(); break;
            case HGEK_F10: Tree::Game::Instance()->Exit(); break;
            case HGEK_ENTER:
                t.Restart();
                st.Restart();
                break;
            case HGEK_SPACE:
                if( t.IsPaused() ) {
                    t.Start();
                }
                else {
                    t.Pause();
                }
                if( st.IsPaused() ) {
                    st.Start();
                }
                else {
                    st.Pause();
                }
                break;
            case HGEK_G:
                t.SetTime( 10.0 );
                st.SetTime( 10.0 );
                break;
            case HGEK_1:
                st.SetSpeed( 0.5 );
                break;
            case HGEK_2:
                st.SetSpeed( 1.0 );
                break;
            case HGEK_3:
                st.SetSpeed( 2.0 );
                break;
            case HGEK_S:
                ShuffleNext();
                break;
            case HGEK_RIGHT:
                dude_body->ApplyImpulse( b2Vec2( 1000, 0 ),
                    dude_body->GetWorldCenter() );
                break;
            case HGEK_LEFT:
                dude_body->ApplyImpulse( b2Vec2( -1000, 0 ),
                    dude_body->GetWorldCenter() );
                break;
            case HGEK_UP:
                dude_body->ApplyImpulse( b2Vec2( 0, -10000 ),
                    dude_body->GetWorldCenter() );
                break;
        }
    }

    return true;
}

void Demo::Update( float dt )
{
//  L_ << "begin update";
    //at least 60hz timestep
    float timeStep = 1.0f / 60.0f;

    //recommended is 10, lower means faster but less accurate
    int iterations  = 10;

    //update the simulation
    world->Step( timeStep, iterations );

//  L_ << "end update";

    girl->Update( dt );
    dude->Update( dt );
}
void Demo::Render()
{
    spr->Render(0,0);

    fnt->SetColor( 0xffffffff );
    fnt->printf( 100, 10, HGETEXT_LEFT, "t: %.2f\nst: %.2f s: %.2f", t.GetTime(), st.GetTime(), st.GetSpeed() );

    fnt->printf( 10, 30, HGETEXT_LEFT, "shuffle: %i", latest );

    int n = 1;
    const float h = fnt->GetHeight() + 2;
    for( Ints::iterator it = bagged.begin(); it != bagged.end(); ++it, ++n )
    {
        fnt->printf( 10, 30 + h * n, HGETEXT_LEFT, "%i", *it );
    }

    n = 1;
    for( Ints::iterator it = rest.begin(); it != rest.end(); ++it, ++n )
    {
        fnt->printf( 30, 30 + h * n, HGETEXT_LEFT, "%i", *it );
    }

    //testing render help functions
    hgeh::render_rect( hge, 200, 40, 220, 60, 0xffffffff );
    hgeh::render_rect( hge, 241, 40, 260, 61, 0xffffffff );
    hgeh::render_rect( hge, 283, 40, 300, 60, 0xffffffff );
    hgeh::render_circle( hge, 150, 150, 30, 16, 0xff333333 );
    hgeh::render_solid_circle( hge, 150, 230, 30, 20, 0xff333333 );
    hgeh::render_circle_slice( hge, 300, 300, 20, 10, 0, math::PI_2, 0xffffffff );
    hgeh::render_solid_circle_slice( hge, 350, 300, 20, 10, 0, math::PI_2, 0xffffffff );

    ////render the box2D bodies
    //b2Body *b = world->GetBodyList();
    //while( b ) {
    //    render_body( b );
    //    b = b->GetNext();
    //}

    debug_drawer.Render();

    girl->Render( 300, 100 );
    dude->Render( 200, 100 );

    poly.Render();

    Vec2D dude_pos = dude_body->GetPosition();
    float rot = dude_body->GetAngle();

    dude->RenderEx( dude_pos.x, dude_pos.y, rot );
}

void Demo::ShuffleNext()
{
    latest = bag->Get();
    bagged = bag->GetBag();
    rest = bag->GetRest();
}

