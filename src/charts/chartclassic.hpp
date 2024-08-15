#pragma once
#include "chart.hpp"
#include <cstdint>
#include <raylib.h>

class ChartClassic {
    private:
        chart::ChartData *ChartData;
        Camera2D *Camera;
        uint8_t _PrintVars;

    public:
        float CameraSpeed;
        float ChartScaleX;
        float ChartScaleY;
        float ChartThick;
        uint32_t ChartCompresion;

        ChartClassic(chart::ChartData *_ChartData, Camera2D *_Camera);
        void Draw();
        void UpdateCamera(float DeltaTime);
        void PrintVars(bool CameraSpeed,bool ChartScaleX,bool ChartScaleY,
                bool ChartThick,bool ChartCompresion,bool CameraPosition,
                bool CameraZoom);
};
