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

    ChartClassic chart(&cd, &Camera);
    chart.PrintVars(true,true,true,true,true,true,true);
   

    Camera.target.y = (cd.Price.at(Camera.target.x / chart.ChartScaleX) * chart.ChartScaleY);

    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_N)) { //new chart
            stock::RandomStock(&cd, 10000,
                stock::DefaultExpiry,
                stock::DefaultRiskLessInterestRate,
                stock::DefaultDividentYeld,
                stock::DefaultVolatilityOfStock,
                GetRandomValue(0,10000) / 100.f);
                Camera.target.y = (cd.Price.at(Camera.target.x / chart.ChartScaleX) * chart.ChartScaleY);
        } 
        chart.UpdateCamera(GetFrameTime());
        chart.Draw();
    }
    
    return 0;
}
