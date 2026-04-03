# 1. Collect app sources
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.inl
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# 2. Collect parent ext (header-only)
file(GLOB_RECURSE EXT_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/ext/*.h
    ${CMAKE_SOURCE_DIR}/ext/*.hpp
    ${CMAKE_SOURCE_DIR}/ext/*.inl
)

# 3. Create executable (include both)
add_executable(ImageCarver 
    ${APP_SOURCES}
    ${EXT_SOURCES}
)

# 4. Apply filters for app
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}
             PREFIX ""
             FILES ${APP_SOURCES})

# 5. Apply filters for ext (separate root)
source_group(TREE ${CMAKE_SOURCE_DIR}/ext
             PREFIX "ext"
             FILES ${EXT_SOURCES})

# 6. Include directories
target_include_directories(ImageCarver
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/ext
)

# 7. Platform-specific settings
if(WIN32)
    target_compile_definitions(ImageCarver PRIVATE PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(ImageCarver PRIVATE PLATFORM_MAC)
endif()