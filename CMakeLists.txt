cmake_minimum_required(VERSION 3.20)

project(ImageCarver VERSION 1.0 LANGUAGES CXX)

# C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =========================
# Output directories
# =========================

# Multi-config (Visual Studio)
foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${CONFIG} CONFIG_UPPER)

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER}
        ${CMAKE_SOURCE_DIR}/bin/${CONFIG})

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG_UPPER}
        ${CMAKE_SOURCE_DIR}/bin/${CONFIG})

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG_UPPER}
        ${CMAKE_SOURCE_DIR}/lib/${CONFIG})
endforeach()

# Single-config (macOS / Ninja / Make)
if(NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif()

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ImageCarver)

# =========================
# Subdirectories
# =========================

add_subdirectory(app)