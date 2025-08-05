#include "brickController.hpp"
#include "../game_data_files/materials.hpp"
#include "../game_data_files/environmentProperties.hpp"
#include <map>
#include <iostream>
#include <algorithm>
#include "../game_files/cameraManager.hpp"
#include "../game_files/gameManager.hpp"

namespace gameObjects
{
    BrickController::BrickController() : GameObjectBase()
    {
        reset();
    }

    void BrickController::reset()
    {
        bricks.clear();
        sortedBricks.clear();

        bricks.reserve(gameData::EnvironmentProperties::bricksInCircle);
        sortedBricks.reserve(gameData::EnvironmentProperties::bricksInCircle * gameData::EnvironmentProperties::bricksInStack);
        for (int c = 0; c < gameData::EnvironmentProperties::bricksInCircle; ++c)
        {
            bricks.emplace_back();
            bricks[c].reserve(gameData::EnvironmentProperties::bricksInStack);
            float orientation = c * 2 * (float)M_PI / gameData::EnvironmentProperties::bricksInCircle;
            for (int r = gameData::EnvironmentProperties::bricksInStack - 1; r >= 0; --r)
            {
                bricks[c].emplace_back(orientation, r, (c % 2 + r % 3) % 3 + 1);
                sortedBricks.push_back(&bricks[c].back());
            }
        }
    }

    void BrickController::update(float deltaTime)
    {
        for (auto itC = bricks.begin(); itC != bricks.end(); ++itC)
        {
            for (auto itR = itC->begin(); itR != itC->end(); ++itR)
            {
                itR->update(deltaTime);
            }
        }
    }

    void BrickController::sort()
    {
        auto distSq = [&](Brick *b)
        {
            // Bricks transform position is in the center -> real positino must be computed
            const math::Quaternion baseVector = math::Quaternion(0, math::Vec3::right * (gameData::EnvironmentProperties::brickInnerRadius + 0.5f * gameData::EnvironmentProperties::brickWidth));
            math::Vec3 brickPos = (b->transform.rotation * baseVector * b->transform.rotation.conjugated()).u() + b->transform.position;
            return (game::CameraManager::instance->currentCamera()->transform.position - brickPos).magSquared();
        };

        // Use insert sort - the order of bricks will stay the same for most of the time
        // The order might change:
        //  - camera moves (only debug camera) - the order stays nearly the same
        //  - bricks moves - the order will stay nearly the same
        //  - camera changes - no need to sort for top down camera
        // int swaps = 0;
        for (int i = 1; i < sortedBricks.size(); ++i)
        {
            int j = i;
            while (j > 0 && distSq(sortedBricks[j]) < distSq(sortedBricks[j - 1]))
            {
                std::swap(sortedBricks[j], sortedBricks[j - 1]);
                --j;
                // ++swaps;
            }
        }
        // if (swaps > 0)
        //     std::cout << "Swaps: " << swaps << std::endl;
    }

    void BrickController::render(bool bindMaterial)
    {
        render(true, bindMaterial);
    }

    void BrickController::render(bool sort, bool bindMaterial)
    {
        if (sort)
            this->sort();

        // Render from the most distant
        for (auto it = sortedBricks.rbegin(); it != sortedBricks.rend(); ++it)
        {
            (*it)->render(bindMaterial);
        }
    }

    const Brick *BrickController::getClosestBrick(math::Polar p) const
    {
        const Brick *b = nullptr;
        float minAngle = INFINITY;

        for (int col = 0; col < bricks.size(); ++col)
        {
            if (!bricks[col].empty())
            {
                float angle = math::Polar::angleDifference(p, bricks[col].back().getRealXZPosition());
                if (angle < minAngle)
                {
                    minAngle = angle;
                    b = &bricks[col].back();
                }
            }
        }

        return b;
    }

    void BrickController::breakBrick(Brick *brick)
    {
        // find brick
        int col = (int)std::round(brick->getRealXZPosition().a() / (2 * M_PI) * bricks.size());

        brick->decreaseLives();
        if (brick->lives() != 0) // the brick is not yet broken
            return;

        // add points for the brick
        game::GameManager::instance->increaseScore(brick->points());

        // erase brick
        bricks[col]
            .pop_back();
        sortedBricks.erase(std::remove(sortedBricks.begin(), sortedBricks.end(), brick), sortedBricks.end());

        // make other brick fall
        for (int i = 0; i < (int)bricks[col].size(); ++i)
        {
            int row = (int)bricks[col].size() - i - 1;
            float targetHeight = (row + 0.5f) * gameData::EnvironmentProperties::brickHeight;
            bricks[col][i].triggerFall(targetHeight);
        }

        // check win condition
        if (sortedBricks.size() == 0)
            reset();
    }
} // namespace gameObjects
