#pragma once

#include "Tree/GameState.hpp"
#include "Hge/Hge.hpp"

class Demo : public Tree::GameState {
public:
	Demo();
	
	bool HandleEvent( hgeInputEvent& );
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<hgeSprite> spr;
	TexObj tex;
};
