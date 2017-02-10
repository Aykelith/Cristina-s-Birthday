#ifndef XAL_STATE_MENUSTATE_HPP
#define XAL_STATE_MENUSTATE_HPP

#include <States/BaseState.hpp>

namespace sf { class RenderWindow; }
namespace XAL { class StateMachine; }

namespace XAL {
    namespace State {
        class MenuState: public BaseState {
        public:
            MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

        	void pause();
        	void resume();

        	void update(float dt);
        	void draw();

        private:

        };
    }
}

#endif // XAL_STATE_MENUSTATE_HPP
