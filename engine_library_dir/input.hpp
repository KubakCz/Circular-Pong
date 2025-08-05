#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>
#include <set>

#include "../math_library_dir/vector.hpp"

namespace engine
{
    class Input
    {
        /** Last position registered by onMouseMove. */
        static math::Vec2 _mouse_new_pos;
        /** Current mouse position. */
        static math::Vec2 _mouse_pos;
        /** Mouse position in the previous frame. */
        static math::Vec2 _mouse_prev_pos;
        /** Delta between mouse positions in the current and the previous frame. */
        static math::Vec2 _mouse_pos_delta;

        static std::set<int> _mouse_sets[5];
        static std::set<int> *_mouse_new_down;
        static std::set<int> *_mouse_down;
        static std::set<int> *_mouse_pressed;
        static std::set<int> *_mouse_new_up;
        static std::set<int> *_mouse_up;

        static std::set<int> _key_sets[5];
        static std::set<int> *_key_new_down;
        static std::set<int> *_key_down;
        static std::set<int> *_key_pressed;
        static std::set<int> *_key_new_up;
        static std::set<int> *_key_up;

    public:
        Input() = delete;

        // Methods for updating state - call these in corresponding application methods
        static void update();
        static void onMouseMove(double x, double y);
        static void onMouseButton(int button, int action, int mods);
        static void onKeyPressed(int key, int scancode, int action, int mods);

        /** Current mouse position. */
        static const math::Vec2 &mousePos() { return _mouse_pos; }
        /** Mouse position in the previous frame. */
        static const math::Vec2 &mousePrevPos() { return _mouse_prev_pos; }
        /** Delta between mouse positions in the current and the previous frame. */
        static const math::Vec2 &mousePosDelta() { return _mouse_pos_delta; }

        /** Returns true, if the mouse button 'button' started to be pressed down in this frame.*/
        static bool mouseDown(int button) { return _mouse_down->count(button); };
        /** Returns true, if the mouse button 'button' is pressed in this frame.*/
        static bool mousePressed(int button) { return _mouse_pressed->count(button); };
        /** Returns true, if the mouse button 'button' was realesed in this frame.*/
        static bool mouseUp(int button) { return _mouse_up->count(button); };

        /** Returns true, if the key 'key' started to be pressed down in this frame.*/
        static bool keyDown(int key) { return _key_down->count(key); };
        /** Returns true, if any key started to be pressed down in this frame.*/
        static bool keyDown() { return !_key_down->empty(); };
        /** Returns true, if the key 'key' is pressed in this frame.*/
        static bool keyPressed(int key) { return _key_pressed->count(key); };
        /** Returns true, if any key is pressed in this frame.*/
        static bool keyPressed() { return !_key_pressed->empty(); };
        /** Returns true, if the key 'key' was realesed in this frame.*/
        static bool keyUp(int key) { return _key_up->count(key); };
        /** Returns true, if any key was realesed in this frame.*/
        static bool keyUp() { return !_key_up->empty(); };
    };
} // namespace engine