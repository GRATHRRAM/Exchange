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

void chart::RandomChart(chart::ChartData *_ChartData, uint64_t chartsize, const int N, const double T,
        const double r, const double q, const double sigma, const double S0) { //todo StockFloat accally do something
    srand(time(0));
    _ChartData->CompanyName = chart::RandomName(chart::CompanyKeyWords, chart::CompanyKeyWordsCout);
    
    
        double dt =  T/N;
        _ChartData->Price.push_back(S0);
        std::normal_distribution<double> dist(0.0, 1.0);
        double drift  = exp(dt*((r - q)-0.5*sigma*sigma));
        double vol = sqrt(sigma*sigma*dt);
        for(int i = 1; i < N; i++){
            double Z = dist(rng);
            _ChartData->Price.push_back(_ChartData->Price[i-1] * drift * exp(vol*Z));
        }
    
       _ChartData->T = T;
       _ChartData->r = r;
       _ChartData->q = q;
       _ChartData->sigma = sigma;
}

void chart::UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime) {
    if(IsKeyDown(KEY_UP))    Camera->target.y -= Speed * DeltaTime;
    if(IsKeyDown(KEY_DOWN))  Camera->target.y += Speed * DeltaTime;
    if(IsKeyDown(KEY_LEFT))  Camera->target.x -= Speed * DeltaTime;
    if(IsKeyDown(KEY_RIGHT)) Camera->target.x += Speed * DeltaTime;
}
