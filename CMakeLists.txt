cmake_minimum_required(VERSION 3.16)
project(cafenea CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(include)

set(SOURCES
        src/Ingredient.cpp
        src/Reteta.cpp
        src/Produs.cpp
        src/Bautura.cpp
        src/Desert.cpp
        src/Sandwich.cpp
        src/Comanda.cpp
        src/Inventar.cpp
        src/Cafenea.cpp
        src/main.cpp
)

add_executable(cafenea ${SOURCES})

include(cmake/CopyHelper.cmake OPTIONAL)
file(COPY assets/ DESTINATION ${CMAKE_BINARY_DIR}/assets)
