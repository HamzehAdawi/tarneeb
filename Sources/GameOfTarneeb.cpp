#include "../Headers/GameOfTarneeb.h"

GameOfTarneeb::GameOfTarneeb(int playerCount) {
        this->playerCount = playerCount;
        deck = Decks();

        //Initialize players with their player #
        for (int i = 0; i < playerCount; i++) {
            players.push_back(Players(i));
        }

        cards = &deck.getCards();        
    }

void GameOfTarneeb::startGame() {
    deck.shuffleCards();
    while (true) {
        handOutCards();
    }
}

std::vector<int> GameOfTarneeb::handOutCards() {
    int handoutCardAmount = 13;

    for (int i = 0; i < playerCount; i++) {
        if (players[i].getPlayerNum() == players[currTurn].getPlayerNum()) {
            handoutCardAmount = 14;
        }
        
        for (int j=0; j <handoutCardAmount; j++) {
            players[i].hand.addCard(cards[j]);
            cards->erase(cards->begin());

        }
    }
}
