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

    stock::StockData stockdata;
    stock::RandomStock(&stockdata, 10000,
            stock::DefaultExpiry,
            stock::DefaultRiskLessInterestRate,
            stock::DefaultDividentYeld,
            stock::DefaultVolatilityOfStock,
            GetRandomValue(0,10000) / 100.f);

    ChartClassic chart(&stockdata, &Camera);
    chart.PrintVars(true,true,true,true,true,true,true);
   
    Camera.target.y = (stockdata.Price.at(stockdata.Price.size() - 1) * chart.ChartScaleY); 
    Camera.target.x = static_cast<float>(stockdata.Price.size() * chart.ChartScaleX);
    
    while (!WindowShouldClose()) {
        if(IsKeyPressed(KEY_N)) { //new chart
            stock::RandomStock(&stockdata, 10000,
                stock::DefaultExpiry,
                stock::DefaultRiskLessInterestRate,
                stock::DefaultDividentYeld,
                stock::DefaultVolatilityOfStock,
                GetRandomValue(0,10000) / 100.f);
                Camera.target.y = (stockdata.Price.at(stockdata.Price.size() - 1) * chart.ChartScaleY); 
                Camera.target.x = static_cast<float>(stockdata.Price.size() * chart.ChartScaleX);
        } 
        chart.UpdateCamera(GetFrameTime());
        chart.Draw();
    }
    
    return 0;
}
