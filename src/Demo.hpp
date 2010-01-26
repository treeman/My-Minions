#pragma once

#include "Hge/Hge.hpp"
#include "Tree/GameState.hpp"
#include "Tree/Timer.hpp"
#include "Tree/SpeedTimer.hpp"
#include "Tree/Shufflebag.hpp"

#include "Box2D/Box2D.h"

//this demo tests some things :)
class Demo : public Tree::GameState {
public:
	Demo();
	
	bool HandleEvent( hgeInputEvent& );
	
	void Update( float dt );
	void Render();
private:
	boost::shared_ptr<hgeSprite> spr;
	TexObj tex;
	
	Tree::Timer t;
	Tree::SpeedTimer st;
	
	boost::shared_ptr<hgeFont> fnt;
	
	//testing the shufflebag
	boost::shared_ptr<Tree::ShuffleBag<int> > bag;
	
	typedef Tree::ShuffleBag<int>::List Ints;
	Ints bagged;
	Ints rest;
	int latest;
	
	void ShuffleNext();
	
	boost::shared_ptr<b2World> world;
	
	//our static ground
	b2Body *groundBody;
	
	//a dynamic body
	b2Body *body;
	
	HgeObj hge;
};
