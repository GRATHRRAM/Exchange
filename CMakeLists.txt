cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(exchange_project VERSION 1.0)

add_compile_options(-Wall -Wextra -O2)

add_library(stock src/stock.cpp)
add_library(chartclassic src/charts/chartclassic.cpp)

add_executable(ex src/main.cpp)

set(libs
    stock
    chartclassic
)

target_link_libraries(ex PRIVATE m raylib ${libs})
