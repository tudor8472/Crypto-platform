#include "OrderBook.h"
#include "CSVreader.h"
#include <map>
#include <algorithm>

OrderBook::OrderBook(std::string filename){
    orders=CSVReader::readCSV(filename);
}
std::vector<std::string> OrderBook::getKnownProducts(){

    std::vector<std::string> products;
    std::map<std::string, bool> prodMap;

    for(OrderBookEntry &e:orders){
        prodMap[e.product] = true;
    }
    for(auto const& e:prodMap){
        products.push_back(e.first);
    }

    return products;
}
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type, std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e:orders){
        if(e.orderType==type &&
        e.product==product && e.timestamp==timestamp){
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

std::string OrderBook::getEarliestTime(){
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std ::string timestamp){
    std::string nexttimestamp = "";
    for (OrderBookEntry &e : orders)
    {
        if(e.timestamp> timestamp){
            nexttimestamp = e.timestamp;
            break;
        }
    }
    if(nexttimestamp==""){
        nexttimestamp = orders[0].timestamp;
    }
    return nexttimestamp;
}

    double OrderBook::getHighPrice(std::vector<OrderBookEntry> &orders)
{
    double max = orders[0].price;
    for(OrderBookEntry&e: orders){
        if(e.price>max){
            max = e.price;
        }
    }
    return max;
}


double OrderBook::getLowestPrice(std::vector<OrderBookEntry> &orders)
{
    double min = orders[0].price;
    for (OrderBookEntry &e : orders)
    {
        if (e.price < min)
        {
            min = e.price;
        }
    }
    return min;
}
//orders is a vector of OrderBookEntries and the return, average is a double
double OrderBook::getAveragePrice(std::vector<OrderBookEntry> &orders){
    double sum = 0;
    for(OrderBookEntry &e:orders){
        sum += e.price;
    }
    double average = sum / orders.size();
    return average;
}

void OrderBook::insertOrder(OrderBookEntry &order){
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAskToBids(std::string product,std::string timestamp){
    std::vector<OrderBookEntry> asks = OrderBook::getOrders(OrderBookType::ask, product, timestamp);

    std::vector<OrderBookEntry> bids = OrderBook::getOrders(OrderBookType::bid, product, timestamp);

    std::vector<OrderBookEntry> sales;

    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceUp);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDown);
    for(OrderBookEntry &ask:asks){
        for(OrderBookEntry &bid:bids){
            if(bid.price>=ask.price){
                OrderBookEntry sale{ask.price, 0,
                    timestamp, product, OrderBookType::ask};

                if(bid.username == "simuser"){

                    sale.username = "simuser";
                    sale.orderType = OrderBookType::bidsale;
                }

                if(ask.username == "simuser"){

                    sale.username = "simuser";
                    sale.orderType = OrderBookType::asksale;
                }

                if (bid.amount == ask.amount && bid.amount > 0)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0;
                    break;
                }
                if (bid.amount > ask.amount && bid.amount > 0)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = bid.amount - ask.amount;
                    break;
                }
                if(bid.amount < ask.amount && bid.amount>0){
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }
    return sales;
}