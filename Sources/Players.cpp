#include <string>
#include <vector>

class Players {
    private:
        int playerNum;
        std::vector<std::string> hand;

    public:
        Players(int playerNum) {
            this->playerNum = playerNum;
        }

        int getPlayerNum() {
            return playerNum;
        }

        std::vector<std::string> getPlayerHand() {
            return hand;
        }

        void setPlayerHand(std::vector<std::string> hand) {
            this->hand = hand;
        }

        void addCard(std::string card) {
            hand.push_back(card);
        }

        void discardCard(std::string card) {
            
        }
    

};