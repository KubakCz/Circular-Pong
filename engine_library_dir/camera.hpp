#pragma once

#include "transform.hpp"
#include "uniforms.hpp"

namespace engine
{
    class Camera
    {
    public:
        enum ProjectionType
        {
            perspective,
            orthographics
        };

    private:
        ProjectionType _type;
        float _near;
        float _far;
        float _fov;
        float _aspect;

        UBO<CameraData> ubo;

        // set projection matrix from above fields
        void SetProjectionMatrix();
        void SetPerspectiveProjectionMatrix();
        void SetOrthographicsProjectionMatrix();

    public:
        Transform transform;

        Camera() = delete;
        Camera(const Camera &c) = default;
        Camera(Camera &&c) = default;

        /// @brief Create new camera.
        /// @param type Type of the projection
        /// @param near Near plane distance
        /// @param far Far plane distance
        /// @param fov Field of view (radians) (perspective) / Height (orthographics)
        /// @param aspect Aspect ratio
        Camera(ProjectionType type, float near, float far, float fov, float aspect);

        /// @brief Create new camera.
        /// @param t Initial transform
        /// @param type Type of the projection
        /// @param near Near plane distance
        /// @param far Far plane distance
        /// @param fov Field of view (radians) (perspective) / Height (orthographics)
        /// @param aspect Aspect ratio
        Camera(Transform t, ProjectionType type, float near, float far, float fov, float aspect);

        Camera &operator=(const Camera &c) = default;

        void bindUBO();

#pragma region getters and setters
        /// @brief Get projection type
        ProjectionType projectionType() const { return _type; };
        /// @brief Set projection type
        void projectionType(ProjectionType type);

        /// @brief Get near plane distance
        float nearPlane() const { return _near; };
        /// @brief Set near plane distance
        void nearPlane(float near);

        /// @brief Get far plane distance
        float farPlane() const { return _far; };
        /// @brief Set far plane distance
        void farPlane(float far);

        /// @brief Get field of view (radians) (perspective) / height (orthographics)
        float fov() const { return _fov; };
        /// @brief Set field of view (radians) (perspective) / height (orthographics)
        void fov(float fov);

        /// @brief Get aspect ration
        float aspectRatio() const { return _aspect; };
        /// @brief Set aspect ration
        void aspectRatio(float aspect);

        /// @brief Set projection parameters.
        /// @param type Type of the projection
        /// @param near Near plane distance
        /// @param far Far plane distance
        /// @param fov Field of view (radians) (perspective) / Height (orthographics)
        /// @param aspect Aspect ratio
        void setProjection(ProjectionType type, float near, float far, float fov, float aspect);
#pragma endregion
    };
}