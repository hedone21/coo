cmake_minimum_required(VERSION 3.0)

# Project name
project(coo LANGUAGES C)

# Version info
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

configure_file(
	"config.h.in"
	"includes/coo_config.h"
	)

# Include directories
include_directories("includes")

# Library source files
# Default: Shared lib
add_library(coo SHARED src/class.c src/coo.c src/iter.c src/list.c)
# Static lib
# add_library(coo STATIC src/class.c src/coo.c src/iter.c src/list.c)

# Headert
set_target_properties(coo PROPERTIES PUBLIC_HEADER includes/coo.h)
target_include_directories(coo PRIVATE includes)

install (TARGETS coo LIBRARY DESTINATION /usr PUBLIC_HEADER DESTINATION /usr/include/coo)
