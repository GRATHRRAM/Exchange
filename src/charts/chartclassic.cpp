#include "chartclassic.hpp"
#include <cmath>
#include <cstdint>
#include <raylib.h>
#include <raymath.h>
#include <vector>

ChartClassic::ChartClassic(std::vector<double> *_Price, Camera2D *_Camera) {
    Price = _Price;
    Camera    = _Camera;
    CameraSpeed = 100;
    ChartScaleX = 15;
    ChartScaleY = -2500;
    ChartThick  = 5;
    CameraTarget = Camera->target;
}

void ChartClassic::Draw(Color Up, Color Down) {
    uint64_t charts = Price->size();

    for(uint64_t i = 0; i < charts; ++i) {
        if(i+1 >= charts) break;
        if(Price->at(i) >= Price->at(i+1)) {
            DrawLineEx((Vector2){static_cast<float>(i)*ChartScaleX,static_cast<float>(Price->at(i)*ChartScaleY)},
                    (Vector2){static_cast<float>((i+1)*ChartScaleX),static_cast<float>(Price->at(i+1)*ChartScaleY)},
                    ChartThick,Down);
        } else {
            DrawLineEx((Vector2){static_cast<float>(i)*ChartScaleX,static_cast<float>(Price->at(i)*ChartScaleY)},
                    (Vector2){static_cast<float>((i+1)*ChartScaleX),static_cast<float>(Price->at(i+1)*ChartScaleY)},
    //srand(time(0));
                    ChartThick,Up);
        }
    }
}

void ChartClassic::UpdateCamera(float DeltaTime) {
    if(IsKeyDown(KEY_UP))    CameraTarget.y -= CameraSpeed * DeltaTime;
    if(IsKeyDown(KEY_DOWN))  CameraTarget.y += CameraSpeed * DeltaTime;
    if(IsKeyDown(KEY_LEFT))  CameraTarget.x -= CameraSpeed * DeltaTime;
    if(IsKeyDown(KEY_RIGHT)) CameraTarget.x += CameraSpeed * DeltaTime;

    
    if(IsKeyDown(KEY_Q)) CameraSpeed+=2;
    if(IsKeyDown(KEY_A)) CameraSpeed-=2;
    
    if(IsKeyDown(KEY_W)) Camera->zoom += (CameraSpeed/1000) * DeltaTime;
    if(IsKeyDown(KEY_S)) Camera->zoom -= (CameraSpeed/1000) * DeltaTime;
   
    if(IsKeyDown(KEY_E)) ChartScaleX+=0.1f;
    if(IsKeyDown(KEY_D)) ChartScaleX-=0.1f;
    
    if(IsKeyDown(KEY_R)) ChartScaleY+=0.1f * (CameraSpeed/10);
    if(IsKeyDown(KEY_F)) ChartScaleY-=0.1f * (CameraSpeed/10);
    
    if(IsKeyDown(KEY_T)) ChartThick++;
    if(IsKeyDown(KEY_G)) ChartThick--;

    if(IsKeyPressed(KEY_C)) CameraSetYChart(); 
    if(IsKeyPressed(KEY_V)) CameraSetBeginChart();
    if(IsKeyPressed(KEY_B)) CameraSetEndChart();
    if(IsKeyPressed(KEY_L)) CameraLock = !CameraLock;

    Camera->target.x = Lerp(Camera->target.x,CameraTarget.x, 0.1);
    Camera->target.y = Lerp(Camera->target.y,CameraTarget.y, 0.1);
}

void ChartClassic::CameraSetYChart() {
    if(CameraTarget.x == 0) return;
    if(CameraTarget.x / ChartScaleX < Price->size()) CameraTarget.y = (Price->at(static_cast<int>(std::abs(CameraTarget.x / ChartScaleX) - 1)) * ChartScaleY); 
}

void ChartClassic::CameraSetBeginChart() {
        if(CameraTarget.x / ChartScaleX == 0) CameraTarget.y = (Price->at(static_cast<int>(std::abs(CameraTarget.x / ChartScaleX))) * ChartScaleY);
        else if(CameraTarget.x / ChartScaleX < Price->size()) CameraTarget.y = (Price->at(static_cast<int>(std::abs(CameraTarget.x / ChartScaleX) - 1)) * ChartScaleY); 
        CameraTarget.x = 0;
}

void ChartClassic::CameraSetEndChart() {
    CameraTarget.y = (Price->at(Price->size() - 1) * ChartScaleY); 
    CameraTarget.x = static_cast<float>(Price->size() * ChartScaleX);
}

void ChartClassic::CameraSetYXChart() {
    CameraSetYChart();
    CameraTarget.x = static_cast<float>(Price->size() * ChartScaleX);
}
