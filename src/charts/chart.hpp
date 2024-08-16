#pragma once

#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>

namespace chart {
    typedef struct ChartData {
        std::string CompanyName;
        std::vector<double> Price;
        double r;          // Riskless interest rate
        double q;          // Divident yield
        double sigma;      // Volatility of stock
        double T;          // Time (expiry)
    } ChartData;

    extern std::string CompanyKeyWords[22];
    const uint32_t CompanyKeyWordsCout = 22;
    const double DefaultR = 0.04;
    const double DefaultQ = 0.0;
    const double DefaultSigma = 0.20;
    const double DefaultT = 1;

    std::string RandomName(std::string *KeyWords, uint32_t WordCout); 
    void RandomChart(chart::ChartData *_ChartData, uint64_t chartsize, const int N, const double T,const double r, const double q, const double sigma, const double S0);
    void UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime);
};
