#pragma once

#include "brick.hpp"
#include "../engine_library_dir/camera.hpp"
#include <vector>
#include <functional>

namespace gameObjects
{
    class BrickController : public engine::GameObjectBase
    {
        // bricks[column index][row index]
        // comlumn index - cw from angle 0
        // row index - highest brick has 0 index (bottom bricks are popped first => address of bricks stays the same even after pop)
        std::vector<std::vector<Brick>> bricks;

        // Vector of bricks sorted by distance to the camera.
        // Use sort() to update the order.
        std::vector<Brick *> sortedBricks;

        /** Sort bricks by distance to the camera for rendering purposes. Result is stored int sortedBricks vector. */
        void sort();

    public:
        BrickController();

        void update(float deltaTime) override;

        /** Sort bricks by distance to the camera and render them from the furthest to closest. */
        void render(bool bindMaterial = true) override;
        /** Render bricks. If sort is true, brick will be rendered from furthest to closest to the camera. */
        void render(bool sort, bool bindMaterial = true);

        /** Get pointer to the brick, that is on the ground and closest to the provided position.  */
        const Brick *getClosestBrick(math::Polar p) const;

        /** Break the brick. Expects, that the brick is on the ground. */
        void breakBrick(Brick *brick);

        /** Reset bricks. */
        void reset();
    };
} // namespace gameObjects
