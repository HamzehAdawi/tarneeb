#include <iostream>
#include <string>
#include <map>
#include <vector>

class Decks {
    private:
        std::map<std::string, int> cardValues = {
            {"Ace", 10},
            {"King", 10},
            {"Queen", 10},
            {"Jack", 10},
            {"10", 10},
            {"9", 9},
            {"8", 8},
            {"7", 7},
            {"6", 6},
            {"5", 5},
            {"4", 4},
            {"3", 3},
            {"2", 2},
        };
        
        std::map<std::string, std::vector<std::string>> suites = {
            {"Hearts", {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"}},
            {"Diamonds", {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"}},
            {"Clubs", {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"}},
            {"Spades", {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"}}
        };

        std::vector<std::string> cards;

    
    public:

        Decks() {}

        std::map<std::string, int> getCardValues() {
            return cardValues;
        }

        std::map<std::string, std::vector<std::string>> getSuites() {
            return suites;
        }

        std::vector<std::string>& getCards() {
            return cards;
        }

        void shuffleCards() {
            // minimal implementation: no-op for now
        }

};