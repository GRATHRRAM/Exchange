#pragma once
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

        ChartClassic(std::vector<double> *Price, Camera2D *_Camera);
        void Draw();
        void UpdateCamera(float DeltaTime);
};
