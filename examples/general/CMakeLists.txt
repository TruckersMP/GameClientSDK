cmake_minimum_required(VERSION 3.21)
project(demo_plugin CXX)

add_library(demo_plugin SHARED src/Main.cxx)

target_compile_features(demo_plugin PRIVATE cxx_std_17)

# Points at the include/ folder of this repository by default; override
# TRUCKERSMP_SDK_INCLUDE_DIR if you moved the SDK or the example elsewhere.
set(TRUCKERSMP_SDK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../include" CACHE PATH "Path to the SDK include folder")

target_include_directories(demo_plugin PRIVATE "${TRUCKERSMP_SDK_INCLUDE_DIR}")
