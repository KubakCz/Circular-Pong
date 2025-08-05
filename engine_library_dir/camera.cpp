#include "camera.hpp"

namespace engine
{
    Camera::Camera(ProjectionType type, float near, float far, float fov, float aspect) : Camera(
                                                                                              Transform(),
                                                                                              type,
                                                                                              near,
                                                                                              far,
                                                                                              fov,
                                                                                              aspect){};

    Camera::Camera(Transform t, ProjectionType type, float near, float far, float fov, float aspect) : transform(t),
                                                                                                       _type(type),
                                                                                                       _near(near),
                                                                                                       _far(far),
                                                                                                       _fov(fov),
                                                                                                       _aspect(aspect),
                                                                                                       ubo(GL_DYNAMIC_STORAGE_BIT){};

    void Camera::bindUBO()
    {
        SetProjectionMatrix();
        ubo.data->model = transform.modelMatrix();
        ubo.data->eyePosition = transform.position;

        ubo.bind();
    }

    void Camera::SetProjectionMatrix()
    {
        switch (_type)
        {
        case Camera::ProjectionType::perspective:
            SetPerspectiveProjectionMatrix();
            break;
        case Camera::ProjectionType::orthographics:
            SetOrthographicsProjectionMatrix();
            break;

        default:
            break;
        }
    }

    void Camera::SetPerspectiveProjectionMatrix()
    {
        float top = _near * std::tanf(_fov / 2);
        float bottom = -top;
        float right = top * _aspect;
        float left = -right;

        ubo.data->projection.get(0, 0) = 2 * _near / (right - left);
        ubo.data->projection.get(0, 2) = -(right + left) / (right - left);
        ubo.data->projection.get(1, 1) = 2 * _near / (top - bottom);
        ubo.data->projection.get(1, 2) = -(top + bottom) / (top - bottom);
        ubo.data->projection.get(2, 2) = (_far + _near) / (_far - _near);
        ubo.data->projection.get(2, 3) = -2 * _far * _near / (_far - _near);
        ubo.data->projection.get(3, 2) = 1;
    }

    void Camera::SetOrthographicsProjectionMatrix()
    {
        float top = _fov / 2;
        float bottom = -top;
        float right = top * _aspect;
        float left = -right;

        ubo.data->projection.get(0, 0) = 2 / (right - left);
        ubo.data->projection.get(1, 1) = 2 / (top - bottom);
        ubo.data->projection.get(2, 2) = 2 / (_far - _near);
        ubo.data->projection.get(3, 3) = 1;

        ubo.data->projection.get(0, 3) = -(right + left) / (right - left);
        ubo.data->projection.get(1, 3) = -(top + bottom) / (top - bottom);
        ubo.data->projection.get(2, 3) = -(_far + _near) / (_far - _near);
    }

#pragma region setters
    void Camera::projectionType(ProjectionType type)
    {
        _type = type;
        SetProjectionMatrix();
    }

    void Camera::nearPlane(float near)
    {
        _near = near;
        SetProjectionMatrix();
    }

    void Camera::farPlane(float far)
    {
        _far = far;
        SetProjectionMatrix();
    }

    void Camera::fov(float fov)
    {
        _fov = fov;
        SetProjectionMatrix();
    }

    void Camera::aspectRatio(float aspect)
    {
        _aspect = aspect;
        SetProjectionMatrix();
    }

    void Camera::setProjection(ProjectionType type, float near, float far, float fov, float aspect)
    {
        _type = type;
        _near = near;
        _far = far;
        _fov = fov;
        _aspect = aspect;
        SetProjectionMatrix();
    }
#pragma endregion
}