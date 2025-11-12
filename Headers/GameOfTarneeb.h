#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "Players.h"
#include "Deck.h"
#include "Suits.h"
#include "thread"

class GameOfTarneeb {
    private:
        int playerCount;
        int currTurn = 0;
        std::vector<std::string>* cards;
        std::vector<std::string> spentCards;
        std::vector<std::vector<std::string>> playersHands; 
        std::vector<Players> players;

    public:
        Deck deck;
        GameOfTarneeb(int players);
        void handOutCards();
        void startGame();
        void cycleTurn();
        void printCards();
        std::vector<std::string>& getSpentCards();
};
