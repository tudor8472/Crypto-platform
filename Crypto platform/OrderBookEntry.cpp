#include"OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double price,
                   double amount,
                   std::string timestamp,
                   std::string product,
                   OrderBookType orderType,
                   std::string username)
        : price(price),
         amount(amount),
          timestamp(timestamp),
           product(product),
            orderType(orderType),
            username(username)
    {
    }

OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){

    if(s == "ask")
        {
            return OrderBookType::ask;
        }
    else
        if(s=="bid")
            return OrderBookType::bid;
        else
            return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimestamp(OrderBookEntry &e1, OrderBookEntry &e2){

    return e1.timestamp < e2.timestamp;
}

bool OrderBookEntry::compareByPriceUp(OrderBookEntry &e1, OrderBookEntry &e2)
{
    return e1.price < e2.price;
}
bool OrderBookEntry::compareByPriceDown(OrderBookEntry &e1, OrderBookEntry &e2)
{
    return e1.price > e2.price;
}
