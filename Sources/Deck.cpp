#include "../Headers/Deck.h"

std::map<std::string, int> Deck::getCardValues() {
    return cardValues;
}

std::vector<std::string>& Deck::getCards() {
    return cards;
}

void Deck::addCardsToDeck(std::vector<std::string> cardsToAdd) {
    cards.insert(cards.end(), cardsToAdd.begin(), cardsToAdd.end());
}

// Fisher-Yates shuffling algorithm
void Deck::shuffleCards() {
    std::random_device rd;
    std::mt19937 g(rd()); 

    for (int i = cards.size() - 1; i > 0; --i) {
        std::uniform_int_distribution<> distrib(0, i);
        int j = distrib(g);

        std::swap(cards[i], cards[j]);
    }
}

std::string Deck::getSuit(int suit) {
    return suits[suit];
} 