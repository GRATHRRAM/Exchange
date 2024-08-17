#pragma once
#include "../stock.hpp"
#include <cstdint>
#include <raylib.h>

class ChartClassic {
    private:
        stock::StockData *StockData;
        Camera2D *Camera;
        uint8_t _PrintVars;

    public:
        float CameraSpeed;
        float ChartScaleX;
        float ChartScaleY;
        float ChartThick;
        uint32_t ChartCompresion;

        ChartClassic(stock::StockData *_StockData, Camera2D *_Camera);
        void Draw();
        void UpdateCamera(float DeltaTime);
        void PrintVars(bool CameraSpeed,bool ChartScaleX,bool ChartScaleY,
                bool ChartThick,bool ChartCompresion,bool CameraPosition,
                bool CameraZoom);
};
