cmake_minimum_required(VERSION 3.10)
project(NetworkBypassSystem VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable warnings and treat warnings as errors
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Main application
add_executable(network_bypass_system
  src/main.cpp
  src/nic.cpp
  src/trading_system.cpp
)

# Test executable
add_executable(run_tests
  tests/test_main.cpp
  tests/test_lock_free_queue.cpp
  tests/test_trading_system.cpp
  src/nic.cpp
  src/trading_system.cpp
)

# Link against pthread for non-Windows systems
if(NOT WIN32)
  target_link_libraries(network_bypass_system pthread)
  target_link_libraries(run_tests pthread)
endif()

# Include directories
target_include_directories(network_bypass_system PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Enable testing
enable_testing()
add_test(NAME unit_tests COMMAND run_tests)