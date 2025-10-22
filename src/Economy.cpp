#include <iostream>
#include <fstream>
#include <string>
#include "Economy.h"
#include "Debug.h"

using namespace std;

// Default constructor, factions start with 100 gold and accumulate at 5 gold per timestep
Economy::Economy() : gold(100), incomeRate(5.0f), acc(0.0f) {};

// Provided unit cost is within budget, subtracts cost of unit
void Economy::spend(int cost){
    if (cost <= gold){
        gold = gold - cost;
    }
}

// Apply timestep to increase the gold value by the rate of income
void Economy::update(float dt){ gold = gold + incomeRate; }

void Economy::setIncomeRate(float inc){incomeRate = inc;}   // Set rate of income
int Economy::getGold() const {return gold;}                 // Get current amount of gold
float Economy::getIncomeRate() const {return incomeRate;}   // Get current rate of income

// Create log to output entire state of object
void Economy::logging(){
    // If file exists, open and delete content (trunc)
    // If file doesn't exist, create it 
    ofstream file("log_Economy.txt", ios::out | ios::trunc);

    // Exit function & output to debugger if log file couldn't open
    if (!file){
        Debug::info("Could not open log file in Economy");
        return;
    }

    file << "Gold count: " << gold << endl;
    file << "Income rate: " << incomeRate << endl;
    file << "Accumulation value: " << acc << endl;

    file.close();
    Debug::info("Successfully wrote to Economy log file");
}