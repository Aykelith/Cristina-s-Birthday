#ifndef XAL_STATEMACHINE_HPP
#define XAL_STATEMACHINE_HPP

#include <Global.hpp>

#include <memory>
#include <stack>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <States/BaseState.hpp>

namespace sf { class RenderWindow; }

namespace XAL {
    class StateMachine {
    public:
        StateMachine();

        void run(std::unique_ptr<State::BaseState> state);

        void nextState();
    	void lastState();

    	void update();
    	void draw();

    	bool running() { return m_running; }
    	void quit() { m_running = false; }

    	template <typename T>
    	static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

        template <typename T>
    	static std::unique_ptr<T> buildGame(StateMachine& machine, sf::RenderWindow& window, int level, bool replace = true);

    private:
        std::stack<std::unique_ptr<State::BaseState>> m_states;

        bool m_resume;
	    bool m_running;

        sf::Clock mClock;
        sf::Time  mFrame;
        sf::Time  mTimePerFrame = sf::seconds(1.0f / 60.0f);
        sf::Time  mTimeSinceLastUpdate = sf::Time::Zero;
    };

    template <typename T>
    std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, bool replace) {
    	return std::unique_ptr<T>(new T(machine, window, replace));
    }

    template <typename T>
    std::unique_ptr<T> StateMachine::buildGame(StateMachine& machine, sf::RenderWindow& window, int level, bool replace) {
        return std::unique_ptr<T>(new T(machine, window, level, replace));
    }
}

#endif // XAL_STATEMACHINE_HPP
