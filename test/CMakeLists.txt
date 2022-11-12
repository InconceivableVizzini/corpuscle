find_package(Check REQUIRED)

add_executable(corpuscle_test tests.c)
target_include_directories(corpuscle_test PUBLIC ../src)
target_link_libraries(corpuscle_test PUBLIC ${CHECK_LIBRARIES} pthread)
target_compile_options(corpuscle_test PUBLIC -O0)
