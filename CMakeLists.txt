cmake_minimum_required (VERSION 3.2)
project(xlog)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/third_party/spdlog/include
)
link_libraries(
    pthread
)

add_library(xlog SHARED src/xlog.cc)


add_executable(xlogTest test/test.cc)
target_link_libraries(xlogTest xlog)

add_executable(nolog test/nolog.cc)
target_compile_definitions(nolog PRIVATE NO_LOG)
target_link_libraries(xlogTest xlog)