#include "../Headers/Players.h"

Players::Players(int playerNum) {
    this->playerNum = playerNum;
}

int Players::getPlayerNum() {
    return playerNum;
}

std::vector<std::string> Players::getPlayerHand() {
    return hand;
}

void Players::addCard(std::string card) {
    hand.push_back(card);
}

void Players::discardCard(std::string card) {
    
}