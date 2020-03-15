cmake_minimum_required(VERSION 3.12)

project(mrmap-converter LANGUAGES C)

add_executable(mrmap-converter "main.c")

set_target_properties(mrmap-converter PROPERTIES
	C_STANDARD 99
	C_STANDARD_REQUIRED ON
	C_EXTENSIONS OFF
)

include(GNUInstallDirs)

install(TARGETS mrmap-converter RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
