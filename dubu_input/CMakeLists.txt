set(target_name "dubu_input")

set(src_precompiled
    "src/dubu_input/precompiled.h")

set(src_input
    "src/dubu_input/input/Input.cpp"
    "src/dubu_input/input/Input.h")

set(src_dubu_input
    "src/dubu_input/dubu_input.h")

set(src_files
    ${src_precompiled}
    ${src_input}
    ${src_dubu_input})

# Project
add_library(${target_name} STATIC ${src_files})
set_target_properties(${target_name} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${target_name}
    compiler_features
    compiler_warnings
    dubu_window)

target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_precompile_headers(${target_name} PUBLIC ${src_precompiled})

source_group("src" FILES ${src_dubu_input})
source_group("src/input" FILES ${src_input})
source_group("src/precompiled" FILES ${src_precompiled})
source_group("src/precompiled" REGULAR_EXPRESSION "cmake_pch\.[ch]xx")

set_target_properties(${target_name} PROPERTIES FOLDER ${${PROJECT_NAME}_FOLDER})
