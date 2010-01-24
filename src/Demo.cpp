#include "Demo.hpp"
#include "Tree/Game.hpp"

Demo::Demo() : fnt( new hgeFont( "fnt/arial10.fnt" ) )
{
	tex.Load( "gfx/dude.png" );
	spr.reset( new hgeSprite( tex, 0, 0, 800, 600 ) );
	
	t.Start();
	st.Start();
	
	bag.reset( new Tree::ShuffleBag<int>() );
	
	for( int i = 0; i < 20; i++ ) {
		bag->Add( i );
	}
	ShuffleNext();
}

bool Demo::HandleEvent( hgeInputEvent &event )
{
	if( event.type == INPUT_KEYDOWN ) {
		switch( event.key ) {
			case HGEK_F4: Tree::Game::Instance()->Pop(); break;
			case HGEK_F10: Tree::Game::Instance()->Exit(); break;
			case HGEK_ENTER:
				t.Restart();
				st.Restart();
				break;
			case HGEK_SPACE:
				if( t.IsPaused() ) {
					t.Start();
				}
				else {
					t.Pause();
				}
				if( st.IsPaused() ) {
					st.Start();
				}
				else {
					st.Pause();
				}
				break;
			case HGEK_G:
				t.SetTime( 10.0 );
				st.SetTime( 10.0 );
				break;
			case HGEK_1:
				st.SetSpeed( 0.5 );
				break;
			case HGEK_2:
				st.SetSpeed( 1.0 );
				break;
			case HGEK_3:
				st.SetSpeed( 2.0 );
				break;
			case HGEK_S:
				ShuffleNext();
				break;
		}
	}
	
	return true;
}

void Demo::Update( float dt )
{
	
}
void Demo::Render()
{
	spr->Render(0,0);
	
	fnt->SetColor( 0xffffffff );
	fnt->printf( 100, 10, HGETEXT_LEFT, "t: %.2f\nst: %.2f s: %.2f", t.GetTime(), st.GetTime(), st.GetSpeed() );
	
	fnt->printf( 10, 30, HGETEXT_LEFT, "shuffle: %i", latest );
	
	int n = 1;
	const float h = fnt->GetHeight() + 2;
	for( Ints::iterator it = bagged.begin(); it != bagged.end(); ++it, ++n )
	{
		fnt->printf( 10, 30 + h * n, HGETEXT_LEFT, "%i", *it );
	}
	
	n = 1;
	for( Ints::iterator it = rest.begin(); it != rest.end(); ++it, ++n )
	{
		fnt->printf( 30, 30 + h * n, HGETEXT_LEFT, "%i", *it );
	}
}

void Demo::ShuffleNext()
{
	latest = bag->Get();
	bagged = bag->GetBag();
	rest = bag->GetRest();
}
