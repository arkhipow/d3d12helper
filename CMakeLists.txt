cmake_minimum_required(VERSION 4.3.4)

project(d3d12helper)

add_library(d3d12helper STATIC
    src/d3d12helper.cpp
)

target_link_libraries(d3d12helper PUBLIC
    dxgi.lib
    d3d12.lib
)