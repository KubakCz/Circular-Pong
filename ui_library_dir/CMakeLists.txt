
add_library(ui_library
        "transform.hpp"
        "transform.cpp"
        "element.hpp"
        "element.cpp"
        "digit.hpp"
        "digit.cpp"
        "rectangle.hpp"
        "rectangle.cpp"
        "number.hpp"
        "number.cpp"
    )

if(MSVC)
    target_compile_options(ui_library PUBLIC /std:c++20)
endif()

find_package(glad CONFIG REQUIRED)
target_link_libraries(ui_library PUBLIC glad::glad)
