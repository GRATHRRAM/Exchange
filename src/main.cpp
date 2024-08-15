#include <raylib.h>
#include "charts/chart.hpp"
#include "charts/chartclassic.hpp"

#define ResX 800
#define ResY 600

int main() {
    InitWindow(ResX,ResY,"Exchange");
    Camera2D Camera = {
        (Vector2){static_cast<float>(ResX/2.f),static_cast<float>(ResY/2.f)},
        (Vector2){0,0},
        0,
        1
    };

    chart::ChartData cd;
    chart::RandomChart(&cd, 100);

    ChartClassic cc(&cd,&Camera);
    cc.PrintVars(true,true,true,true,true,true,true);

    while (!WindowShouldClose()) {
        cc.UpdateCamera(GetFrameTime());
        cc.Draw();
    }
    
    return 0;
}
