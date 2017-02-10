#ifndef XAL_DEBUG_STREAM_HPP
#define XAL_DEBUG_STREAM_HPP

#include <iostream>
#include <sstream>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace XAL {
    namespace Debug {
        class Stream {
        public:
            static inline Stream debug() {
                return Stream();
            }

            inline Stream(): m_ss { new std::ostringstream } { }
            inline ~Stream() {
                std::cout << m_ss->str() << "\n";
                delete m_ss;
            }

            inline Stream &operator<<(bool t) { (*m_ss) << (t ? "true" : "false") << " "; return *this; }

            template <typename T>
            inline Stream &operator<<(const sf::Vector2<T>& v) { (*m_ss) << "{" << v.x << ", " << v.y << "} "; return *this; }

            template <typename T>
            inline Stream &operator<<(const sf::Rect<T>& r) { (*m_ss) << "{" << r.left << ", " << r.top << ", " << r.width << ", " << r.height << "} "; return *this; }

            template <typename T>
            inline Stream &operator<<(T t) { (*m_ss) << t << " "; return *this; }

        private:
            std::ostringstream *m_ss;
        };
    }
}

#ifdef XAL_DEBUG
    #define xalDebug XAL::Debug::Stream::debug
#else

#endif

#endif // XAL_DEBUG_STREAM_HPP
