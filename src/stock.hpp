#pragma once

#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>

namespace stock {
    typedef struct StockData {
        std::string CompanyName;
        std::vector<double> Price;
        double RiskLessInterestRate;
        double DividentYield;
        double VolatilityOfStock;
        double Expiry;//time
    } StockData;

    const double DefaultRiskLessInterestRate = 0.04;
    const double DefaultDividentYeld = 0.0;
    const double DefaultVolatilityOfStock = 0.20;
    const double DefaultExpiry = 1;
    const std::string DefaultPath = "templates/";

    std::string RandomName(std::vector<std::string> KeyWords);
    void RandomStock(stock::StockData *_StockData, const uint32_t StockDataSize, const double Expiry,
        const double RiskLessInterestRate, const double DividentYeld, const double VolatilityOfStock,
        const double StartingPrice);
    void UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime);
    std::vector<std::string> GetCompanyNames(std::string path);
};
