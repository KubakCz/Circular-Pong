#include "transform.hpp"

namespace engine
{
    const Transform Transform::defaultTransform = Transform();

    math::Mat4 scaleMat(math::Vec3 scale)
    {
        float data[16] = {
            scale.x(), 0, 0, 0,
            0, scale.y(), 0, 0,
            0, 0, scale.z(), 0,
            0, 0, 0, 1};
        return math::Mat4(data);
    }

    math::Mat4 translateMat(math::Vec3 position)
    {
        float data[16] = {
            1, 0, 0, position.x(),
            0, 1, 0, position.y(),
            0, 0, 1, position.z(),
            0, 0, 0, 1};
        return math::Mat4(data);
    }

    math::Mat4 Transform::modelMatrix() const
    {
        return translateMat(position) * rotation.toRotMatrix() * scaleMat(scale);

        // // to be tested:
        // math::Mat4 m = rotation.toRotMatrix();

        // for (int i = 0; i < 3; ++i)
        // {
        //     m.get(i, 0) *= scale.x();
        //     m.get(i, 1) *= scale.y();
        //     m.get(i, 2) *= scale.z();
        //     m.get(i, 3) = m.get(3, 3) * position[i];
        // }

        // return m;
    }
}