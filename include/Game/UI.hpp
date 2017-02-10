#ifndef XAL_UI_HPP
#define XAL_UI_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

#include <string>

namespace XAL {
    class UI: public sf::Drawable {
    public:
        UI() = default;
        void load(const std::string& configurationFile, const sf::Vector2u& windowSize);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

    };
}

#endif // XAL_UI_HPP
