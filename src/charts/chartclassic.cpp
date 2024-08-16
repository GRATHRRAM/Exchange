#include "chartclassic.hpp"
#include "chart.hpp"
#include <cstdint>
#include <raylib.h>

ChartClassic::ChartClassic(chart::ChartData *_ChartData, Camera2D *_Camera) {
    ChartData = _ChartData;
    Camera    = _Camera;
    CameraSpeed = 100;
    ChartScaleX = 15;
    ChartScaleY = -4000;
    ChartThick  = 5;
    ChartCompresion = 0;
}

void ChartClassic::Draw() {
    BeginDrawing();
    ClearBackground(DARKGRAY);
    DrawText(ChartData->CompanyName.c_str(),10,10,20,BLACK);
    if(_PrintVars & 0b10000000) DrawText(TextFormat("CameraSpeed: %.2f",CameraSpeed),10,40,15,LIGHTGRAY);
    if(_PrintVars & 0b01000000) DrawText(TextFormat("ChartScaleX: %.2f",ChartScaleX),10,55,15,LIGHTGRAY);
    if(_PrintVars & 0b00100000) DrawText(TextFormat("ChartScaleY: %.2f",ChartScaleY),10,70,15,LIGHTGRAY);
    if(_PrintVars & 0b00010000) DrawText(TextFormat("ChartThick: %.2f" ,ChartThick) ,10,85,15,LIGHTGRAY);
    if(_PrintVars & 0b00001000) DrawText(TextFormat("ChartCompresion: %.2f",ChartCompresion),10,100,15,LIGHTGRAY);
    if(_PrintVars & 0b00000100) DrawText(TextFormat("CameraPosition{x: %.2f,y: %.2f}",Camera->target.x,Camera->target.y),10,115,15,LIGHTGRAY);
    if(_PrintVars & 0b00000010) DrawText(TextFormat("CameraZoom: %.2f",Camera->zoom),10,130,15,LIGHTGRAY);
    BeginMode2D(*Camera);

    uint64_t charts = ChartData->Price.size();
    for(uint64_t i = 0; i < charts; ++i) {
        if(i+1 >= charts) break;
        if(ChartData->Price.at(i) >= ChartData->Price.at(i+1)) {
            DrawLineEx((Vector2){static_cast<float>(i)*ChartScaleX,static_cast<float>(ChartData->Price.at(i)*ChartScaleY)},
                    (Vector2){static_cast<float>((i+1)*ChartScaleX),static_cast<float>(ChartData->Price.at(i+1)*ChartScaleY)},
                    ChartThick,RED);
        } else {
            DrawLineEx((Vector2){static_cast<float>(i)*ChartScaleX,static_cast<float>(ChartData->Price.at(i)*ChartScaleY)},
                    (Vector2){static_cast<float>((i+1)*ChartScaleX),static_cast<float>(ChartData->Price.at(i+1)*ChartScaleY)},
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
    
    if(IsKeyDown(KEY_W)) ChartScaleX+=0.1f;
    if(IsKeyDown(KEY_S)) ChartScaleX-=0.1f;
    
    if(IsKeyDown(KEY_E)) ChartScaleY+=0.1f;
    if(IsKeyDown(KEY_D)) ChartScaleY-=0.1f;
    
    if(IsKeyDown(KEY_R)) ChartThick++;
    if(IsKeyDown(KEY_F)) ChartThick--;
    
    if(IsKeyDown(KEY_T)) ChartCompresion++;
    if(IsKeyDown(KEY_G)) ChartCompresion++;
 
    if(IsKeyDown(KEY_Z)) Camera->zoom += (CameraSpeed/100) * DeltaTime;
    if(IsKeyDown(KEY_X)) Camera->zoom -= (CameraSpeed/100) * DeltaTime;
}

void ChartClassic::PrintVars(bool cs,bool csx,bool csy,bool ct,bool cc,bool cp,bool cz) {
    _PrintVars = 0;
    if(cs)  _PrintVars = _PrintVars | 0b10000000;
    if(csx) _PrintVars = _PrintVars | 0b01000000;
    if(csy) _PrintVars = _PrintVars | 0b00100000;
    if(ct)  _PrintVars = _PrintVars | 0b00010000;
    if(cc)  _PrintVars = _PrintVars | 0b00001000;
    if(cp)  _PrintVars = _PrintVars | 0b00000100;
    if(cz)  _PrintVars = _PrintVars | 0b00000010;
}

