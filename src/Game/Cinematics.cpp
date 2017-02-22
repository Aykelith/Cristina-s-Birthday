#include <Game/Cinematics.hpp>
#include <Debug/Stream.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace XAL {
    Cinematics::Cinematics(const sf::Vector2u& windowSize)
    : m_windowSize { windowSize }
    {
        m_lua.open_libraries(sol::lib::base, sol::lib::string, sol::lib::math);

        m_lua.set_function("dialog", &Cinematics::lua_dialog, this);

        m_dialogBackground.setSize({static_cast<float>(windowSize.x) - 2 * DIALOG_MARGINS, 0.f});
        m_dialogBackground.setFillColor(sf::Color::Blue);
    }

    void Cinematics::setScript(const std::string& scriptPath) {
        try {
            m_script = m_lua.load_file(scriptPath);
        } catch (const std::exception& e) {
            xalDebug() << "Error!" << e.what();
        }

        if (!m_script.valid()) {
            xalDebug() << "Script not good!";
        }
    }

    void Cinematics::update(float dt) {
        if (m_currentTaskUpdater(dt)) {
            if (m_currentTaskIndex < m_tasks.size()) {
                m_tasks[m_currentTaskIndex]();
                ++m_currentTaskIndex;
            } else {
                m_terminated = true;
            }
        }
    }

    void Cinematics::start() {
        m_script();
        m_tasks[0]();
        m_currentTaskIndex = 1;
    }

    void Cinematics::setFont(const std::shared_ptr<sf::Font>& font) {
        m_font = font;

        m_text.setFont(*font);
    }

    void Cinematics::lua_dialog(int textSize, const std::string& character, const std::string& text) {
        m_tasks.push_back([&](){
            xalDebug() << "Now dialog task";

            m_text.setCharacterSize(textSize);

            std::string string = character + ": " + text + "\nAm citit deja! ENTER!!";
            m_text.setString(string);
            m_dialogBackground.setSize({m_dialogBackground.getSize().x, m_text.getLocalBounds().height + 2 * DIALOG_PADDING});
            m_dialogBackground.setPosition(DIALOG_MARGINS, static_cast<float>(m_windowSize.y) - DIALOG_MARGINS - m_dialogBackground.getSize().y);

            m_dialogDt = 0.f;
            m_text.setString("");

            m_actualTaskType = TaskType::DIALOG;

            m_currentTaskUpdater = [=](float dt){
                m_dialogDt += dt;

                if (m_text.getString().getSize() == string.size()) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                        return true;
                    }
                } else if (m_dialogDt > DIALOG_SPEED) {
                    m_dialogDt = 0.f;
                    m_text.setString(string.substr(0, m_text.getString().getSize() + 1));
                    m_text.setOrigin(m_text.getLocalBounds().left, m_text.getLocalBounds().top);

                    auto backgroundPos = m_dialogBackground.getPosition();
                    m_text.setPosition(backgroundPos.x + DIALOG_PADDING, backgroundPos.y + DIALOG_PADDING);
                }

                return false;
            };
        });
    }

    void Cinematics::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (m_actualTaskType == TaskType::DIALOG) {
            target.draw(m_dialogBackground);
            target.draw(m_text);
        }
    }
}
