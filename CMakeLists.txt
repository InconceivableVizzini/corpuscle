cmake_minimum_required(VERSION 3.18)

project(Corpuscle)

set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_compile_options(-Wall -Wextra -Werror -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition)

add_subdirectory(src)
add_subdirectory(test)


set(CMAKE_C_STANDARD 17)
