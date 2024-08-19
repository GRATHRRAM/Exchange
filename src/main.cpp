#include <raylib.h>
#include "exchange.hpp"

int main() {
    Exchange ex(800,600,1000);
    
    while (!WindowShouldClose()) {
        ex.Update();        
    } 
}
