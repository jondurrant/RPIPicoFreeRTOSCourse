# Add library cpp files
if (DEFINED (NOT TINY_JSON_PATH))
	SET(TINY_JSON_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/tiny-json" CACHE STRING "Lib")
endif ()
add_library(tiny_json INTERFACE)
target_sources(tiny_json INTERFACE
    ${TINY_JSON_PATH}/tiny-json.c
)

# Add include directory
target_include_directories(tiny_json INTERFACE ${TINY_JSON_PATH}/)

# Add the standard library to the build
target_link_libraries(tiny_json INTERFACE pico_stdlib)