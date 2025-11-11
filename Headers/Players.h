#include <string>
#include <vector>

class Players {
    private:
        int playerNum;
        std::vector<std::string> hand;

    public:
        Players(int playerNum); 
        int getPlayerNum();
        std::vector<std::string> getPlayerHand();
        void addCard(std::string card);
        void discardCard(std::string card);
    
};