#include <cstdint>   //to access fixed-width integers
#include <cstdlib>   //to access rand and srand
#include <ctime>     //for "time" function
#include <iostream>  //for cin and cout

// Libraries from C that are still useful in C++ were given a "c" prefix.
// stdlib.h became cstdlib

// There are Player 1 and Player 2
enum class PlayerNumber {
        ONE,
        TWO,
};

// A player can have a total score and partial score (for the round)
struct Player {
        PlayerNumber number = PlayerNumber::ONE;
        int totalScore = 0;
        int partialScore = 0;
};

/**
 * A function that toggles the player. If the current player is Player ONE, then
 * it switches to Player TWO.
 *
 * @param player current player. Doing this because non-const global variables
 * are evil.
 */
void togglePlayer(Player player);
/**
 * A function that gets the PlayerNumber value as a string (instead of values
 * ONE and TWO, we get "ONE" and "TWO")
 *
 * @param player the player to get the number from
 * @return the player number as a string
 */
std::string getPlayerNumber(Player player);
/**
 * Function that prints the welcome message on the screen
 */
void printWelcome();

int main() {
        // random seed according to system time
        std::srand(std::time(NULL));

        // There is no need for an initial die value, so I'm just using a zero
        // initialization here
        int dieValue{};
        // Variable that will hold the choice for the round (Throw or Stand)
        int choice{0};
        // Initializing both players
        Player player{};

        printWelcome();

        while (true) {
                // end condition is if someone gets the total score to be 100 or
                // higher.
                if (player.totalScore >= 100) {
                        std::cout << "Player" << getPlayerNumber(player)
                                  << "wins!";
                        return 0;
                }

                std::cout << "1 - Throw\n2 - Stand\n";
                std::cin >> choice;

                if (choice == 1) {
                        // once the user chooses to throw a dice, the die value
                        // should now be assigned a random value.
                        dieValue = (std::rand() % 6) + 1;

                        if (dieValue == 1)
                                player.partialScore = 0;
                        else
                                // once the die has been thrown and its value
                                // isn't 1, add its value to the partial score
                                player.partialScore += dieValue;
                }
                // considering anything else to mean "Stand"
                else {
                        // if the player stands, then he gets all the score he
                        // gathered by now
                        player.totalScore += player.partialScore;
                        // and of course after doing this we have to reset his
                        // score
                        player.partialScore = 0;
                }

                togglePlayer(player);
        }

        return 0;
}

std::string getPlayerNumber(Player player) {
        // Return the appropriate string. If it isn't found, return "UNDEFINED"
        switch (player.number) {
                case PlayerNumber::ONE:
                        return "ONE";
                case PlayerNumber::TWO:
                        return "TWO";
                default:
                        return "UNDEFINED";
        }
}

void togglePlayer(Player player) {
        // Switches the player types (if it is TWO, then it becomes ONE and vice
        // versa) by using a Switch statement
        switch (player.number) {
                case PlayerNumber::ONE:
                        player.number = PlayerNumber::TWO;
                        return;
                case PlayerNumber::TWO:
                        player.number = PlayerNumber::ONE;
                        return;
        }
}
