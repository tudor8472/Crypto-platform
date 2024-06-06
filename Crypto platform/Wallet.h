#pragma once
#include "OrderBookEntry.h"
#include<string>
#include<map>
class Wallet{
public:
    Wallet();
    void insert_currency(std::string type, double amount);
    bool contains_currency(std::string type, double amount);
    std::string toString();
    bool removeCurrency(std::string type, double amount);
    bool canFulfillOrder(OrderBookEntry order);
    void processSale(OrderBookEntry &sale);

private:
    std::map<std::string, double> currencies;
};