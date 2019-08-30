#include <cstdint>   //to access fixed-width integers
#include <cstdlib>   //to access rand and srand
#include <ctime>     //for "time" function
#include <iostream>  //for cin and cout

// Libraries from C that are still useful in C++ were given a "c" prefix.
// stdlib.h became cstdlib

short togglePlayer(short player);
void printWelcome();

int main() {
        srand(time(NULL));

        int dieValue{(rand() % 6) + 1};
        short player{0};
        int totalPlayer1{0};
        int totalPlayer2{0};
        int partialValue{0};
        int choice{0};

        printWelcome();

        while (true) {
                std::cout << "1 - Throw\n2 - Stand\n";
                std::cin >> choice;

                if (choice == 1) {
                        dieValue = (rand() % 6) + 1;
                        partialValue += dieValue;
                }
        }

        return 0;
}

short togglePlayer(short player) {
        if (player)
                return 0;
        else
                return 1;
}
