#include "ode.hpp"

#include <cassert>

namespace engine
{
    void ODE::eulerForward(
        const std::vector<float> &y0,
        const std::vector<F_y_t> &fyt,
        float t0,
        float dt,
        std::vector<float> &y)
    {
        assert(y0.size() == fyt.size());
        assert(fyt.size() == y.size());

        for (int i = 0; i < y0.size(); ++i)
        {
            y[i] = y0[i] + dt * fyt[i](y0, t0);
        }
    }

    void ODE::midpoint(
        const std::vector<float> &y0,
        const std::vector<F_y_t> &fyt,
        float t0,
        float dt,
        std::vector<float> &y)
    {
        assert(y0.size() == fyt.size());
        assert(fyt.size() == y.size());

        std::vector<float> y1(y0.size());
        for (int i = 0; i < y0.size(); ++i)
        {
            y1[i] = y0[i] + dt / 2 * fyt[i](y0, t0);
        }
        float t1 = t0 + dt / 2;

        for (int i = 0; i < y0.size(); ++i)
        {
            y[i] = y0[i] + dt * fyt[i](y1, t1);
        }
    }
} // namespace engine