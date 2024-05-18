cmake_minimum_required(VERSION 3.27)
project(SGD_Game)

set(CMAKE_CXX_STANDARD 23)

set(FINAL_PATH "${CMAKE_BINARY_DIR}/LIBS")

set(SDL2_INCLUDE_DIR "${FINAL_PATH}/SDL2-2.30.1/include")
set(SDL2_LIB_DIR "${FINAL_PATH}/SDL2-2.30.1/lib/x64")
set(SDL2IMAGE_LIB_DIR "${FINAL_PATH}/SDL2_image")
set(AL "${FINAL_PATH}/openAL/openal-soft/include")

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2IMAGE_LIB_DIR})
include_directories(${AL})

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

file(COPY "${SDL2IMAGE_LIB_DIR}/lib/SDL2_image.dll" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "${FINAL_PATH}/openAL/openal-soft/build/Debug/OpenAL32.dll" DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2main.lib )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2.lib )
target_link_libraries(${PROJECT_NAME} ${SDL2_LIB_DIR}/SDL2test.lib)
target_link_libraries(${PROJECT_NAME} "${SDL2IMAGE_LIB_DIR}/lib/SDL2_image.dll")
target_link_libraries(${PROJECT_NAME} "${FINAL_PATH}/openAL/openal-soft/build/Debug/OpenAL32.dll")
target_link_libraries(${PROJECT_NAME} winmm.lib)

message(${CMAKE_BINARY_DIR})