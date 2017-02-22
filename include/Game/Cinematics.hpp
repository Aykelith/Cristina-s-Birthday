#ifndef XAL_CINEMATICS_HPP
#define XAL_CINEMATICS_HPP

#include <Global.hpp>

#include <sol2/sol.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>
#include <functional>

enum TaskType {
    DIALOG = 0,
    NONE
};

namespace XAL {
    class Cinematics: public sf::Drawable {
    public:
        Cinematics(const sf::Vector2u& windowSize);
        void setScript(const std::string& scriptPath);

        void update(float dt);

        void start();
        bool isTerminated() const { return m_terminated; }

        void setFont(const std::shared_ptr<sf::Font>& font);
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void lua_dialog(int textSize, const std::string& character, const std::string& text);

    private:
        static constexpr float DIALOG_MARGINS = 20.f;
        static constexpr float DIALOG_PADDING = 20.f;

        static constexpr float DIALOG_SPEED = 0.3f;

    private:
        bool m_terminated = false;

        std::shared_ptr<sf::Font> m_font;
        sf::Text m_text;

        std::vector< std::function<void()> > m_tasks;
        std::size_t m_currentTaskIndex;
        std::function<bool(float)> m_currentTaskUpdater;

        sf::Vector2u m_windowSize;
        sf::RectangleShape m_dialogBackground;

        sol::state m_lua;
        sol::load_result m_script;

        float m_dialogDt = 0.f;

        long m_actualTaskType = TaskType::NONE;
    };
}

#endif // XAL_CINEMATICS_HPP
