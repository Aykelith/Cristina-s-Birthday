#ifndef XAL_HANDLER_HPP
#define XAL_HANDLER_HPP

#include <Global.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <StateMachine.hpp>

namespace XAL {
    class Handler {
    public:
        Handler();

        void run();

    private:
        StateMachine m_machine;
	    sf::RenderWindow m_window;
    };
}

#endif // XAL_HANDLER_HPP
