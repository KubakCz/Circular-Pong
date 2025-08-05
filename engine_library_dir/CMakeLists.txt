
add_library(engine_library
    "transform.hpp"
    "transform.cpp"
    "camera.hpp"
    "camera.cpp"
    "debug.hpp"
    "debug.cpp"
    "geometry.hpp"
    "geometry.cpp"
    "uniforms.hpp"
    "uniforms.cpp"
    "input.hpp"
    "input.cpp"
    "gameObjectBase.hpp"
    "gameObjectBase.cpp"
    "shaderManager.hpp"
    "shaderManager.cpp"
    "textureManager.hpp"
    "textureManager.cpp"
    "ssao.hpp"
    "ssao.cpp"
    "ode.hpp"
    "ode.cpp"
    "texture.hpp"
    "texture.cpp"
    )

if(MSVC)
    target_compile_options(engine_library PUBLIC /std:c++20)
endif()

find_package(glad CONFIG REQUIRED)
target_link_libraries(engine_library PUBLIC glad::glad)
