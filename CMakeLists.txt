# CMakeLists.txt. Project file for graph algorithms based on S&W 4th ed.
cmake_minimum_required( VERSION 3.0 )
project( Graphs )

#########################################
# find Boost program_options library
set(Boost_USE_STATIC_LIBS     ON)
set(Boost_USE_MULTITHREADED  OFF) # multithreading is unneeded for prog options
set(Boost_USE_STATIC_RUNTIME OFF)

find_package( Boost 1.63.0 COMPONENTS program_options )

#########################################

# compiler config
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wpedantic -Wall -Werror" )

# add source subdirectory
add_subdirectory( "${PROJECT_SOURCE_DIR}/src" )
