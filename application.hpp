// ################################################################################
// Common Framework for Computer Graphics Courses at FI MUNI.
//
// Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
// All rights reserved.
// ################################################################################

#pragma once
#include "iapplication.h"
#include "glad/glad.h"

#include "engine_library_dir/uniforms.hpp"
#include "engine_library_dir/shaderManager.hpp"
#include "engine_library_dir/textureManager.hpp"
#include "engine_library_dir/ssao.hpp"
#include "game_data_files/geometries.hpp"
#include "game_data_files/materials.hpp"
#include "game_files/cameraManager.hpp"
#include "game_files/gameObjectManager.hpp"
#include "game_files/gameManager.hpp"
#include "game_files/renderManager.hpp"

class Application : public IApplication
{
  // ----------------------------------------------------------------------------
  // Variables
  // ----------------------------------------------------------------------------
private:
  // ----------------------------------------------------------------------------
  // Engine Variables
  // ----------------------------------------------------------------------------
  float time = 0;

  engine::ShaderManager shaderManager;
  engine::TextureManager textureManager;

  // ----------------------------------------------------------------------------
  // Game Variables
  // ----------------------------------------------------------------------------
  gameData::Geometries geometries;
  gameData::Materials materials;

  game::CameraManager cameraManager;
  game::GameObjectManager gameObjectManager;
  game::GameManager gameManager;
  game::RenderManager renderManager;

  // ----------------------------------------------------------------------------
  // Constructors & Destructors
  // ----------------------------------------------------------------------------
public:
  Application(int initial_width, int initial_height, std::vector<std::string> arguments = {});

  /** Destroys the {@link Application} and releases the allocated resources. */
  virtual ~Application();

  // ----------------------------------------------------------------------------
  // Methods
  // ----------------------------------------------------------------------------

  /** @copydoc IApplication::update */
  void update(float delta) override;

  /** @copydoc IApplication::render */
  void render() override;

  /** @copydoc IApplication::render_ui */
  void render_ui() override;

  /** @copydoc IApplication::on_resize */
  void on_resize(int width, int height) override;

  /** @copydoc IApplication::on_mouse_move */
  void on_mouse_move(double x, double y) override;

  /** @copydoc IApplication::on_mouse_button */
  void on_mouse_button(int button, int action, int mods) override;

  /** @copydoc IApplication::on_key_pressed */
  void on_key_pressed(int key, int scancode, int action, int mods) override;
};
