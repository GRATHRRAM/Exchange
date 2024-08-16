#include "chart.hpp"
#include <cstdint>
#include <cstdlib>
#include <raylib.h>
#include <string>
#include <ctime>
#include <math.h>
#include <random>

static std::mt19937 rng(time(0)); 

std::string chart::CompanyKeyWords[22] = {
    "Metal","wood","Gun","Food",
    "House","Fance","Sales","Good",
    "Bad","Cool","Bikes","Car","Tv",
    "HardWare","SoftWare","Electronics",
    "Enginering","Making","Producing",
    "Manufacturing","Real"
};

std::string chart::RandomName(std::string *KeyWords, uint32_t WordsCout) {
    srand(time(0));

    uint8_t wordsc = GetRandomValue(2,3);
    std::string name = "";

    for(uint8_t i = 0; i < wordsc; ++i) {
        name += KeyWords[GetRandomValue(0,WordsCout)];
        name += " ";
    }
    return name;
}

void chart::RandomChart(chart::ChartData *_ChartData, const uint32_t StockDataSize, const double Expiry,
        const double RiskLessInterestRate, const double DividentYeld, const double VolatilityOfStock, const double StartingPrice) {
    srand(time(0));
    _ChartData->CompanyName = chart::RandomName(chart::CompanyKeyWords, chart::CompanyKeyWordsCout);
    
    
        double dt =  Expiry/StockDataSize;
        _ChartData->Price.push_back(StartingPrice);
        std::normal_distribution<double> dist(0.0, 1.0);
        double drift  = exp(dt*((RiskLessInterestRate - DividentYeld)-0.5*VolatilityOfStock*VolatilityOfStock));
        double vol = sqrt(VolatilityOfStock*VolatilityOfStock*dt);
        for(uint32_t i = 1; i < StockDataSize; i++){
            double Z = dist(rng);
            _ChartData->Price.push_back(_ChartData->Price[i-1] * drift * exp(vol*Z));
        }
    
       _ChartData->Expiry = Expiry;
       _ChartData->RiskLessInterestRate = RiskLessInterestRate;
       _ChartData->DividentYield = DividentYeld;
       _ChartData->VolatilityOfStock = VolatilityOfStock;
}

void chart::UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime) {
    if(IsKeyDown(KEY_UP))    Camera->target.y -= Speed * DeltaTime;
    if(IsKeyDown(KEY_DOWN))  Camera->target.y += Speed * DeltaTime;
    if(IsKeyDown(KEY_LEFT))  Camera->target.x -= Speed * DeltaTime;
    if(IsKeyDown(KEY_RIGHT)) Camera->target.x += Speed * DeltaTime;
}
