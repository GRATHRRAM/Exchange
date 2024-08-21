#pragma once
#include "../stock.hpp"
#include <cstddef>
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
        stock::NormalizedPrice *NPrice;
        uint32_t Sellers;
        uint32_t Buyers;
        LiveStockStaff::News News;
        float RealCoolDown;
    public:
        float CoolDown = 1;
        size_t *Seed = 0x0;

        LiveStock(stock::StockData *Stock,stock::NormalizedPrice *NPrice, size_t *Seed, float CoolDownSeconds);
        void Simulate(float DeltaTime);  
};
