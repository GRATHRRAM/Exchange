#pragma once

#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>

namespace chart {
    typedef struct ChartData {
        std::vector<float> Data;
        std::string CompanyName;
    } ChartData;

    extern std::string CompanyKeyWords[21];
    const uint32_t CompanyKeyWordsCout = 21;

    std::string RandomName(std::string *KeyWords, uint32_t WordCout);
    void RandomChart(ChartData *_ChartData, uint64_t chartsize);
    void UpdateCamera(Camera2D *Camera, float Speed, float DeltaTime);
};
