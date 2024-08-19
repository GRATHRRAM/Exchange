#include "chartclassic.hpp"
#include <cmath>
#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>

ChartClassic::ChartClassic(std::vector<double> *_Price, Camera2D *_Camera, std::string *_CompanyName) {
    CompanyName = _CompanyName;
    Price = _Price;
    Camera    = _Camera;
    CameraSpeed = 100;
    ChartScaleX = 15;
    ChartScaleY = -2500;
    ChartThick  = 5;
}

void ChartClassic::Draw() {
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawFPS(10,150);
    DrawText(CompanyName->c_str(),10,10,20,BLACK);
    if(_PrintVars & 0b10000000) DrawText(TextFormat("CameraSpeed: %.2f",CameraSpeed),10,40,15,LIGHTGRAY);
    if(_PrintVars & 0b01000000) DrawText(TextFormat("CameraPosition{x: %.2f,y: %.2f}",Camera->target.x,Camera->target.y),10,55,15,LIGHTGRAY);
    if(_PrintVars & 0b00100000) DrawText(TextFormat("CameraZoom: %.2f",Camera->zoom),10,70,15,LIGHTGRAY);
    if(_PrintVars & 0b00010000) DrawText(TextFormat("ChartScaleX: %.2f",ChartScaleX),10,85,15,LIGHTGRAY);
    if(_PrintVars & 0b00001000) DrawText(TextFormat("ChartScaleY: %.2f",ChartScaleY),10,100,15,LIGHTGRAY);
    if(_PrintVars & 0b00000100) DrawText(TextFormat("ChartThick: %.2f" ,ChartThick) ,10,115,15,LIGHTGRAY);
    BeginMode2D(*Camera);

    uint64_t charts = Price->size();

    for(uint64_t i = 0; i < charts; ++i) {
        if(i+1 >= charts) break;
        if(Price->at(i) >= Price->at(i+1)) {
            DrawLineEx((Vector2){static_cast<float>(i)*ChartScaleX,static_cast<float>(Price->at(i)*ChartScaleY)},
                    (Vector2){static_cast<float>((i+1)*ChartScaleX),static_cast<float>(Price->at(i+1)*ChartScaleY)},
                    ChartThick,RED);
        } else {
            DrawLineEx((Vector2){static_cast<float>(i)*ChartScaleX,static_cast<float>(Price->at(i)*ChartScaleY)},
                    (Vector2){static_cast<float>((i+1)*ChartScaleX),static_cast<float>(Price->at(i+1)*ChartScaleY)},
                    ChartThick,GREEN);
        }
    }
    
    EndMode2D();
    EndDrawing();
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

    if(IsKeyPressed(KEY_C) && Camera->target.x / ChartScaleX < Price->size()) Camera->target.y = (Price->at(static_cast<int>(std::abs(Camera->target.x / ChartScaleX) - 1)) * ChartScaleY); 
    if(IsKeyPressed(KEY_V)) {
        if(Camera->target.x / ChartScaleX == 0) Camera->target.y = (Price->at(static_cast<int>(std::abs(Camera->target.x / ChartScaleX))) * ChartScaleY);
        else if(Camera->target.x / ChartScaleX < Price->size()) Camera->target.y = (Price->at(static_cast<int>(std::abs(Camera->target.x / ChartScaleX) - 1)) * ChartScaleY); 
        Camera->target.x = 0;
    }
    if(IsKeyPressed(KEY_B)) {
        Camera->target.y = (Price->at(Price->size() - 1) * ChartScaleY); 
        Camera->target.x = static_cast<float>(Price->size() * ChartScaleX);
    }
}

void ChartClassic::PrintVars(bool cs,bool cp,bool cz,bool csx,bool csy,bool ct) {
    _PrintVars = 0;
    if(cs)  _PrintVars = _PrintVars | 0b10000000;
    if(cp)  _PrintVars = _PrintVars | 0b01000000;
    if(cz)  _PrintVars = _PrintVars | 0b00100000;
    if(csx) _PrintVars = _PrintVars | 0b00010000;
    if(csy) _PrintVars = _PrintVars | 0b00001000;
    if(ct)  _PrintVars = _PrintVars | 0b00000100;
}
