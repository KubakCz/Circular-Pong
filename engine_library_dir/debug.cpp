#include "debug.hpp"

namespace engine
{
    std::unique_ptr<UBO<ModelData>> Debug::modelUBO = nullptr;
    std::unique_ptr<UBO<MaterialData>> Debug::colorUBO = nullptr;
    std::unique_ptr<Geometry> Debug::line_geometry = nullptr;

    void Debug::bindUBOs(math::Mat4 model, math::Vec4 col)
    {
        if (modelUBO == nullptr)
        {
            assert(colorUBO == nullptr);
            modelUBO = std::make_unique<UBO<ModelData>>(
                std::make_unique<ModelData>(
                    model));
            colorUBO = std::make_unique<UBO<MaterialData>>(
                std::make_unique<MaterialData>(col));
        }
        else
        {
            modelUBO->data->model = model;
            colorUBO->data->Color(col);
        }

        modelUBO->bind();
        colorUBO->bind();
    }

    const Geometry &Debug::get_line_geometry()
    {
        if (line_geometry == nullptr)
            line_geometry = std::make_unique<Geometry>(GL_LINES,
                                                       std::vector<Geometry::Vertex>{
                                                           Geometry::Vertex(math::Vec3::zero, math::Vec3::zero, math::Vec2::zero),
                                                           Geometry::Vertex(math::Vec3::right, math::Vec3::zero, math::Vec2::zero)},
                                                       std::vector<uint32_t>{0, 1});

        return *(line_geometry.get());
    }

    void Debug::drawLine(const math::Vec3 &a, const math::Vec3 &b, const math::Vec4 &col)
    {
        drawLine(a, b, col, Transform::defaultTransform);
    }

    void Debug::drawLine(const math::Vec3 &a, const math::Vec3 &b, const math::Vec4 &col, const Transform &t)
    {
        math::Vec3 v = b - a;
        float lineTransformData[16] = {
            v.x(), 0, 0, a.x(),
            v.y(), 1, 0, a.y(),
            v.z(), 0, 1, a.z(),
            0, 0, 0, 1};
        math::Mat4 lineTransform = math::Mat4(lineTransformData);

        bindUBOs(t.modelMatrix() * lineTransform, col);
        get_line_geometry().draw();
    }

    void Debug::drawAxis()
    {
        drawAxis(Transform::defaultTransform);
    }

    void Debug::drawAxis(const Transform &t)
    {
        drawLine(math::Vec3::zero, math::Vec3::right, math::Vec4(1, 0, 0, 1), t);
        drawLine(math::Vec3::zero, math::Vec3::up, math::Vec4(0, 1, 0, 1), t);
        drawLine(math::Vec3::zero, math::Vec3::forward, math::Vec4(0, 0, 1, 1), t);
    }

    void Debug::drawCross(const math::Vec3 &pos, float size, const math::Vec4 &col)
    {
        float size_2 = size / 2;
        drawLine(pos + math::Vec3::left * size_2, pos + math::Vec3::right * size_2, col);
        drawLine(pos + math::Vec3::down * size_2, pos + math::Vec3::up * size_2, col);
        drawLine(pos + math::Vec3::back * size_2, pos + math::Vec3::forward * size_2, col);
    }
}