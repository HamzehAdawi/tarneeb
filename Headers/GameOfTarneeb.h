#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../Sources/Players.cpp"
#include "../Sources/Decks.cpp"

class GameOfTarneeb {
    private:
        int playerCount;
        int currTurn = 0;
        std::vector<std::string>* cards;
        std::vector<std::vector<std::string>> playersHands; 
        std::vector<Players> players;


    public:
        Decks deck;
        GameOfTarneeb(int players);
    void handOutCards();
        void startGame();

};
