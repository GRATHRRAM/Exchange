#pragma once
#include "charts/chartclassic.hpp"
#include "stock.hpp"
#include <cstddef>
#include <cstdint>
#include <raylib.h>
#include <vector>

class Exchange {
    private:
    
    typedef struct RenderCfg {
        Color ChartBackgroudColor;
        Color ChartUpPriceColor;
        Color ChartDownPriceColor;
        uint64_t DrawLinesCout;
    } RenderCfg;
    
    typedef struct StockCfg {
        double RiskLessInterestRate = 0.08;
        double DividentYeld = 0.2;
        double VolatilityOfStock = 0.4;
        double Expiry = 2;
    } StockCfg;

    typedef struct NormalizedPrice {
        std::vector<double> Price;
        double max;
        double min;
    } NormalizedPrice;

    uint8_t _PrintVars;

    void UpdateRender();
    void UpdateCharts();
    void UpdateEvents();
    public:
    stock::StockData StockData;
    stock::NormalizedPrice NPrice;
    Camera2D Camera;
    ChartClassic *Chart;
    size_t seed;

    uint16_t ResX = 800;
    uint16_t ResY = 600;
   
    RenderCfg RenderConfig = {
        DARKGRAY,
        GREEN,
        RED,
        10
    };

    StockCfg StockConfig = {
        0.08,
        0.2,
        0.4,
        2
    };

    Exchange(uint16_t ResX, uint16_t ResY,uint64_t CoutOfStartingStockData, size_t seed);
    ~Exchange();
    void Update();
    void PrintVars(bool CameraSpeed,bool CameraPosition,bool CameraZoom, bool ChartScaleX,bool ChartScaleY,bool ChartThick);
};
