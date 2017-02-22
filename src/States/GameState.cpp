#include <States/GameState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <StateMachine.hpp>

#include <JSONTools.hpp>

#include <Debug/Stream.hpp>

namespace XAL { namespace State {
    GameState::GameState(StateMachine& machine, sf::RenderWindow& window, int level, bool replace)
    : BaseState { machine, window, replace }
    , m_cinematics { window.getSize() }
    {
        xalDebug() << "GameState(): init";
        std::string path = LEVEL_FOLDER + std::to_string(level) + LEVEL_EXTENSION;
        xalDebug() << "GameState(): map path:\"" << path << "\"";

        m_font = std::make_shared<sf::Font>();
        m_font->loadFromFile("res/Comfortaa-Regular.ttf");
        m_cinematics.setFont(m_font);

        auto jsonObj = JSONTools::parseJSONFromFile(path);

        m_map.load(jsonObj["map"], window.getSize());
        m_player.load(jsonObj["player"]);
        m_ui.load(jsonObj["ui"], window.getSize());

        m_floorPosition = m_map.getFloorPosition();

        m_player.setFloorPosition(m_floorPosition);
        m_player.setPosition(PLAYER_NORMAL_OFFSET, m_floorPosition);

        m_map.setGameSpeed(m_gameSpeed);
        m_player.setGameSpeed(m_gameSpeed);

        m_map.setEnemiesUpdateFunction([&](const Enemy& enemy){
            if (m_player.isAttacking() && m_player.getHairPosition() >= enemy.position(false)) {
                return true;
            } else if (m_player.getPosition().x >= enemy.position(false)) {

            }

            return false;
        });

        std::string intro_cinematics = jsonObj["intro_cinematics"];
        if (!intro_cinematics.empty()) {
            m_cinematicsRunning = true;
            m_cinematics.setScript(intro_cinematics);
            m_cinematics.start();
        }
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

        if (m_cinematicsRunning) {
            m_cinematics.update(dt);

            if (m_cinematics.isTerminated()) {
                m_cinematicsRunning = false;
            }
        } else {
            m_map.update(dt);
            m_player.update(dt);
        }
    }

    void GameState::draw() {
        m_window.clear();

        m_window.draw(m_map);
        m_window.draw(m_player);
        m_window.draw(m_ui);

        if (m_cinematicsRunning) {
            m_window.draw(m_cinematics);
        }

        m_window.display();
    }
} }
