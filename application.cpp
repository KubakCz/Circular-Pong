// ################################################################################
// Common Framework for Computer Graphics Courses at FI MUNI.
//
// Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
// All rights reserved.
// ################################################################################

#include "application.hpp"
#include "glad/glad.h"
#include <iostream>

#include "engine_library_dir/input.hpp"
#include "engine_library_dir/debug.hpp"
#include "math_library_dir/quaternion.hpp"
#include "game_data_files/environmentProperties.hpp"

// ----------------------------------------------------------------------------
// Constructors & Destructors
// ----------------------------------------------------------------------------

Application::Application(int initial_width, int initial_height, std::vector<std::string> arguments)
    : IApplication(initial_width, initial_height, arguments),
      shaderManager(lecture_folder_path / "data" / "shaders"),
      textureManager(lecture_folder_path / "data" / "textures",
                     {"ground.png",
                      "ballMask.png",
                      "pause.png",
                      "you_win.png",
                      "game_over.png"}),
      renderManager(width, height)
{
    cameraManager.updateAspectRatio((float)width / height);
}

Application::~Application()
{
}

// ----------------------------------------------------------------------------
// Update
// ----------------------------------------------------------------------------

void Application::update(float delta)
{
    float deltaSeconds = delta / 1000;
    time += deltaSeconds;
    engine::Input::update();

    cameraManager.update(deltaSeconds);
    gameManager.update(deltaSeconds);
}

// ----------------------------------------------------------------------------
// Render
// ----------------------------------------------------------------------------

void Application::render()
{
    renderManager.render();
}

void Application::render_ui()
{
    renderManager.renderUI();
}

// ----------------------------------------------------------------------------
// Input
// ----------------------------------------------------------------------------

void Application::on_resize(int width, int height)
{
    // Calls the default implementation to set the class variables.
    IApplication::on_resize(width, height);

    // Update fullscreen textures
    renderManager.resizeFullscreenTextures();

    // Update camera
    cameraManager.updateAspectRatio((float)width / height);
}

void Application::on_mouse_move(double x, double y)
{
    // std::cout << "Mouse x: " << x << " | y: " << y << "\n";
    engine::Input::onMouseMove(x, y);
}

void Application::on_mouse_button(int button, int action, int mods)
{
    // std::cout << "Mouse button: " << button << " | action: " << action << " | mods: " << mods << "\n";
    engine::Input::onMouseButton(button, action, mods);
}

void Application::on_key_pressed(int key, int scancode, int action, int mods)
{
    // std::cout << "Key pressed: " << key << " | scancode: " << scancode << " | action: " << action << " | mods: " << mods << "\n";
    engine::Input::onKeyPressed(key, scancode, action, mods);
}
