#include "../Headers/GameOfTarneeb.h"

GameOfTarneeb::GameOfTarneeb(int playerCount) {
    this->playerCount = playerCount;
    deck = Deck();

    for (int i = 0; i < playerCount; i++) {
        players.push_back(Players(i));
    }

    cards = &deck.getCards();        
}

void GameOfTarneeb::startGame() {
    deck.shuffleCards();
    handOutCards();

    std::cout << "Handing out cards";
    for (int i = 0; i < 3; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << ".";
    }
    
    std::cout << "\nHAND: " << std::endl;
    printCards();

    std::cout << "Probability of winning with his hand \n" << std::endl;
    std::cout << "≈ " << calculateWinProbability(players[0].getPlayerHand(), 1000) << " chance\n";
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

void GameOfTarneeb::printCards() {
    int handoutCardAmount = players[0].getPlayerNum() == currTurn ? 15:14;
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
                else rankStr = token; 
                numValue = token;
            } else {
                if (token == "Spades") suitStr = deck.getSuit(Suits::SPADE);
                else if (token == "Hearts") suitStr = deck.getSuit(Suits::HEART);
                else if (token == "Diamonds") suitStr = deck.getSuit(Suits::DIAMOND);
                else if (token == "Clubs") suitStr = deck.getSuit(Suits::CLOVER);
            }
        }

        std::vector<std::string> suitLines;
        std::istringstream sss(suitStr);
        std::string line;
        while (std::getline(sss, line)) {
            if (!line.empty()) suitLines.push_back(line);
        }
        while (suitLines.size() < 2) {
            suitLines.push_back(std::string("|      |"));
        }

        std::vector<std::string> cardLines;
        cardLines.push_back(".------.");

        if (rankStr == "10") {
            cardLines.push_back("|10    |");
        }
        else if (!rankStr.empty()) {
            cardLines.push_back(std::string("|") + rankStr + "     |");
        } else {
            cardLines.push_back("|?     |");
        }

        cardLines.push_back(suitLines[0]);
        cardLines.push_back(suitLines[1]);
        cardLines.push_back("|______|'");

        auto normalize = [](const std::string &s, size_t w) {
            if (s.size() >= w) {
                return s.substr(0, w);
            }
            if (s.size() >= 2 && s.front() == '|' && s.back() == '|') {
                std::string inner = s.substr(1, s.size() - 2);
                if (inner.size() < w - 2) inner += std::string((w - 2) - inner.size(), ' ');
                return std::string("|") + inner + std::string("|");
            }
            return s + std::string(w - s.size(), ' ');
        };

        for (auto &ln : cardLines) {
            ln = normalize(ln, 8);
        }

        asciiCards.push_back(cardLines);
    }

    if (!asciiCards.empty()) {
        const int rows = (int)asciiCards[0].size();
        const size_t cardsPerRow = 8; 
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

double GameOfTarneeb::calculateWinProbability(const std::vector<std::string>& handStrings, int trials) {
    std::map<std::string, int> cardValues = {
        {"Ace",10},{"King",10},{"Queen",10},{"Jack",10},{"10",10},
        {"9",9},{"8",8},{"7",7},{"6",6},{"5",5},{"4",4},{"3",3},{"2",2}
    };

    std::vector<std::pair<std::string,std::string>> baseHand;
    for (auto &card : handStrings) {
        std::istringstream iss(card);
        std::string rank, suit;
        std::string token;
        while (iss >> token) {
            if (token=="Spades"||token=="Hearts"||token=="Diamonds"||token=="Clubs")
                suit = token;
            else rank = token;
        }
        baseHand.emplace_back(rank, suit);
    }

    std::vector<std::string> ranks = {"Ace","King","Queen","Jack","10","9","8","7","6","5","4","3","2"};
    std::map<std::string,int> rankIndex;
    for (int i=0;i<(int)ranks.size();++i) rankIndex[ranks[i]]=i;

    auto maxMeldValue = [&](const std::vector<std::pair<std::string,std::string>>& cards){
        int total=0;
        std::map<std::string,std::vector<int>> rankPos;
        for (int i=0;i<(int)cards.size();++i)
            rankPos[cards[i].first].push_back(i);
        for (auto &kv:rankPos){
            if (kv.second.size()>=3){
                total += 3 * cardValues[kv.first];
            }
        }
        std::map<std::string,std::vector<int>> suitPos;
        for (int i=0;i<(int)cards.size();++i)
            suitPos[cards[i].second].push_back(i);
        for (auto &kv:suitPos){
            auto idxs = kv.second;
            std::sort(idxs.begin(),idxs.end(),[&](int a,int b){
                return rankIndex.at(cards[a].first)<rankIndex.at(cards[b].first);
            });
            int run=1;
            for (int j=1;j<(int)idxs.size();++j){
                if (rankIndex.at(cards[idxs[j]].first)==rankIndex.at(cards[idxs[j-1]].first)+1)
                    ++run;
                else run=1;
                if (run>=3){
                    total += cardValues[cards[idxs[j]].first]
                           + cardValues[cards[idxs[j-1]].first];
                }
            }
        }
        return total;
    };

    std::vector<std::pair<std::string,std::string>> deck;
    for (auto &r:ranks){
        for (std::string s:{"Spades","Hearts","Diamonds","Clubs"}){
            deck.emplace_back(r,s);
        }
    }

    std::mt19937 rng(std::random_device{}());
    int success=0;
    for (int t=0;t<trials;++t){
        std::shuffle(deck.begin(), deck.end(), rng);
        std::vector<std::pair<std::string,std::string>> hand(deck.begin(), deck.begin()+15);
        int best=0;
        for (int d=0; d<15; ++d){
            std::vector<std::pair<std::string,std::string>> h;
            for (int i=0;i<15;++i) if (i!=d) h.push_back(hand[i]);
            int val = maxMeldValue(h);
            best = std::max(best, val);
        }
        if (best>=52) ++success;
    }

    return static_cast<double>(success) / trials;
}
