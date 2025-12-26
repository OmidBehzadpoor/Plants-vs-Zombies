cmake_minimum_required(VERSION 3.11)

project(PlantsVsZombies C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Source files
# -----------------------------
set(SOURCES
        Source/PlantsVsZombies.c
        Source/menu.c
        Source/levelselect.c
)

# -----------------------------
# Executable
# -----------------------------
add_executable(PlantsVsZombies ${SOURCES})

# -----------------------------
# Include path
# -----------------------------
target_include_directories(PlantsVsZombies PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# -----------------------------
# Raylib
# -----------------------------
set(RAYLIB_VERSION 5.5)

find_package(raylib ${RAYLIB_VERSION} QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
    )

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(PlantsVsZombies PRIVATE raylib)

# -----------------------------
# Windows fix (MinGW + raylib)
# -----------------------------
if (WIN32)
    target_link_libraries(PlantsVsZombies PRIVATE winmm gdi32)
endif()
