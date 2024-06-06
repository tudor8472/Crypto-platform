#pragma once
#include<vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain{
    public:
        MerkelMain();
        void init();

    private:
        void PrintMenu();

        int getUserOption();

        void printHelp();

        void printMarketStats();

        void enterAsk();

        void enterBid();

        void printWallet();

        void Continue();

        void AveragePrice();

        void InvalidImput();

        void menu(int i);

        std::string curent_time;

        OrderBook orderBook{"csv.txt"};

        Wallet wallet;
};
