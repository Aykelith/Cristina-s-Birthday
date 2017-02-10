#include <States/MenuState.hpp>

#include <Debug/Stream.hpp>
#include <StateMachine.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <States/GameState.hpp>

namespace XAL {
    namespace State {
        MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
        : BaseState{ machine, window, replace }
        {
            xalDebug() << "MenuState(): next state";
            m_next = StateMachine::buildGame<GameState>(m_machine, m_window, 1, true);
        }

        void MenuState::pause() {
            xalDebug() << "MenuState::pause";
        }

        void MenuState::resume() {
            xalDebug() << "MenuState::resume";
        }


        void MenuState::update(float dt) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_machine.quit();
                }
            }
        }

        void MenuState::draw() {
            m_window.clear();

        	m_window.display();
        }
    }
}
