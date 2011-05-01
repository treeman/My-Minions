#include "Tree/Log.hpp"
#include "Tree/Util.hpp"
#include "Tree/Butler.hpp"
#include "Tree/Tweaks.hpp"
#include "Game.hpp"
#include "GameController.hpp"

Game::Game()
{
    BUTLER->LoadSprites( "sprites.lua" );

    mouse = BUTLER->CreateSprite( "gfx/mouse.png" );

    world.reset( new World() );

    controller.reset( new GameController( world.get() ) );
    input_chain.AddHandler( controller.get() );
    controller->AddOrderHandler( world.get() );
}

bool Game::HandleEvent( sf::Event &e )
{
    if( e.Type == sf::Event::KeyPressed ) {
        switch( e.Key.Code ) {
            default:
                break;
        }
    }
    else if( e.Type == sf::Event::MouseMoved ) {
        Tree::Redraw();
    }
    return input_chain.HandleEvent( e );
}

void Game::Loaded()
{
    //Tree::DrawLazy();
    Tree::DrawNonLazy();
    Tree::SetMousePos(
        Tree::GetWindowWidth() / 2,
        Tree::GetWindowHeight() / 2
    );
}

void Game::Update( float dt )
{
    if( Tree::IsMouseValid() ) {
        Vec2f mpos = Tree::GetMousePos();
        mouse.SetPosition( mpos.x, mpos.y );
    }

    controller->Update( dt );
    world->Update( dt );
}

void Game::Draw()
{
    world->Draw();
    controller->Draw();

    if( Tree::IsMouseValid() ) {
        Tree::Draw( mouse );
    }
}

