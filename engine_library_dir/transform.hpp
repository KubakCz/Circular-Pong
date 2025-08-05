#pragma once

#include "../math_library_dir/vector.hpp"
#include "../math_library_dir/quaternion.hpp"

namespace engine
{
    class Transform
    {
    public:
        math::Vec3 position;
        math::Quaternion rotation;
        math::Vec3 scale = math::Vec3(1, 1, 1);

        Transform() = default;
        Transform(const Transform &t) = default;
        Transform(Transform &&t) = default;

        Transform(math::Vec3 position, math::Quaternion rotation, math::Vec3 scale) : position(position),
                                                                                      rotation(rotation),
                                                                                      scale(scale){};

        Transform(math::Vec3 position, math::Quaternion rotation) : position(position),
                                                                    rotation(rotation){};

        Transform(math::Vec3 position) : position(position){};

        Transform &operator=(const Transform &t) = default;

        /// @brief Rotate the object, so it's pointing towards the point.
        // void lookAt(math::Vec3 point);

        /// @brief Compute model matrix based on position, rotation and scale.
        math::Mat4 modelMatrix() const;

        static const Transform defaultTransform;
    };
}
