#pragma once
#include "../stock.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace LiveStockStaff {
    typedef struct News {
        std::string Title;
        std::string Content;
        float SellersImpact; //% ex +0.20 -> +20% or -0.20 -> -20%
        float BuyersImpact;
    } News;

    std::vector<std::string> GetNewsTemplates(std::string Path);
    void RandomNews(News *_News, News *NewsTemplates);
}


class LiveStock {
    private:
        stock::StockData *Stock;
        uint32_t Sellers;
        uint32_t Buyers;
        LiveStockStaff::News News;
        float RealCoolDown;
    public:
        float CoolDown = 1;

        LiveStock(stock::StockData *Stock, float CoolDownSeconds);
        void Simulate(float DeltaTime);  
};
