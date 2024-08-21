#include "chartclassic.hpp"
#include <cmath>
#include <cstdint>
#include <raylib.h>
#include <vector>

ChartClassic::ChartClassic(std::vector<double> *_Price, Camera2D *_Camera) {
    Price = _Price;
    Camera    = _Camera;
    CameraSpeed = 100;
    ChartScaleX = 15;
    ChartScaleY = -2500;
    ChartThick  = 5;
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
    if(IsKeyDown(KEY_UP))    Camera->target.y -= CameraSpeed * DeltaTime;
    if(IsKeyDown(KEY_DOWN))  Camera->target.y += CameraSpeed * DeltaTime;
    if(IsKeyDown(KEY_LEFT))  Camera->target.x -= CameraSpeed * DeltaTime;
    if(IsKeyDown(KEY_RIGHT)) Camera->target.x += CameraSpeed * DeltaTime;

    
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
}

void ChartClassic::CameraSetYChart() {
    if(Camera->target.x / ChartScaleX < Price->size()) Camera->target.y = (Price->at(static_cast<int>(std::abs(Camera->target.x / ChartScaleX) - 1)) * ChartScaleY); 
}

void ChartClassic::CameraSetBeginChart() {
        if(Camera->target.x / ChartScaleX == 0) Camera->target.y = (Price->at(static_cast<int>(std::abs(Camera->target.x / ChartScaleX))) * ChartScaleY);
        else if(Camera->target.x / ChartScaleX < Price->size()) Camera->target.y = (Price->at(static_cast<int>(std::abs(Camera->target.x / ChartScaleX) - 1)) * ChartScaleY); 
        Camera->target.x = 0;
}

void ChartClassic::CameraSetEndChart() {
    Camera->target.y = (Price->at(Price->size() - 1) * ChartScaleY); 
    Camera->target.x = static_cast<float>(Price->size() * ChartScaleX);
}

void ChartClassic::CameraSetYXChart() {
    CameraSetYChart();
    Camera->target.x = static_cast<float>(Price->size() * ChartScaleX);
}
