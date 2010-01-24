#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include "Tree/Game.hpp"
#include "Tree/Logo.hpp"
#include "Demo.hpp"

bool frame_func()
{
	return Tree::Game::Instance()->Logic();
}

bool render_func()
{
	return Tree::Game::Instance()->Render();
}

int main( int argc, char *argv[] )
{	
	try {
		HgeObj hge;
		
		//register basic hge functionality
		hge->System_SetState( HGE_FRAMEFUNC, frame_func );
		hge->System_SetState( HGE_RENDERFUNC, render_func );
		
		//important to set it to windowed to prevent flashing back n forth
		//if you want it windowed but it's fullscreen by default
		hge->System_SetState( HGE_WINDOWED, true );
		
		//create the game
		Tree::Game::Instance()->Init(
			800, //width
			600, //height
			false, //fullscreen
			"7days test" //window title
		);
		
		if( hge->System_Initiate() )
		{
			Tree::Game::Instance()->InitPostHge();
			
			//push your gamestates here
			boost::shared_ptr<Tree::GameState> state( new Demo() );
			Tree::Game::Instance()->Push( state );
			state.reset( new Tree::Logo() );
			Tree::Game::Instance()->Push( state );
			
			hge->System_Start();
		}
		
	}
	catch( std::exception &e )
	{
		
	}
	catch( ... )
	{
		
	}
	
	//destroy the game
	Tree::Game::Instance()->Destroy();

	return 0;
}
