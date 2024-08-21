#pragma once
#include <cstdint>
#include <raylib.h>
#include <vector>

class ChartClassic {
    private:
        std::vector<double> *Price;
        Camera2D *Camera;
    public:
        float CameraSpeed;
        float ChartScaleX;
        float ChartScaleY;
        float ChartThick;
        uint8_t CameraLock;

        ChartClassic(std::vector<double> *Price, Camera2D *_Camera);
        void Draw(Color Up, Color Down);
        void UpdateCamera(float DeltaTime);
        void CameraSetYChart();
        void CameraSetBeginChart();
        void CameraSetEndChart();
        void CameraSetYXChart();
};
