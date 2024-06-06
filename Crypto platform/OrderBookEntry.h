#pragma once
#include <string>

enum class OrderBookType
{
    bid,
    ask,
    asksale,
    bidsale,
    unknown
};

class OrderBookEntry
{
public:
    double price;
    double amount;
    std::string timestamp;
    std::string product;
    OrderBookType orderType;
    std::string username;
    static bool compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2);
    static bool compareByPriceUp(OrderBookEntry &e1, OrderBookEntry &e2);
    static bool compareByPriceDown(OrderBookEntry &e1, OrderBookEntry &e2);
    OrderBookEntry(double price,
                   double amount,
                   std::string timestamp,
                   std::string product,
                   OrderBookType orderType,
                   std::string username="dataset");

    static OrderBookType stringToOrderBookType(std::string s);
};