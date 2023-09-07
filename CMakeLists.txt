cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(stats_headers   include/stats/character.hpp
                    include/stats/enemy.hpp 
                    include/stats/attributes.hpp 
                    include/stats/statistics.hpp 
                    include/stats/calculations.hpp
                    include/stats/combat.hpp
                    include/stats/save.hpp)
set(stats_sources   lib/character.cpp
                    lib/enemy.cpp
                    lib/calculations.cpp
                    lib/combat.cpp)
set(ui_headers  include/ui/scene.hpp)
set(ui_sources  lib/scene.cpp)
set(tools_headers include/tools/json_tools.hpp)
set(tools_sources lib/json_tools.cpp)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
find_package(Boost REQUIRED)

add_library(stats ${stats_headers} ${stats_sources})
add_library(ui ${ui_headers} ${ui_sources})
add_library(tools ${tools_headers} ${tools_sources})
set_target_properties(stats PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(stats PUBLIC include "/include")
set_target_properties(ui PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(ui PUBLIC include "/include")
set_target_properties(tools PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(tools PUBLIC include "/include")
install(TARGETS stats DESTINATION lib)
install(TARGETS ui DESTINATION lib)
install(TARGETS tools DESTINATION lib)
install(FILES ${stats_headers} DESTINATION include/stats)
install(FILES ${ui_headers} DESTINATION include/ui)
install(FILES ${tools_headers} DESTINATION include/tools)

add_executable(RPGBattle app/rpgbattle.cpp)
target_link_libraries(RPGBattle stats ui tools ${CURSES_LIBRARY} ${Boost_INCLUDE_DIRS})
install(TARGETS RPGBattle DESTINATION bin)
install(PROGRAMS demo DESTINATION bin)
