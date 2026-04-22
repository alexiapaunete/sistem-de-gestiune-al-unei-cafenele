cmake_minimum_required(VERSION 3.16)
project(CafeneaApp CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings stricte
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

include_directories(include)

set(SOURCES
    src/Ingredient.cpp
    src/Reteta.cpp
    src/Produs.cpp
    src/Comanda.cpp
    src/Cafenea.cpp
    src/main.cpp
        src/Inventar.cpp
        include/Inventar.h
)

add_executable(cafenea ${SOURCES})
