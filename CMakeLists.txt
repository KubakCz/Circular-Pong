################################################################################
# Common Framework for Computer Graphics Courses at FI MUNI.
#
# Copyright (c) 2021-2022 Visitlab (https://visitlab.fi.muni.cz)
# All rights reserved.
#
# Course: PA199 (Project Template)
################################################################################

# Generates the lecture. DO NOT MODIFY THIS COMMAND:
visitlab_generate_lecture(PA199 project)

# Finds the external libraries and load their settings.
find_package(lodepng CONFIG REQUIRED)

target_sources(PA199_project
    # Here you can add more source files to the excutable of the game.
    PUBLIC 
    "game_data_files/environmentProperties.hpp"
    "game_data_files/environmentProperties.cpp"
    "game_data_files/geometryGenerator.hpp"
    "game_data_files/geometryGenerator.cpp"
    "game_data_files/geometries.hpp"
    "game_data_files/geometries.cpp"
    "game_data_files/materials.hpp"
    "game_data_files/materials.cpp"
    "game_objects/ball.hpp"
    "game_objects/ball.cpp"
    "game_objects/paddle.hpp"
    "game_objects/paddle.cpp"
    "game_objects/ground.hpp"
    "game_objects/ground.cpp"
    "game_objects/brick.hpp"
    "game_objects/brick.cpp"
    "game_objects/brickBase.hpp"
    "game_objects/brickBase.cpp"
    "game_objects/paddleController.hpp"
    "game_objects/paddleController.cpp"
    "game_objects/brickController.hpp"
    "game_objects/brickController.cpp"
    "game_objects/screenOrientedQuad.hpp"
    "game_objects/screenOrientedQuad.cpp"
    "game_ui/fullscreenText.hpp"
    "game_ui/fullscreenText.cpp"
    "game_ui/fullscreenTexts.hpp"
    "game_files/gameManager.hpp"
    "game_files/gameManager.cpp"
    "game_files/gameObjectManager.hpp"
    "game_files/gameObjectManager.cpp"
    "game_files/cameraManager.hpp"
    "game_files/cameraManager.cpp"
    "game_files/renderManager.hpp"
    "game_files/renderManager.cpp"
)

# Add sub-directories of your libraries
add_subdirectory("math_library_dir")
add_subdirectory("engine_library_dir")
add_subdirectory("ui_library_dir")

# Include your liblaries to linking of the project.
target_link_libraries(PA199_project
    PUBLIC 
        lodepng # This links the lodepng library. Do not remove.
        "math_library"
        "engine_library"
        "ui_library"
)

# Includes 'unit_tests' project to the build. DO NOT MODIFY THIS COMMAND:
add_subdirectory("test")  # Do not rename the directory name.

# Installing the application. Do not modify!
install(TARGETS PA199_project DESTINATION .)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glfw3.dll OPTIONAL DESTINATION .)
install(CODE [[file(WRITE ${CMAKE_INSTALL_PREFIX}/configuration.toml "framework_dir = \".\"\nlecture_dir = \".\"")]])
install(DIRECTORY ./data DESTINATION .)
