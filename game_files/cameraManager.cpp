#include "cameraManager.hpp"
#include <stdexcept>
#include "../engine_library_dir/input.hpp"
#include "gameManager.hpp"

namespace game
{
    CameraManager *CameraManager::instance = nullptr;

    CameraManager::CameraManager()
    {
        if (instance == nullptr)
            instance = this;
        else
            throw std::logic_error("Instance already exists.");
    }

    CameraManager::~CameraManager()
    {
        if (instance == this)
            instance = nullptr;
    }

    void CameraManager::update(float deltaSeconds)
    {
        switchCamera();
        if (_currentCamera == &_debugCamera)
            moveCamera(deltaSeconds);
    }

    void CameraManager::updateAspectRatio(float aspect)
    {
        _currentCamera->aspectRatio(aspect);
    }

    void CameraManager::moveCamera(float deltaSeconds)
    {
        const float flying_speed = 2.0f;
        const float rotation_speed = 0.001f;

        auto cmm = _currentCamera->transform.modelMatrix();

        // move
        _currentCamera->transform.position += flying_speed * deltaSeconds *
                                              (math::Vec3)(cmm *
                                                           (math::Vec4)(math::Vec3::forward * engine::Input::keyPressed(GLFW_KEY_W) +
                                                                        math::Vec3::back * engine::Input::keyPressed(GLFW_KEY_S) +
                                                                        math::Vec3::right * engine::Input::keyPressed(GLFW_KEY_D) +
                                                                        math::Vec3::left * engine::Input::keyPressed(GLFW_KEY_A) +
                                                                        math::Vec3::up * engine::Input::keyPressed(GLFW_KEY_LEFT_SHIFT) +
                                                                        math::Vec3::down * engine::Input::keyPressed(GLFW_KEY_LEFT_CONTROL)));

        // rotate
        if (engine::Input::mousePressed(GLFW_MOUSE_BUTTON_MIDDLE))
        {
            auto d = engine::Input::mousePosDelta() * rotation_speed;
            auto local_x = math::Vec3(cmm.get(0, 0), cmm.get(1, 0), cmm.get(2, 0));
            _currentCamera->transform.rotation = math::Quaternion::fromAxisAngle(math::Vec3::up, d.x()) * math::Quaternion::fromAxisAngle(local_x, d.y()) * _currentCamera->transform.rotation;
            _currentCamera->transform.rotation.normalize();
        }
    }

    void CameraManager::switchCamera()
    {
        if (engine::Input::keyDown(GLFW_KEY_1))
        {
            // update aspect (it could change during the time, the camera was inactive)
            _perspectiveCamera.aspectRatio(_currentCamera->aspectRatio());
            _currentCamera = &_perspectiveCamera;
        }
        else if (engine::Input::keyDown(GLFW_KEY_2))
        {
            // update aspect (it could change during the time, the camera was inactive)
            _topDownCamera.aspectRatio(_currentCamera->aspectRatio());
            _currentCamera = &_topDownCamera;
        }
        else if (engine::Input::keyDown(GLFW_KEY_3) && GameManager::instance->debug())
        {
            // update aspect (it could change during the time, the camera was inactive)
            _debugCamera.aspectRatio(_currentCamera->aspectRatio());
            _currentCamera = &_debugCamera;
        }
    }
} // namespace game
