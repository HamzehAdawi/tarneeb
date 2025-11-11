#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../Sources/Players.cpp"
#include "../Sources/Decks.cpp"

class GameOfTarneeb {
    private:
        int playerCount;
        std::vector<std::vector<std::string>> playersHands; 
        std::vector<Players> players;


    public:
        Decks deck;
        GameOfTarneeb(int players);
        std::vector<int> handOutCards();
        void startGame();

};
