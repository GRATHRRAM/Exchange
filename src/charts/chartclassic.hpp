#pragma once
#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>

class ChartClassic {
    private:
        std::vector<double> *Price;
        Camera2D *Camera;
        std::string *CompanyName;
        uint8_t _PrintVars;
    public:
        float CameraSpeed;
        float ChartScaleX;
        float ChartScaleY;
        float ChartThick;

        ChartClassic(std::vector<double> *Price, Camera2D *_Camera, std::string *CompanyName);
        void Draw();
        void UpdateCamera(float DeltaTime);
        void PrintVars(bool CameraSpeed,bool CameraPosition,bool CameraZoom,
                bool ChartScaleX,bool ChartScaleY,bool ChartThick);
};
