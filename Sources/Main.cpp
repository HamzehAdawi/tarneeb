#include <iostream> 
#include "../Headers/GameOfTarneeb.h"

int main() {
    std::cout << " _______       _____  _   _ ______ ______ ____  " << std::endl;
    std::cout << "|__   __|/\\   |  __ \\| \\ | |  ____|  ____|  _ \\ " << std::endl;
    std::cout << "   | |  /  \\  | |__) |  \\| | |__  | |__  | |_) |" << std::endl;
    std::cout << "   | | / /\\ \\ |  _  /| . ` |  __| |  __| |  _ < " << std::endl;
    std::cout << "   | |/ ____ \\| | \\ \\| |\\  | |____| |____| |_) |" << std::endl;
    std::cout << "   |_/_/    \\_\\_|  \\_\\_| \\_|______|______|____/ " << std::endl;

    while (true) {    
        std::cout << "\ns - Start Game, q - Quit" << std::endl;
        std::string input; 
        std::cin >> input;

        if (input != "q" && input != "s") {
            std::cout << "Invalid input." << std::endl;
        }
        else if (input == "q") {
            return 0;
        }
        else if (input == "s") {
            break;
        }
    }

    GameOfTarneeb game = GameOfTarneeb(3);
    game.startGame();

    
}