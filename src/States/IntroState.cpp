#include <States/IntroState.hpp>

#include <Debug/Stream.hpp>
#include <StateMachine.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <States/MenuState.hpp>

namespace XAL {
    namespace State {
        IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
        : BaseState{ machine, window, replace }
        {
            xalDebug() << "IntroState(): next state";
            m_next = StateMachine::build<MenuState>(m_machine, m_window, true);
        }

        void IntroState::pause() {
            xalDebug() << "IntroState::pause";
        }

        void IntroState::resume() {
            xalDebug() << "IntroState::resume";
        }


        void IntroState::update(float dt) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    m_machine.quit();
                }
            }
        }

        void IntroState::draw() {
            m_window.clear();

        	m_window.display();
        }
    }
}
