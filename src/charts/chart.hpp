#pragma once

#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>

namespace chart {
    typedef struct ChartData {
        std::string CompanyName;
        std::vector<double> Price;
        double RiskLessInterestRate;
        double DividentYield;
        double VolatilityOfStock;
        double Expiry;//time
    } ChartData;

    extern std::string CompanyKeyWords[22];
    const uint32_t CompanyKeyWordsCout = 22;
    const double DefaultRiskLessInterestRate = 0.04;
    const double DefaultDividentYeld = 0.0;
    const double DefaultVolatilityOfStock = 0.20;
    const double DefaultExpiry = 1;

    std::string RandomName(std::string *KeyWords, uint32_t WordCout); 
    void RandomChart(chart::ChartData *_ChartData, const uint32_t StockDataSize, const double Expiry,
        const double RiskLessInterestRate, const double DividentYeld, const double VolatilityOfStock,
        const double StartingPrice);
    void UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime);
};
