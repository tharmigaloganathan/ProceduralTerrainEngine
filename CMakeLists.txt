cmake_minimum_required(VERSION 4.2)
project(ProceduralTerrainEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 3.3 REQUIRED)

add_executable(ProceduralTerrainEngine
        external/glad/src/gl.c

        src/main.cpp
        src/app/WorldExplorerApp.cpp
        src/app/WorldExplorerApp.h
        src/platform/Window.cpp
        src/platform/Window.h
        src/render/Renderer.cpp
        src/render/Renderer.h
        src/render/Shader.cpp
        src/render/Shader.h
        src/render/Mesh.cpp
        src/render/Mesh.h)

target_include_directories(ProceduralTerrainEngine PRIVATE
        src
        external/glad/include)

target_link_libraries(ProceduralTerrainEngine PRIVATE
        glfw)

add_custom_command(TARGET ProceduralTerrainEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:ProceduralTerrainEngine>/assets
)