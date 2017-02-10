#include <States/BaseState.hpp>

namespace XAL {
    namespace State {
        BaseState::BaseState(StateMachine& machine, sf::RenderWindow &window, bool replace)
        : m_machine{ machine }
        , m_window{ window }
        , m_replacing{ replace }
        {

        }

        std::unique_ptr<BaseState> BaseState::next()
        {
        	return std::move(m_next);
        }

        bool BaseState::isReplacing()
        {
        	return m_replacing;
        }
    }
}
