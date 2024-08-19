#include "stock.hpp"
#include <cstdint>
#include <cstdlib>
#include <raylib.h>
#include <string>
#include <ctime>
#include <math.h>
#include <random>
#include <fstream>
#include <vector>

std::string stock::RandomName(std::vector<std::string> KeyWords) {
    uint8_t wordsc = GetRandomValue(2,3);
    std::string name = "";
    
    uint64_t size = KeyWords.size();

    for(uint8_t i = 0; i < wordsc; ++i) {
        name += KeyWords[GetRandomValue(0,size)];
        name += " ";
    }
    return name;
}

void stock::RandomStock(size_t seed, stock::StockData *_StockData, const uint32_t StockDataSize, const double Expiry,
        const double RiskLessInterestRate, const double DividentYeld, const double VolatilityOfStock, const double StartingPrice) {
        
    static std::mt19937 rng(seed); 
    std::vector<std::string> names = stock::GetCompanyNames();
    _StockData->CompanyName = stock::RandomName(names);

    _StockData->Price.clear();

    double dt =  Expiry/StockDataSize;
    _StockData->Price.push_back(StartingPrice);
    std::normal_distribution<double> dist(0.0, 1.0);
    double drift  = exp(dt*((RiskLessInterestRate - DividentYeld)-0.5*VolatilityOfStock*VolatilityOfStock));
    double vol = sqrt(VolatilityOfStock*VolatilityOfStock*dt);
    for(uint32_t i = 1; i < StockDataSize; i++){
        double Z = dist(rng);
        _StockData->Price.push_back(_StockData->Price[i-1] * drift * exp(vol*Z));
    }
    
   _StockData->Expiry = Expiry;
   _StockData->RiskLessInterestRate = RiskLessInterestRate;
   _StockData->DividentYield = DividentYeld;
   _StockData->VolatilityOfStock = VolatilityOfStock;
}

std::vector<std::string> stock::GetCompanyNames() {
    std::fstream file;
    file.open("ExchangeData/templates/companynames.list", std::ios::in); 
    
    std::vector<std::string> sv;

    if (file.is_open()) { 
        std::string s;
        while(getline(file, s)) { 
            sv.push_back(s);
        }
        
        file.close(); 
    }
    
    return sv;
}

stock::NormalizedPrice stock::Normalize(const std::vector<double> *Vector) {
    uint64_t Size = Vector->size();
    
    double min = 1000000;
    double max = 0;

    for(uint64_t i = 0; i < Size; ++i) {
        if(Vector->at(i) < min) min = Vector->at(i);
        if(Vector->at(i) > max) max = Vector->at(i);
    }
    
    std::vector<double> buff;
    for(uint64_t i = 0; i < Size; ++i) {
        buff.push_back((Vector->at(i) - min) / (max - min));
    }

    stock::NormalizedPrice np = {
        buff,
        max,
        min
    };
    return np;
}
