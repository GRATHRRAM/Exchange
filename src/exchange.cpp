#include "exchange.hpp"
#include "charts/chartclassic.hpp"
#include "stock.hpp"
#include <cstdint>
#include <raylib.h>

Exchange::Exchange(uint16_t x, uint16_t y, uint64_t sc) {
    ResX = x;
    ResY = y;

    stock::RandomStock(&StockData,
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

    Chart = new ChartClassic(&NPrice.Price, &Camera, &StockData.CompanyName);
    
    Chart->PrintVars(1,1,1,1,1,1);

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
            stock::RandomStock(&StockData, 10000,
            StockConfig.Expiry,
            StockConfig.RiskLessInterestRate,
            StockConfig.DividentYeld,
            StockConfig.VolatilityOfStock,
            GetRandomValue(0,10000) / 1000.f);
            Camera.target.y = (StockData.Price.at(StockData.Price.size() - 1) * Chart->ChartScaleY); 
            Camera.target.x = static_cast<float>(StockData.Price.size() * Chart->ChartScaleX);
    }
}

void Exchange::UpdateRender() {
    Chart->Draw();
}

void Exchange::UpdateCharts() {

}

void Exchange::Update() {
    UpdateEvents();
    UpdateCharts();
    UpdateRender();
}
