cmake_minimum_required(VERSION 3.16)

project(PlantsVsZombies C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# macOS — حداقل نسخه سیستم‌عامل
if (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS version")
endif()

# -----------------------------
# پیدا کردن خودکار فایل‌های سورس و هدر
# -----------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "Source/*.c")
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "include/*.h")

# -----------------------------
# فایل ریسورس آیکون — فقط ویندوز
# -----------------------------
if (WIN32)
    set(RESOURCE_FILE "Data/resource.rc")
endif()

# -----------------------------
# Executable
# -----------------------------
add_executable(PlantsVsZombies ${SOURCES} ${HEADERS} ${RESOURCE_FILE})

# -----------------------------
# Include path
# -----------------------------
target_include_directories(PlantsVsZombies PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# -----------------------------
# Raylib — اگر نصب باشه استفاده می‌کنه، وگرنه خودکار دانلود می‌کنه
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
    set(BUILD_EXAMPLES      OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES         OFF CACHE BOOL "" FORCE)
    set(SUPPORT_GIF_RECORDING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(PlantsVsZombies PRIVATE raylib)

# -----------------------------
# تنظیمات هر سیستم‌عامل
# -----------------------------
if (WIN32)
    target_link_libraries(PlantsVsZombies PRIVATE
        winmm
        gdi32
        opengl32
    )
    # برای حذف پنجره CMD در حالت ریلیز، خط زیر را فعال کن:
    # set_target_properties(PlantsVsZombies PROPERTIES WIN32_EXECUTABLE TRUE)

elseif (APPLE)
    target_link_libraries(PlantsVsZombies PRIVATE
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
        "-framework CoreVideo"
        "-framework CoreFoundation"
    )

elseif (UNIX AND NOT APPLE)
    find_package(Threads REQUIRED)
    find_package(OpenGL REQUIRED)
    target_link_libraries(PlantsVsZombies PRIVATE
        OpenGL::GL
        Threads::Threads
        m
        dl
        rt
        X11
    )
endif()