#ifndef XAL_STATE_GAMESTATE_HPP
#define XAL_STATE_GAMESTATE_HPP

#include <States/BaseState.hpp>

#include <Game/Player.hpp>
#include <Game/Map.hpp>
#include <Game/UI.hpp>

#include <SFML/Graphics/View.hpp>

namespace sf { class RenderWindow; }
namespace XAL { class StateMachine; }

namespace XAL {
    namespace State {
        class GameState: public BaseState {
        public:
            GameState(StateMachine& machine, sf::RenderWindow& window, int level, bool replace = true);

        	void pause();
        	void resume();

        	void update(float dt);
        	void draw();

        private:
            static constexpr auto LEVEL_FOLDER = "data/maps/";
            static constexpr auto LEVEL_EXTENSION = ".json";

            static constexpr float PLAYER_NORMAL_OFFSET = 100.f;

        private:
            Map m_map;
            Player m_player;
            UI m_ui;

            float m_floorPosition;
            float m_gameSpeed = 100.f;
        };
    }
}

#endif // XAL_STATE_GAMESTATE_HPP
