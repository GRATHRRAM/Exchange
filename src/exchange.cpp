#include "exchange.hpp"
#include "charts/chartclassic.hpp"
#include "stock.hpp"
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <raylib.h>

Exchange::Exchange(uint16_t x, uint16_t y, uint64_t sc, size_t _seed) {
    ResX = x;
    ResY = y;
    seed = _seed;

    stock::RandomStock(seed,
    &StockData,
    sc,
    StockConfig.Expiry,
    StockConfig.RiskLessInterestRate,
    StockConfig.DividentYeld,
    StockConfig.VolatilityOfStock,
    GetRandomValue(1,10000) / 1000.f);
    
    NPrice = stock::Normalize(&StockData.Price);

    Camera = {
        (Vector2){static_cast<float>(ResX/2.f),static_cast<float>(ResY/2.f)},
        (Vector2){0,0},
        0,
        1
    };

    Chart = new ChartClassic(&NPrice.Price, &Camera);
    
    Camera.target.y = (NPrice.Price.at(NPrice.Price.size() - 1) * Chart->ChartScaleY); 
    Camera.target.x = static_cast<float>(NPrice.Price.size() * Chart->ChartScaleX);
    
    InitWindow(ResX, ResY, "Exchange");
    SetTargetFPS(60);
}

Exchange::~Exchange() {
    delete Chart;
}

void Exchange::UpdateEvents() {
   Chart->UpdateCamera(GetFrameTime());

    if(IsKeyPressed(KEY_N)) { //new chart
            seed = rand() % RAND_MAX;
            stock::RandomStock(seed,
            &StockData, 10000,
            StockConfig.Expiry,
            StockConfig.RiskLessInterestRate,
            StockConfig.DividentYeld,
            StockConfig.VolatilityOfStock,
            GetRandomValue(0,10000) / 1000.f);
            
            NPrice = stock::Normalize(&StockData.Price);

            Camera.target.y = (NPrice.Price.at(NPrice.Price.size() - 1) * Chart->ChartScaleY); 
            Camera.target.x = static_cast<float>(NPrice.Price.size() * Chart->ChartScaleX);
    }
}

void Exchange::UpdateRender() {
    BeginDrawing();
        ClearBackground(RenderConfig.ChartBackgroudColor);

        BeginMode2D(Camera);
            Chart->Draw(RenderConfig.ChartUpPriceColor,RenderConfig.ChartDownPriceColor); 
        EndMode2D();
        
        DrawText(StockData.CompanyName.c_str(),10,10,20,BLACK);
        if(_PrintVars & 0b10000000) DrawText(TextFormat("CameraSpeed: %.2f",Chart->CameraSpeed),10,40,15,LIGHTGRAY);
        if(_PrintVars & 0b01000000) DrawText(TextFormat("CameraPosition{x: %.2f,y: %.2f}",Camera.target.x,Camera.target.y),10,55,15,LIGHTGRAY);
        if(_PrintVars & 0b00100000) DrawText(TextFormat("CameraZoom: %.2f",Camera.zoom),10,70,15,LIGHTGRAY);
        if(_PrintVars & 0b00010000) DrawText(TextFormat("ChartScaleX: %.2f",Chart->ChartScaleX),10,85,15,LIGHTGRAY);
        if(_PrintVars & 0b00001000) DrawText(TextFormat("ChartScaleY: %.2f",Chart->ChartScaleY),10,100,15,LIGHTGRAY);
        if(_PrintVars & 0b00000100) DrawText(TextFormat("ChartThick: %.2f" ,Chart->ChartThick) ,10,115,15,LIGHTGRAY);
        
        DrawText(TextFormat("Seed: %zu", seed), 10, ResY - 20,20, BLACK);
        DrawFPS(10, ResY - 40);
    EndDrawing();
}

void Exchange::UpdateCharts() {

}

void Exchange::Update() {
    UpdateEvents();
    UpdateCharts();
    UpdateRender();
}


void Exchange::PrintVars(bool cs,bool cp,bool cz,bool csx,bool csy,bool ct) {
    _PrintVars = 0;
    if(cs)  _PrintVars = _PrintVars | 0b10000000;
    if(cp)  _PrintVars = _PrintVars | 0b01000000;
    if(cz)  _PrintVars = _PrintVars | 0b00100000;
    if(csx) _PrintVars = _PrintVars | 0b00010000;
    if(csy) _PrintVars = _PrintVars | 0b00001000;
    if(ct)  _PrintVars = _PrintVars | 0b00000100;
}
