#pragma once
#include "OrderBookEntry.h"
#include "CSVreader.h"
#include <string>
#include <vector>

class OrderBook{

public:
    OrderBook(std::string filename);
    std::vector<std::string> getKnownProducts();
    std::vector<OrderBookEntry> getOrders(OrderBookType type, std::string product, std::string timestamp);
    std::string getEarliestTime();
    std::string getNextTime(std :: string timestamp);

    void insertOrder(OrderBookEntry& order);

    std::vector<OrderBookEntry> matchAskToBids(std::string product, std::string timestamp);

    static double getHighPrice(std::vector<OrderBookEntry> &orders);
    static double getLowestPrice(std::vector<OrderBookEntry> &orders);
    static double getAveragePrice(std::vector<OrderBookEntry> &orders);

private:
    std::vector<OrderBookEntry> orders;
};