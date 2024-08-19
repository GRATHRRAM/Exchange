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

    typedef struct NormalizedPrice {
        std::vector<double> Price;
        double max;
        double min;
    } NormalizedPrice;

    const double DefaultCalmRiskLessInterestRate = 0.04;
    const double DefaultCalmDividentYeld = 0.0;
    const double DefaultCalmVolatilityOfStock = 0.20;
    const double DefaultCalmExpiry = 1;
   
    const double DefaultRiskLessInterestRate = 0.08;
    const double DefaultDividentYeld = 0.2;
    const double DefaultVolatilityOfStock = 0.40;
    const double DefaultExpiry = 2;

    std::string RandomName(std::vector<std::string> KeyWords);
    void RandomStock(stock::StockData *_StockData, const uint32_t StockDataSize, const double Expiry,
        const double RiskLessInterestRate, const double DividentYeld, const double VolatilityOfStock,
        const double StartingPrice);
    void UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime);
    std::vector<std::string> GetCompanyNames();
    stock::NormalizedPrice Normalize(const std::vector<double> *data);
};
