#pragma once

#include <list>

#include "Hge/Hge.hpp"
#include "Tree/GameState.hpp"
#include "Tree/Singleton.hpp"

namespace Tree 
{
	class Game : public Singleton<Game> {
	public:
		Game();
		~Game();
		
		bool Logic();
		bool Render();
		
		void Init( int width, int height, bool windowed, std::string title, std::string settings_file = "" );
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
	};

}
