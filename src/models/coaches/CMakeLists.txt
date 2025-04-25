add_library(coaches STATIC coach.cpp coach.h)
target_include_directories(coaches PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(coaches displays)

add_executable(coach_tests coach_tests.cpp)
target_link_libraries(coach_tests coaches Catch2::Catch2WithMain)
catch_discover_tests(coach_tests)
