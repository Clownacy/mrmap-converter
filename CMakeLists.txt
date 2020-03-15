cmake_minimum_required(VERSION 3.12)

project(mrmap-converter LANGUAGES C)

add_executable(mrmap-converter "main.c")

include(GNUInstallDirs)

install(TARGETS mrmap-converter RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
