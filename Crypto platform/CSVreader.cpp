#include "CSVreader.h"
#include <iostream>
#include <fstream>
CSVReader::CSVReader(){

}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName){
    
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFileName};
    std::string line;
    if(csvFile.is_open()){

        while(std::getline(csvFile,line)){
            try
            {
                OrderBookEntry obe = convertor(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch(const std::exception& e)
            {
                std::cout << "bad data\n";
            }
        }
    }
    //std::cout << entries.size()<<"\n";
    return entries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){
    
    std::vector<std::string> tokens;

    int start, end;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
        {
            token = csvLine.substr(start, end - start);
        }
        else
        {
            token = csvLine.substr(start, csvLine.length() - start);
        }
        tokens.push_back(token);
        start = end + 1;
    }while (end > 0);
    
    return tokens;
}

OrderBookEntry CSVReader::convertor(std::vector<std::string> tokens){
    

    double price, amount;

    if (tokens.size()!=5)
    {
        std::cout << "bad line\n";
        throw std::exception{};
    }

    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
        
    }
    catch (const std::exception &e)
    {
        std::cout << "bad read\n ";
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string price,
                            std::string amount,
                            std::string timestamp,
                            std::string product,
                            OrderBookType OrderType){

    double priced, amountd;

    try
    {
        priced = std::stod(price);
        amountd = std::stod(amount);
    }
    catch (const std::exception &e)
    {
        std::cout << "bad read\n ";
        throw;
    }

    OrderBookEntry obe{priced,
                       amountd,
                       timestamp,
                       product,
                       OrderType};
    return obe;
}
