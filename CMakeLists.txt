cmake_minimum_required(VERSION 3.27)
project(SGD_Game)

set(CMAKE_CXX_STANDARD 23)


set(SDL2_INCLUDE_DIR "E:/C++_Libs/SDL2-2.30.1/include")
set(SDL2_LIB_DIR "E:/C++_Libs/SDL2-2.30.1/lib/x64")
set(SDL2IMAGE_LIB_DIR "E:/C++_Libs/SDL2_image")
set(SDL2MIXER_LIB_DIR "E:/C++_Libs/SDL2_mixer")


include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2IMAGE_LIB_DIR})
include_directories(${SDL2MIXER_LIB_DIR})

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
        BoundingBox.h
        FarBackground.cpp
        FarBackground.h
        NearBackground.cpp
        NearBackground.h
        Arrow.cpp
        Arrow.h
        Coin.cpp
        Coin.h
        ForeGround.cpp
        ForeGround.h
)

file(COPY "E:/C++_Libs/SDL2_image/lib/SDL2_image.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "E:/C++_Libs/SDL2_mixer/SDL2_mixer.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "E:/C++_Libs/SDL2_mixer/smpeg2.dll" DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2main.lib )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2test.lib)
target_link_libraries(${PROJECT_NAME} "E:/C++_Libs/SDL2_image/lib/SDL2_image.dll")
target_link_libraries(${PROJECT_NAME} "E:/C++_Libs/SDL2_mixer/SDL2_mixer.dll")
target_link_libraries(${PROJECT_NAME} "E:/C++_Libs/SDL2_mixer/smpeg2.dll")

