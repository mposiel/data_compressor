cmake_minimum_required(VERSION 3.25)
project(data_compressor C)

set(CMAKE_C_STANDARD 99)

add_executable(data_compressor main.c encoder.c encoder.h decoder.c decoder.h file_extension.c file_extension.h file_size.h file_size.c)
