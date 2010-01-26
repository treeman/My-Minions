#include "Demo.hpp"
#include "Tree/Game.hpp"

Demo::Demo() : fnt( new hgeFont( "fnt/arial10.fnt" ) )
{
	tex.Load( "gfx/dude.png" );
	spr.reset( new hgeSprite( tex, 0, 0, 800, 600 ) );
	
	t.Start();
	st.Start();
	
	bag.reset( new Tree::ShuffleBag<int>() );
	
	for( int i = 0; i < 20; i++ ) {
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
	groundBodyDef.position.Set( 10.0f, 500.0f );
	
	//use the world to create a body
	//note: does not need to be deleted, the world manages memory
	groundBody = world->CreateBody( &groundBodyDef );
	
	//definition for a basic polygon
	b2PolygonDef groundShapeDef;
	
	//transform into a box which will become 100x20 big
	groundShapeDef.SetAsBox( 50.0f, 10.0f );
	
	//copy the box defenition into our ground
	groundBody->CreateShape( &groundShapeDef );
	
	//create the dynamic body
	b2BodyDef bodyDef;
	bodyDef.position.Set( 10.0f, 100.0f );
	body = world->CreateBody( &bodyDef );
	
	//define the dynamic body
	b2PolygonDef shapeDef;
	shapeDef.SetAsBox( 4.0f, 4.0f );
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	body->CreateShape( &shapeDef );
	
	//note that you can set multiple shapes to a body
	body->SetMassFromShapes();
	
	///note: never heap allocate bodies, shapes or joints with box2D
	///always have b2World on heap
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
		}
	}
	
	return true;
}

void Demo::Update( float dt )
{
	//at least 60hz timestep
	float timeStep = 1.0f / 60.0f;
	
	//recommended is 10, lower means faster but less accurate
	int iterations  = 10;
	
	//update the simulation
	world->Step( timeStep, iterations );
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
	
	//render the ground
	b2Vec2 gpos = groundBody->GetPosition();
	hgeh::render_solid_rect( hge, gpos.x - 50, gpos.y - 10, gpos.x + 50, gpos.y + 10, 0xff64b2cf );
	
	//render the dynamic body
	b2Vec2 pos = body->GetPosition();
	hgeh::render_solid_rect( hge, pos.x, pos.y, pos.x + 4, pos.y + 4, 0xff9a1111 );
	
	//testing render help functions
	hgeh::render_rect( hge, 200, 40, 220, 60, 0xffffffff );
	hgeh::render_rect( hge, 241, 40, 260, 61, 0xffffffff );
	hgeh::render_rect( hge, 283, 40, 300, 60, 0xffffffff );
	hgeh::render_circle( hge, 150, 150, 30, 16, 0xff333333 );
	hgeh::render_solid_circle( hge, 150, 230, 30, 20, 0xff333333 );
	hgeh::render_circle_slice( hge, 300, 300, 20, 10, 0, math::PI_2, 0xffffffff );
	hgeh::render_solid_circle_slice( hge, 350, 300, 20, 10, 0, math::PI_2, 0xffffffff );
}

void Demo::ShuffleNext()
{
	latest = bag->Get();
	bagged = bag->GetBag();
	rest = bag->GetRest();
}
