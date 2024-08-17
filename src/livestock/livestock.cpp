#include "livestock.hpp"
#include <raylib.h>


LiveStock::LiveStock(stock::StockData *S, float c) {
    Stock = S;
    CoolDown = c;
    Sellers = GetRandomValue(0,100);
    Buyers = GetRandomValue(0,100);
}
