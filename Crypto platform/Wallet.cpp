#include "Wallet.h"
#include "CSVreader.h"
#include <vector>
#include <iostream>
Wallet::Wallet(){

}
void Wallet::insert_currency(std::string type, double amount) {
    double balance;
    if(amount<0)
        throw std::exception();
    if (currencies.count(type) == 0) //not there
    {
        balance = 0;
    }
    else{
        balance = currencies[type];
    }
    balance += amount;
    currencies[type] = balance;
}
bool Wallet::contains_currency(std::string type, double amount) {
    if (currencies.count(type) == 0) //not there
    {
        return 0;
    }
    else
    {
        return currencies[type] >= amount;
    }
}
std::string Wallet::toString() {
    std::string s;
    for (auto pair : currencies)
    {
        std::string currency = pair.first;
        double amount = pair.second;
        s += currency + ":" + std::to_string(amount) + "\n";
    }
    s += "\0";
    return s;
}

bool Wallet::removeCurrency(std::string type, double amount){

    double balance;
    if (amount < 0)
        throw std::exception();
    if (currencies.count(type) == 0) //not there
    {
        std::cout << "Couldn't find " << type << "\n";
        return false;
    }
    else
    {
        if(contains_currency(type,amount)){
            currencies[type] -= amount;
            return true;
        }
        else{
            std::cout << "Couldn't remove " << type << ", insuficient funds\n";
            return false;
        }
    }
}

bool Wallet::canFulfillOrder(OrderBookEntry order){

    std::vector<std::string> currs = CSVReader::tokenise(order.product, '/');

    if(order.orderType==OrderBookType::ask){
        double amount = order.amount;
        std::string currency = currs[0];
        std::cout << "Wallet::canFulfillOrder " << currency << " : "<<amount<<std::endl;
        return contains_currency(currency, amount);
    }
    if (order.orderType == OrderBookType::bid)
    {
        double amount = order.amount*order.price;
        std::string currency = currs[1];
        std::cout << "Wallet::canFulfillOrder " << currency << " : " << amount << std::endl;
        return contains_currency(currency, amount);
    }

    return false;
}

void Wallet::processSale(OrderBookEntry &sale){
    std::vector<std::string> currs = CSVReader::tokenise(sale.product, '/');

    if (sale.orderType == OrderBookType::asksale)
    {
        double outgoingAmount = sale.amount;
        std::string outgoingCurrency = currs[0];

        double incomingAmount = sale.amount * sale.price;
        std::string incomingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    if (sale.orderType == OrderBookType::bidsale)
    {
        double incomingAmount = sale.amount;
        std::string incomingCurrency = currs[0];
  
        double outgoingAmount = sale.amount * sale.price;
        std::string outgoingCurrency = currs[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}