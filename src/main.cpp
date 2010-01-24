#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "Tree/Game.hpp"
#include "Demo.hpp"

boost::scoped_ptr<Tree::Game> game;

bool frame_func()
{
	return game->Logic();
}

bool render_func()
{
	return game->Render();
}

int main( int argc, char *argv[] )
{	
	HgeObj hge;
		
	hge->System_SetState( HGE_FRAMEFUNC, frame_func );
	hge->System_SetState( HGE_RENDERFUNC, render_func );
	hge->System_SetState( HGE_WINDOWED, true );
	
	game.reset( new Tree::Game( 
		800, //width
		600, //height
		false, //fullscreen
		"7days test", //window title
		true, //show madeoftree logo
	) );
	
	if( hge->System_Initiate() )
	{
		game->Init();
		
		//push your gamestates here
		boost::shared_ptr<Tree::GameState> state( new Demo() );
		game->Push( state );
		
		hge->System_Start();
	}

	return 0;
}
