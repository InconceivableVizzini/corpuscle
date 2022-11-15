add_executable(corp image-io.c main.c)

set_property(TARGET corp PROPERTY C_STANDARD 17)

target_link_libraries(corp m)
