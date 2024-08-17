#include <raylib.h>
#include "stock.hpp"
#include "charts/chartclassic.hpp"

#define ResX 800
#define ResY 600

int main() {
    InitWindow(ResX,ResY,"Exchange");
    SetTargetFPS(60);

    Camera2D Camera = {
        (Vector2){static_cast<float>(ResX/2.f),static_cast<float>(ResY/2.f)},
        (Vector2){0,0},
        0,
        1
    };

    stock::StockData cd;
    stock::RandomStock(&cd, 10000,
            stock::DefaultExpiry,
            stock::DefaultRiskLessInterestRate,
            stock::DefaultDividentYeld,
            stock::DefaultVolatilityOfStock,
            GetRandomValue(0,10000) / 100.f);

    ChartClassic cc(&cd,&Camera);
    cc.PrintVars(true,true,true,true,true,true,true);
   

    Camera.target.y = (cd.Price.at(Camera.target.x / cc.ChartScaleX) * cc.ChartScaleY);

    while (!WindowShouldClose()) {
        cc.UpdateCamera(GetFrameTime());
        cc.Draw();
    }
    
    return 0;
}
