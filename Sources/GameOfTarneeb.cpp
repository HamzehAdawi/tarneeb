#include "../Headers/GameOfTarneeb.h"

GameOfTarneeb::GameOfTarneeb(int playerCount) {
    this->playerCount = playerCount;
    deck = Deck();

    //Initialize players with their player #
    for (int i = 0; i < playerCount; i++) {
        players.push_back(Players(i));
    }

    cards = &deck.getCards();        
}

void GameOfTarneeb::startGame() {
    deck.shuffleCards();
    handOutCards();

    while (true) {
        std::cout << "Your turn: " << std::endl;
        std::cout << "HAND: " << std::endl;
        
        int handoutCardAmount = players[0].getPlayerNum() == currTurn ? 15:14;
        for (int i = 0; i < handoutCardAmount; i++) {
            
            {
                // Build ASCII art for each card first, then print them side-by-side (columnar)
                std::vector<std::vector<std::string>> asciiCards;

                for (std::string cardAndSuit: players[0].getPlayerHand()) {
                    std::istringstream iss(cardAndSuit);
                    std::string token;
                    std::string numValue;
                    std::string rankStr;
                    std::string suitStr;

                    while (iss >> token) {
                        if (token != "Spades" && token != "Hearts" && token != "Diamonds" && token != "Clubs") {
                            if (token == "Ace") rankStr = "A";
                            else if (token == "King") rankStr = "K";
                            else if (token == "Queen") rankStr = "Q";
                            else if (token == "Jack") rankStr = "J";
                            else rankStr = token; // numbers like 10, 9, 8...
                            numValue = token;
                        } else {
                            if (token == "Spades") suitStr = deck.getSuit(Suits::SPADE);
                            else if (token == "Hearts") suitStr = deck.getSuit(Suits::HEART);
                            else if (token == "Diamonds") suitStr = deck.getSuit(Suits::DIAMOND);
                            else if (token == "Clubs") suitStr = deck.getSuit(Suits::CLOVER);
                        }
                    }

                    // split suitStr into lines (Deck::getSuit returns two lines with '\n')
                    std::vector<std::string> suitLines;
                    std::istringstream sss(suitStr);
                    std::string line;
                    while (std::getline(sss, line)) {
                        if (!line.empty()) suitLines.push_back(line);
                    }
                    // ensure missing suit lines are full-width card interior rows (with '|' edges)
                    while (suitLines.size() < 2) suitLines.push_back(std::string("|      |"));

                    // Construct fixed-height ASCII card (5 lines)
                    std::vector<std::string> cardLines;
                    cardLines.push_back(".------.");

                    if (rankStr == "10") cardLines.push_back("|10    |");
                    else if (!rankStr.empty()) cardLines.push_back(std::string("|") + rankStr + "     |");
                    else cardLines.push_back("|?     |");

                    // suitLines contain e.g. "|  /\\  |" etc.
                    cardLines.push_back(suitLines[0]);
                    cardLines.push_back(suitLines[1]);
                    // bottom of card should show the raw edge as requested: `------'
                    cardLines.push_back("|______|'");

                    // Normalize each line to a fixed width to avoid cutting off bottoms/columns
                    auto normalize = [](const std::string &s, size_t w) {
                        if (s.size() >= w) return s.substr(0, w);
                        // If line starts and ends with '|' keep edges and pad inner content
                        if (s.size() >= 2 && s.front() == '|' && s.back() == '|') {
                            std::string inner = s.substr(1, s.size() - 2);
                            if (inner.size() < w - 2) inner += std::string((w - 2) - inner.size(), ' ');
                            return std::string("|") + inner + std::string("|");
                        }
                        // Otherwise pad on the right
                        return s + std::string(w - s.size(), ' ');
                    };

                    for (auto &ln : cardLines) ln = normalize(ln, 8);

                    asciiCards.push_back(cardLines);
                }

                // Print cards side-by-side in chunks so lines don't wrap in narrow terminals
                if (!asciiCards.empty()) {
                    const int rows = (int)asciiCards[0].size();
                    const size_t cardsPerRow = 8; // adjust if you want more/less per output row
                    size_t start = 0;
                    while (start < asciiCards.size()) {
                        size_t end = std::min(start + cardsPerRow, asciiCards.size());
                        for (int r = 0; r < rows; ++r) {
                            for (size_t c = start; c < end; ++c) {
                                std::cout << asciiCards[c][r] << " ";
                            }
                            std::cout << std::endl;
                        }
                        start = end;
                    }
                }
            }

            std::cout << "Waiting for your move... ";
            std::string move;
            std::cin >> move;


        }
        

    }
}

void GameOfTarneeb::handOutCards() {
    int handoutCardAmount = 14;

    for (int i = 0; i < playerCount; i++) {
        handoutCardAmount = players[i].getPlayerNum() == currTurn ? 15:14;

        for (int j = 0; j < handoutCardAmount; j++) {
            players[i].addCard(cards->at(0));
            cards->erase(cards->begin());
        }
    }
}

void GameOfTarneeb::cycleTurn() {
    currTurn = currTurn++ % playerCount;
}

std::vector<std::string>& GameOfTarneeb::getSpentCards() {
    return spentCards;
}




