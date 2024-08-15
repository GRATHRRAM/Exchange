#include "chart.hpp"
#include <cstdint>
#include <raylib.h>
#include <string>
#include <ctime>


std::string chart::CompanyKeyWords[21] = {
    "Metal","wood","Gun","Food",
    "House","Fance","Sales","Good",
    "Bad","Cool","Bikes","Car","Tv",
    "HardWare","SoftWare","Electronics",
    "Enginering","Making","Producing",
    "Manufacturing","Real"
};

std::string chart::RandomName(std::string *KeyWords, uint32_t WordsCout) {
    srand(time(0));

    uint8_t wordsc = GetRandomValue(2,4);
    std::string name = "";

    for(uint8_t i = 0; i < wordsc; ++i) {
        name += KeyWords[GetRandomValue(0,WordsCout)];
        name += " ";
    }
    return name;
}

void chart::RandomChart(chart::ChartData *_ChartData, uint64_t chartsize) {
    _ChartData->CompanyName = chart::RandomName(chart::CompanyKeyWords, chart::CompanyKeyWordsCout);
    
    _ChartData->Data.push_back(GetRandomValue(-100000,100000) / 1000.f);
    for(uint64_t i = 1; i < chartsize; ++i) {
        _ChartData->Data.push_back(((GetRandomValue(-100000,100000) / 1000.f) 
         + _ChartData->Data.at(i-1)) / 2);
    }
}

void chart::UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime) {
    if(IsKeyDown(KEY_UP))    Camera->target.y -= Speed * DeltaTime;
    if(IsKeyDown(KEY_DOWN))  Camera->target.y += Speed * DeltaTime;
    if(IsKeyDown(KEY_LEFT))  Camera->target.x -= Speed * DeltaTime;
    if(IsKeyDown(KEY_RIGHT)) Camera->target.x += Speed * DeltaTime;
}
