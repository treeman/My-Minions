#pragma once

#include <list>

#include "Hge/Hge.hpp"
#include "Tree/GameState.hpp"

namespace Tree 
{
	
	class Game {
	public:
		Game();
		~Game();
		
		//singleton
		static Game *Instance();
		static void Destroy();
		
		bool Logic();
		bool Render();
		
		void Init( int width, int height, bool fullscreen, std::string title, bool show_logo );
		void InitPostHge();
		
		void Pop();
		void Push( boost::shared_ptr<GameState> state );
		boost::shared_ptr<GameState> Top();
		
		void Exit();
		bool ShallExit() const;
	private:
		typedef std::list<boost::shared_ptr<GameState> > StateList;
		StateList state_list;
		
		bool exit_called;
		
		boost::shared_ptr<GameState> curr_state;
		
		HgeObj hge;
		
		static Game *game;
	};

}

Tree::Game Tree::Game::game = 0;
