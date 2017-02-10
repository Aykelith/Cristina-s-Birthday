#ifndef XAL_RANDOMPROPGENERATOR_HPP
#define XAL_RANDOMPROPGENERATOR_HPP

#include <Global.hpp>

#include <random>

namespace XAL {
    class RandomPropGenerator {
    public:
        RandomPropGenerator() = default;

        void setSettings(uint distance, uint stackSize, uint propWidth) {
            m_distance = distance;
            m_stackSize = stackSize;
            m_propWidth = propWidth;
        }

        void setTotalDistance(uint distance) { m_totalDistance = distance; }

        void reset() {
            m_actualDistance = 0;
            m_stackCount = 1;
        }

        int generateNextPosition() {
            if (m_stackCount == m_stackSize) {
                m_actualDistance += m_distance;
                m_stackCount = 1;
            } else {
                m_actualDistance += m_propWidth;
            }

            if (m_actualDistance > m_totalDistance)
                return -1;

            ++m_stackCount;

            return (m_distribution(m_generator) > 50) ? m_actualDistance : 0;
        };
    private:
        uint m_distance;
        uint m_stackSize;
        uint m_propWidth;
        uint m_totalDistance;

        uint m_actualDistance = 0;

        uint m_stackCount = 0;

        std::random_device m_randomDevice;
        std::mt19937 m_generator = std::mt19937(m_randomDevice());
        std::uniform_int_distribution<> m_distribution = std::uniform_int_distribution<>(1, 100);
    };
}

#endif // XAL_RANDOMPROPGENERATOR_HPP
