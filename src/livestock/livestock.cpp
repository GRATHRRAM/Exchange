#include "livestock.hpp"
#include <cstddef>
#include <raylib.h>
#include <random>


LiveStock::LiveStock(stock::StockData *S, stock::NormalizedPrice *np ,size_t *_Seed, float c) {
    Stock = S;
    NPrice = np;
    CoolDown = c;
    Seed = _Seed;
    Sellers = GetRandomValue(0,100);
    Buyers = GetRandomValue(0,100);
}

void LiveStock::Simulate(float DeltaTime) {
    RealCoolDown -= DeltaTime; 
    if(RealCoolDown > 0) return;
    RealCoolDown = CoolDown;

    static std::mt19937 rng(*Seed); 

    double dt =  Stock->Expiry/Stock->Price.size();
    std::normal_distribution<double> dist(0.0, 1.0);
    double drift  = exp(dt*((Stock->RiskLessInterestRate - Stock->DividentYield)-0.5*Stock->VolatilityOfStock*Stock->VolatilityOfStock));
    double vol = sqrt(Stock->VolatilityOfStock*Stock->VolatilityOfStock*dt);
    double Z = dist(rng);
    Stock->Price.push_back(Stock->Price[Stock->Price.size()-1] * drift * exp(vol*Z));

    stock::FastNormalize(NPrice, Stock->Price.at(Stock->Price.size() - 1));
}
