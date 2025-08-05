#pragma once

#include <vector>
#include <functional>

namespace engine
{
    typedef std::function<float(const std::vector<float> &, float)> F_y_t;

    class ODE
    {
    public:
        ODE() = delete;

        /// @brief Compute physics step using euler forward method.
        /// @param y0 Initial values
        /// @param fyt Vector of derivative functions for values
        /// @param t0 Current time
        /// @param dt Time step
        /// @param y New values
        static void eulerForward(
            const std::vector<float> &y0,
            const std::vector<F_y_t> &fyt,
            float t0,
            float dt,
            std::vector<float> &y);

        /// @brief Compute physics step using euler forward method.
        /// @param y0 Initial values
        /// @param fyt Vector of derivative functions for values
        /// @param t0 Current time
        /// @param dt Time step
        /// @param y New values
        static void midpoint(
            const std::vector<float> &y0,
            const std::vector<F_y_t> &fyt,
            float t0,
            float dt,
            std::vector<float> &y);
    };
} // namespace engine
