#include <raylib.h>
#include "charts/chart.hpp"
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

    chart::ChartData cd;
    chart::RandomChart(&cd, 10000,
            chart::DefaultExpiry,
            chart::DefaultRiskLessInterestRate,
            chart::DefaultDividentYeld,
            chart::DefaultVolatilityOfStock,
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
