#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include "exchange.hpp"
#include <time.h>
#include "startscreen/startscreen.hpp"

#define ResX 800
#define ResY 600

int main() {
    
    size_t seed;
    /*
    std::cout << "Type Seed (Numbers) || Type 0 if you want a random seed\nseed: ";
    std::cin >> seed;

    if(seed == 0) {srand(time(0)); seed = rand() % RAND_MAX;}
        
    */
    {
    StartScreen ss(ResX,ResY,&seed);
    ss.Run();
    }

    srand(seed);
    SetRandomSeed(seed);

    Exchange ex(ResX,ResY,1000, seed);
    
    ex.PrintVars(1,1,1,1,1,1);

    while (!WindowShouldClose()) {
        ex.Update();        
    } 
}
