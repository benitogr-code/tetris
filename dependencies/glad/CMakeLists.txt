set(GLAD_LIB glad)

add_library(${GLAD_LIB} STATIC "src/glad.c")

target_include_directories(${GLAD_LIB} PRIVATE PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
