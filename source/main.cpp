// TODO: Main switching players bug fix
#include <cstdint>   //to access fixed-width integers
#include <cstdlib>   //to access rand and srand
#include <ctime>     //for "time" function
#include <iostream>  //for cin and cout

// Not using OOP Classes because I'm using this project to test my skills using
// structs and enums

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
// void togglePlayer(Player turnPlayer); //pointers or reference needed
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
/**
 * Function that prints a player's information with a nice format
 *
 * @param player the player to print information from
 */
void printPlayerInfo(Player player);

int main() {
        // random seed according to system time
        std::srand(std::time(NULL));

        // There is no need for an initial die value, so I'm just using a zero
        // initialization here
        int dieValue{};
        // Variable that will hold the choice for the round (Throw or Stand)
        int choice{0};
        // Initializing both players
        Player player1{PlayerNumber::ONE};
        Player player2{PlayerNumber::TWO};

        // Player with the turn. At the beginning it is Player ONE
        Player turnPlayer{player1};

        printWelcome();

        // The end condition of the while loop is if someone gets the total
        // score to be 100 or higher (which means "continue with the loop until
        // there is a winner")
        while (player1.totalScore < 100 || player2.totalScore < 100) {
                // just an extra newline here for more vertical space
                std::cout << '\n';

                printPlayerInfo(turnPlayer);

                std::cout << "\n1 - Throw\n2 - Stand\n";
                std::cin >> choice;

                if (choice == 1) {
                        // once the user chooses to throw a dice, the die value
                        // should now be assigned a random value.
                        dieValue = (std::rand() % 6) + 1;

                        std::cout << "The value shown is " << dieValue << '\n';

                        if (dieValue == 1) {
                                turnPlayer.partialScore = 0;
                                std::cout << "Skipping turn\n";
                                // Now all we have to do is switch players
                                // replace this with togglePlayer(turnPlayer);
                                // once it is ready to be used
                                if (turnPlayer.number == PlayerNumber::ONE)
                                        turnPlayer = player2;
                                else
                                        turnPlayer = player1;
                        } else {
                                // once the die has been thrown and its value
                                // isn't 1, add its value to the partial score
                                turnPlayer.partialScore += dieValue;
                                std::cout << "Added to partial score\n";
                        }
                }
                // considering anything else to mean "Stand"
                else {
                        // if the player stands, then he gets all the score he
                        // gathered by now
                        turnPlayer.totalScore += turnPlayer.partialScore;
                        // and of course after doing this we have to reset his partial
                        // score
                        turnPlayer.partialScore = 0;

                        // Now all we have to do is switch turnPlayers
                        std::cout << "Switching players\n";
                        // replace this with togglePlayer(turnPlayer); once it
                        // is ready to be used
                        if (turnPlayer.number == PlayerNumber::ONE)
                                turnPlayer = player2;
                        else
                                turnPlayer = player1;
                }
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

#if 0
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
#endif
void printWelcome() { std::cout << "\tDice Game\n\n"; }
void printPlayerInfo(Player player) {
        std::cout << "player" << getPlayerNumber(player)
                  << " (Total: " << player.totalScore
                  << "; Partial: " << player.partialScore << ")";
}
