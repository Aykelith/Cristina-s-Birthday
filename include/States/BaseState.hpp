#ifndef XAL_STATE_BASESTATE_HPP
#define XAL_STATE_BASESTATE_HPP

#include <Global.hpp>

#include <memory>

namespace sf { class RenderWindow; }
namespace XAL { class StateMachine; }

namespace XAL {
    namespace State {
        class BaseState {
        public:
            BaseState(XAL::StateMachine& machine, sf::RenderWindow& window, bool replace = true);
        	virtual ~BaseState() = default;

        	BaseState(const BaseState&) = delete;
        	BaseState& operator=(const BaseState&) = delete;

        	virtual void pause() = 0;
        	virtual void resume() = 0;

        	virtual void update(float dt) = 0;
        	virtual void draw() = 0;

        	std::unique_ptr<BaseState> next();

        	bool isReplacing();

        protected:
            XAL::StateMachine& m_machine;
            sf::RenderWindow& m_window;

        	bool m_replacing;

        	std::unique_ptr<BaseState> m_next;
        };
    }
}

#endif // XAL_STATE_BASESTATE_HPP
