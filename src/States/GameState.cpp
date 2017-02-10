#include <States/GameState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <StateMachine.hpp>

#include <JSONTools.hpp>

#include <Debug/Stream.hpp>

namespace XAL { namespace State {
    GameState::GameState(StateMachine& machine, sf::RenderWindow& window, int level, bool replace)
    : BaseState { machine, window, replace }
    {
        xalDebug() << "GameState(): init";
        std::string path = LEVEL_FOLDER + std::to_string(level) + LEVEL_EXTENSION;
        xalDebug() << "GameState(): map path:\"" << path << "\"";

        auto jsonObj = JSONTools::parseJSONFromFile(path);

        m_map.load(jsonObj["map"], window.getSize());
        m_player.load(jsonObj["player"]);
        m_ui.load(jsonObj["ui"], window.getSize());

        m_floorPosition = m_map.getFloorPosition();

        m_player.setPosition(PLAYER_NORMAL_OFFSET, m_floorPosition);

        m_map.setGameSpeed(m_gameSpeed);
    }

    void GameState::pause() {

    }

    void GameState::resume() {

    }

    void GameState::update(float dt) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_machine.quit();
            }
        }

        m_map.update(dt);
    }

    void GameState::draw() {
        m_window.clear();

        m_window.draw(m_map);
        m_window.draw(m_player);
        m_window.draw(m_ui);

        m_window.display();
    }
} }
