#pragma once

#include "../engine_library_dir/camera.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

namespace game
{
    class CameraManager
    {
#pragma region camera instances
        engine::Camera _perspectiveCamera = engine::Camera(
            engine::Transform(
                math::Vec3(0, 8, -8),
                math::Quaternion::fromEulerAngles((float)M_PI / 4, 0, 0)),
            engine::Camera::ProjectionType::perspective,
            0.1f,
            100.0f,
            (float)M_PI / 3,
            1);

        engine::Camera _topDownCamera = engine::Camera(
            engine::Transform(
                math::Vec3(0, 10, 0),
                math::Quaternion::fromEulerAngles((float)M_PI / 2, 0, 0)),
            engine::Camera::ProjectionType::orthographics,
            0.1f,
            100.0f,
            14,
            1);

        engine::Camera _debugCamera = engine::Camera(
            engine::Transform(
                math::Vec3(0, -5, -10),
                math::Quaternion::fromEulerAngles((float)M_PI / 8, 0, 0)),
            engine::Camera::ProjectionType::perspective,
            0.01f, 100,
            (float)(M_PI / 3),
            1);
#pragma endregion camera instances

        engine::Camera *_currentCamera = &_perspectiveCamera;

        void moveCamera(float deltaSeconds);
        void switchCamera();

    public:
        static CameraManager *instance;

        CameraManager();
        CameraManager(const CameraManager &cm) = delete;
        CameraManager(CameraManager &&cm) = delete;
        ~CameraManager();

        engine::Camera *currentCamera() const { return _currentCamera; }

        void update(float deltaSeconds);
        void bindCamera() const { _currentCamera->bindUBO(); };
        void updateAspectRatio(float aspect);

        bool currentCameraIsTopDown() const { return _currentCamera == &_topDownCamera; }
    };
} // namespace game
