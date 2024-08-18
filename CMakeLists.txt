cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(exchange_project VERSION 1.0)

if(CMAKE_ARGV0 STREQUAL "win") 
    message("Building For Windows")
    add_compile_options(-Wall -Wextra -O2)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
    link_directories(win/lib)
    include_directories(win/include)
else()
    message("Building For Linux")
    add_compile_options(-Wall -Wextra -O2)
endif()

add_library(stock src/stock.cpp)
add_library(chartclassic src/charts/chartclassic.cpp)

add_executable(ex src/main.cpp)

set(libs
    stock
    chartclassic
)

if(CMAKE_ARGV0 STREQUAL "win")
    target_link_libraries(ex PRIVATE m raylib ${libs} -static -lopengl32 -lgdi32 -lwinmm -lgcc -lstdc++ -lwinpthread)
else()
    target_link_libraries(ex PRIVATE m raylib ${libs})
endif()
