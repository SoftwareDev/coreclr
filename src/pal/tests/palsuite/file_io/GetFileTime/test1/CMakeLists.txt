cmake_minimum_required(VERSION 2.8.12.2)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SOURCES
  GetFileTime.c
)

add_executable(paltest_getfiletime_test1
  ${SOURCES}
)

add_dependencies(paltest_getfiletime_test1 CoreClrPal)

target_link_libraries(paltest_getfiletime_test1
  pthread
  m
  CoreClrPal
)
