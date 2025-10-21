#ifndef ECONOMY_H
#define ECONOMY_H

class Economy {
    private:
        int gold;           // Current amount of gold for each faction
        float incomeRate;   // Rate of gold increase per timestep
        float acc;          // Accumulation?
    public:
        Economy();          // Economy created with default values 
        ~Economy() {};

        void update(float dt);          // Increases gold value
        void spend(int cost);           // Decreases gold by cost

        void setIncomeRate(float inc);  // Sets rate of income increase
        int getGold();                  // Returns amount of gold present
        float getIncomeRate();          // Returns rate of income
};

#endif