#include "Tree/Butler.hpp"
#include "Tree/Util.hpp"
#include "Tree/Log.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/VisualDebug.hpp"
#include "Tree/Util.hpp"
#include "Tree/Game.hpp"

#include "Intro.hpp"

Intro::Intro()
{

}

Intro::~Intro()
{

}

bool Intro::HandleEvent( sf::Event &e )
{
    if( e.Type == sf::Event::KeyPressed ) {
        switch( e.Key.Code ) {
            case sf::Key::F10:
                GAME->Exit();
                break;
            case sf::Key::Space:
            case sf::Key::Return:
            case sf::Key::Escape:
                GAME->Pop();
                break;
            default:
                break;
        }
    }
    return true;
}

void Intro::Loaded()
{
    Tree::DrawNonLazy();
}

void Intro::Update( float dt )
{
    narrative.Update( dt );
    if( narrative.IsDone() ) {
        GAME->Pop();
    }
}

void Intro::Draw()
{
    narrative.Draw();
}

