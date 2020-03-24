cmake_minimum_required(VERSION 3.10)

project(cppyy_example LANGUAGES CXX)


execute_process(COMMAND cling-config --cmake OUTPUT_VARIABLE CPPYY_MODULE_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
# Make sure this is set to something like:
# ~/.local/lib/python2.7/site-packages/cpyy_backend/cmake 
message("CPYY_MODULE_PATH: " ${CPPYY_MODULE_PATH})
list(INSERT CMAKE_MODULE_PATH 0 ${CPPYY_MODULE_PATH})

find_package(Cppyy)

set(SOURCES nearest_neighbors.cpp)
set(HEADERS nearest_neighbors.h)

# It seems like this library has to be shared...
add_library(knn_lib SHARED ${SOURCES})
# Note this is a necessary compile flag for cppyy bindings to work.
set_target_properties(knn_lib PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(knn_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

cppyy_add_bindings(
   "knn_example" "0.0.1" "Joel" "joel@joel.com"
   LANGUAGE_STANDARD "14"
   GENERATE_OPTIONS "-D__PIC__;-Wno-macro-redefined"
   INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
   LINK_LIBRARIES knn_lib
   H_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
   H_FILES ${HEADERS})

add_executable(knn main.cpp)
target_link_libraries(knn PUBLIC knn_lib)