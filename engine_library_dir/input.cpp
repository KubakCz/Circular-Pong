#include "input.hpp"

#include <cassert>

namespace engine
{
    math::Vec2 Input::_mouse_new_pos = math::Vec2();
    math::Vec2 Input::_mouse_pos = math::Vec2();
    math::Vec2 Input::_mouse_prev_pos = math::Vec2();
    math::Vec2 Input::_mouse_pos_delta = math::Vec2();

    std::set<int> Input::_mouse_sets[5] = {};
    std::set<int> *Input::_mouse_new_down = &_mouse_sets[0];
    std::set<int> *Input::_mouse_down = &_mouse_sets[1];
    std::set<int> *Input::_mouse_pressed = &_mouse_sets[2];
    std::set<int> *Input::_mouse_new_up = &_mouse_sets[3];
    std::set<int> *Input::_mouse_up = &_mouse_sets[4];

    std::set<int> Input::_key_sets[5] = {};
    std::set<int> *Input::_key_new_down = &_key_sets[0];
    std::set<int> *Input::_key_down = &_key_sets[1];
    std::set<int> *Input::_key_pressed = &_key_sets[2];
    std::set<int> *Input::_key_new_up = &_key_sets[3];
    std::set<int> *Input::_key_up = &_key_sets[4];

    void Input::update()
    {
        // mouse pos
        _mouse_prev_pos = _mouse_pos;
        _mouse_pos = _mouse_new_pos;
        _mouse_pos_delta = _mouse_pos - _mouse_prev_pos;

        // mouse buttons
        std::swap(_mouse_down, _mouse_new_down);
        _mouse_new_down->clear();
        std::swap(_mouse_up, _mouse_new_up);
        _mouse_new_up->clear();
        for (auto it = _mouse_up->begin(); it != _mouse_up->end(); ++it)
            _mouse_pressed->erase(*it);
        _mouse_pressed->insert(_mouse_down->begin(), _mouse_down->end());

        // keys
        std::swap(_key_down, _key_new_down);
        _key_new_down->clear();
        std::swap(_key_up, _key_new_up);
        _key_new_up->clear();
        for (auto it = _key_up->begin(); it != _key_up->end(); ++it)
            _key_pressed->erase(*it);
        _key_pressed->insert(_key_down->begin(), _key_down->end());
    }

    void Input::onMouseMove(double x, double y)
    {
        _mouse_new_pos.x() = (float)x;
        _mouse_new_pos.y() = (float)y;
    }

    void Input::onMouseButton(int button, int action, int mods)
    {
        if (action == 1) // down
        {
            _mouse_new_down->insert(button);
        }
        else if (action == 0) // up
        {
            _mouse_new_up->insert(button);
        }
    }

    void Input::onKeyPressed(int key, int scancode, int action, int mods)
    {
        if (action == 1) // down
        {
            _key_new_down->insert(key);
        }
        else if (action == 0) // up
        {
            _key_new_up->insert(key);
        }
    }

} // namespace engine
