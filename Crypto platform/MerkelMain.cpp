#include "MerkelMain.h"
#include "CSVreader.h"
#include<iostream>

MerkelMain::MerkelMain(){

}

void MerkelMain::init()
{
    int input;
    curent_time = orderBook.getEarliestTime();
    wallet.insert_currency("BTC", 10);
    while (true)
    {
        PrintMenu();
        input = getUserOption();
        menu(input);
    }
}


void MerkelMain::PrintMenu()
{
    std::cout << "1: Print help" << std::endl;

    std::cout << "2: Print exchange stats" << std::endl;

    std::cout << "3: Place an ask" << std::endl;

    std::cout << "4: Place a bid" << std::endl;

    std::cout << "5: Print wallet" << std::endl;

    std::cout << "6: Continue" << std::endl;

    //std::cout << "7: Average prices" << std::endl;

    std::cout << "=============\n";

    std::cout << "Current time is: " << curent_time << std::endl;
}

int MerkelMain::getUserOption()
{
    int x;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try
    {
        x = std::stoi(line);
    }
    catch(const std::exception& e)
    {

    }

    return x;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. \n"
              << std::endl;
}

void MerkelMain::printMarketStats()
{
    for(std::string const &s:orderBook.getKnownProducts()){
        std::cout << "Product: " << s << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::bid, s, curent_time);
        std::cout << "Bids seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowestPrice(entries) << std::endl<<std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an offer - enter the amount: product, price, amount\n";
    std::string input;
    std::getline(std::cin, input);
    std::cout << "You typed: " << input << "\n\n";

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size()!=3){
        std::cout << "Wrong input\n";
    }
    else{
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1],
                                                        tokens[2],
                                                        curent_time,
                                                        tokens[0],
                                                        OrderBookType::ask
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good.\n";
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Insuficient funds\n";
            }
                }
        
        catch (const std::exception &e)
        {
            std::cout << "Wrong input\n";
        }
        
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make a bid - enter the amount: product, price, amount\n";
    std::string input;
    std::getline(std::cin, input);
    std::cout << "You typed: " << input << "\n\n";

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "Wrong input\n";
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(tokens[1], tokens[2], curent_time, tokens[0], OrderBookType::bid);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good.\n";
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Insuficient funds\n";
            }
        }

        catch (const std::exception &e)
        {
            std::cout << "Wrong input\n";
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}



void MerkelMain::Continue()
{
    std::cout << "Going to next time frame\n\n";
    std::vector<OrderBookEntry> sales= orderBook.matchAskToBids("ETH/BTC",curent_time);
    std::cout << "Sales: " << sales.size() << "\n";
    for (OrderBookEntry &sale : sales)
    {
        std::cout << "sale price: " << sale.price << "\nsale amount: " << sale.amount<<"\n";
        if(sale.username == "simuser"){
            wallet.processSale(sale);
        }
    }
    curent_time = orderBook.getNextTime(curent_time);
}

void MerkelMain::AveragePrice(){
    for (std::string const &s : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, s, curent_time);
        std::cout << "The average for " << s << " in the timestamp: " << curent_time << " is: " << OrderBook::getAveragePrice(entries) << std::endl<<std::endl;
    }
}

void MerkelMain::InvalidImput()
{
    std::cout << "Invalid Input\n\n";
}

void MerkelMain::menu(int i)
{
    switch (i){
        case 1:{
            printHelp();
            break;
        }
        case 2:{
            printMarketStats();
            break;
        }
        case 3:{
            enterAsk();
            break;
        }
        case 4:{
            enterBid();
            break;
        }
        case 5:{
            printWallet();
            break;
        }
        case 6:{
            Continue();
            break;
        }
        default:{
            InvalidImput();
            break;
        }
    }
}

