#include "Demo.hpp"

Demo::Demo()
{
	tex.Load( "gfx/dude.png" );
	spr.reset( new hgeSprite( tex, 0, 0, 800, 600 ) );
}

bool Demo::HandleEvent( hgeInputEvent& )
{
	
}

void Demo::Update( float dt )
{
	
}
void Demo::Render()
{
	spr->Render(0,0);
}
