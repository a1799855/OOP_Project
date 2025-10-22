#ifndef ECONOMY_H
#define ECONOMY_H

// Manages 'bank' for each faction, controlling quantity of gold and rate of income
// Can spend gold buying units, thereby decreasing total amount

class Economy {
    private:
        int gold;           // Current amount of gold for each faction
        float incomeRate;   // Rate of gold increase per timestep
        float acc;
    public:
        Economy();                      // Economy created with default values 
        ~Economy() {}; 

        void update(float dt);          // Each faction receives income each timestep
        void spend(int cost);           // Decreases gold amount by cost of a unit

        void setIncomeRate(float inc);  // Sets rate of income increase
        int getGold() const;            // Returns amount of gold present
        float getIncomeRate() const;    // Returns rate of income
        void logging();                 // Print entire state of object to file
};

#endif