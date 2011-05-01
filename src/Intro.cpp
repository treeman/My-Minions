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
    return true;
}

void Intro::Loaded()
{
    Tree::DrawNonLazy();
    narrative.Start();
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

