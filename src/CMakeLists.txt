add_executable(corp image-io.c main.c)
target_include_directories(corp PUBLIC "../../steed/include/" "../../surfaces/include/")
target_link_libraries(corp m)
