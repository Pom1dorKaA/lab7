cmake_minimum_required(VERSION 3.10)
project(MyGameProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(npc_lib
    src/Squirrel.cpp
    src/Druid.cpp
    src/Werewolf.cpp
)
target_include_directories(npc_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_library(patterns_lib 
  src/NPC_Factory.cpp
  src/Game.cpp
)
target_include_directories(patterns_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(patterns_lib PUBLIC npc_lib)

add_executable(main src/main.cpp)
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(main patterns_lib npc_lib)

enable_testing()

add_executable(tests test/tests.cpp)
target_include_directories(tests PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests patterns_lib npc_lib gtest_main)

add_test(NAME MyProjectTests COMMAND tests)
