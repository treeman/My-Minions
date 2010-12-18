#pragma once

#include <list>
#include <boost/shared_ptr.hpp>

#include <SFML/Graphics.hpp>

#include "Tree/GameState.hpp"
#include "Tree/Singleton.hpp"
#include "Tree/WindowManager.hpp"
/*#include "Tree/SoundManager.hpp"*/
#include "Tree/Console.hpp"
#include "Tree/GameDebug.hpp"
#include "Tree/Settings.hpp"
#include "Tree/Butler.hpp"
#include "Tree/Tweaks.hpp"
#include "Tree/Loghelper.hpp"
#include "Tree/Vec2D.hpp"
#include "Tree/Debug.hpp"

#define GAME Tree::Game::Instance()

namespace Tree
{
    class Game : public Singleton<Game> {
    public:
        Game();
        ~Game();

        void Draw( const sf::Drawable &obj );

        float GetFPS();
        const sf::Input &GetInput();

        Vec2f GetMousePos() const;
        void SetMousePos( float x, float y );

        int GetWindowWidth() const;
        int GetWindowHeight() const;

        void Init( int width, int height, bool windowed, std::string title,
            std::string settings_file = "" );
        void Start();

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

        boost::shared_ptr<Tree::WindowManager> window_manager;
        /*boost::shared_ptr<Tree::SoundManager> sound_manager;*/

        boost::shared_ptr<Console> console;
        boost::shared_ptr<Tree::GameDebug> game_debug;

        boost::shared_ptr<sf::RenderWindow> window;

        boost::shared_ptr<Tree::InputChain> input_chain;

        void UpdateFPS( float dt );
        float fps;
        float fps_buff;
        int fps_frame_count;

        Vec2f mpos;

    //encapsulate them in Game instead of being their own Singleton
    public:
        boost::shared_ptr<Settings> GetSettings() const {
            return settings;
        }
        boost::shared_ptr<Tweaks> GetTweaks() const {
            return tweaks;
        }
        boost::shared_ptr<Butler> GetButler() const {
            return butler;
        }
        boost::shared_ptr<LogHelper> GetLogHelper() const {
            return log_helper;
        }
        boost::shared_ptr<Tree::Debug> GetVisualDebug() const {
            return visual_debug;
        }

    private:
        boost::shared_ptr<Settings> settings;
        boost::shared_ptr<Tweaks> tweaks;
        boost::shared_ptr<Butler> butler;
        boost::shared_ptr<LogHelper> log_helper;
        boost::shared_ptr<Tree::Debug> visual_debug;
    };
}

