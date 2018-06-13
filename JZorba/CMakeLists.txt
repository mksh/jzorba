cmake_minimum_required(VERSION 3.5.1)

project(JZORBA)

set(CMAKE_BUILD_TYPE Release)

find_package(JNI REQUIRED)
find_library(ZORBA_SIMPLESTORE NAMES libzorba_simplestore.so)

include_directories(${JNI_INCLUDE_DIRS} ${JZORBA_SOURCE_DIR}/include/)


set(CMAKE_CXX_FLAGS "-fPIC -g -shared -licuuc -licudata -licui18n -D_GLIBCXX_USE_CXX11_ABI=0")
set(SOURCE_FILES src/main/native/JZorba_utils.cpp src/main/native/JZorba_proxy.cpp src/main/native/JZorbaQuery.cpp src/main/native/JZorba.cpp)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${JZORBA_SOURCE_DIR}/target/classes)

add_library(JZORBA SHARED ${SOURCE_FILES})
set_target_properties(JZORBA PROPERTIES OUTPUT_NAME "jzorba")
# Link zorba store to jZorba
target_link_libraries(JZORBA "${ZORBA_SIMPLESTORE}")
