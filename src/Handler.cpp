#include <Handler.hpp>

#include <Debug/Stream.hpp>
#include <States/IntroState.hpp>

#include <SettingsTools.hpp>

namespace XAL {
    Handler::Handler() {
        m_window.setFramerateLimit(60);
    }

    void Handler::run() {
        // Create render window
    	XAL::SettingsTools::applyWindowSettings(m_window);

    	// Initialize the engine
    	m_machine.run(StateMachine::build<State::IntroState>(m_machine, m_window, true));

    	// Main loop
    	while(m_machine.running())
    	{
    		m_machine.nextState();
    		m_machine.update();
    		m_machine.draw();
    	}
    }
}
