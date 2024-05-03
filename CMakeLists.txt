cmake_minimum_required(VERSION 3.27)
project(SGD_Game)

set(CMAKE_CXX_STANDARD 23)


set(SDL2_INCLUDE_DIR "E:/C++_Libs/SDL2-2.30.1/include")
set(SDL2_LIB_DIR "E:/C++_Libs/SDL2-2.30.1/lib/x64")


include_directories(${SDL2_INCLUDE_DIR})
add_executable(SGD_Game main.cpp
        Window.cpp
        Window.h
        Player.cpp
        Player.h
        LevelLayout.cpp
        LevelLayout.h
        GameObject.cpp
        GameObject.h
        Tile.cpp
        Tile.h
        LevelDesign.cpp
        LevelDesign.h
        UI.cpp
        UI.h
        BoundingBox.cpp
        BoundingBox.h)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2main.lib )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2test.lib)


message("message: ${SDL2_LIB_DIR}/SDL2main.lib ")
