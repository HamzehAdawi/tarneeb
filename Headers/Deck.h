#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <random> 
#include <algorithm> 

class Deck {
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
        
        std::vector<std::string> cards = {
            "2 Hearts", "3 Hearts", "4 Hearts", "5 Hearts", "6 Hearts", "7 Hearts", "8 Hearts", "9 Hearts", "10 Hearts", "Jack Hearts", "Queen Hearts", "King Hearts", "Ace Hearts",
            "2 Diamonds", "3 Diamonds", "4 Diamonds", "5 Diamonds", "6 Diamonds", "7 Diamonds", "8 Diamonds", "9 Diamonds", "10 Diamonds", "Jack Diamonds", "Queen Diamonds", "King Diamonds", "Ace Diamonds",
            "2 Clubs", "3 Clubs", "4 Clubs", "5 Clubs", "6 Clubs", "7 Clubs", "8 Clubs", "9 Clubs", "10 Clubs", "Jack Clubs", "Queen Clubs", "King Clubs", "Ace Clubs",
            "2 Spades", "3 Spades", "4 Spades", "5 Spades", "6 Spades", "7 Spades", "8 Spades", "9 Spades", "10 Spades", "Jack Spades", "Queen Spades", "King Spades", "Ace Spades"
        };

        std::vector<std::string> suits = {
            "|  /\\  |\n| (__) |\n",
            "| (\\/) |\n|  \\/  |\n",
            "|  /\\  |\n|  \\/  |\n",
            "|  ()  |\n| ()() |\n",
        };

 
    
    public:
        Deck() {}
        std::map<std::string, int> getCardValues();
        std::vector<std::string>& getCards();
        void shuffleCards();
        void addCardsToDeck(std::vector<std::string> cards);
        std::string getSuit(int suit);
};