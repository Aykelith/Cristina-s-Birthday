#ifndef XAL_ANIMATION_HPP
#define XAL_ANIMATION_HPP

namespace XAL {
    struct Frame {
        float time;
        sf::IntRect rect;
    };

    struct Animation {
        std::vector<Frame> frames;

        sf::IntRect animate(float dt) {
            if (frames.size() == 1) return frames[0].rect;
        }
    };
}

#endif // XAL_ANIMATION_HPP
