// comment out system("clear") if you want it safe (and working on Windows)
#include <cstdint>   //to access fixed-width integers
#include <cstdlib>   //to access rand, srand and system("clear")
#include <ctime>     //for "time" function
#include <iostream>  //for cin and cout
#include <string>    //for std::string

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
 * A function that gets the PlayerNumber value as a string (instead of values
 * ONE and TWO, we get "ONE" and "TWO")
 *
 * @param player the player to get the number from
 * @return the player number as a string
 */
std::string getPlayerNumber(Player *player);
/**
 * Function that prints the welcome message on the screen
 */
void printWelcome();
/**
 * Function that prints a player's information with a nice format
 *
 * @param player the player to print information from
 */
void printPlayerInfo(Player *player);

int main() {
        // random seed according to system time
        std::srand(std::time(NULL));

        system("clear");

        // There is no need for an initial die value, so I'm just using a zero
        // initialization here
        int dieValue{};
        // Variable that will hold the choice for the round (Throw or Stand)
        int choice{};
        // Initializing both players
        Player player1{PlayerNumber::ONE};
        Player player2{PlayerNumber::TWO};

        // Player with the turn. At the beginning it is Player ONE
        Player *turnPlayer{&player1};

        printWelcome();

        // The end condition of the while loop is if someone gets the total
        // score to be 100 or higher (which means "continue with the loop until
        // there is a winner")
        while (true) {
                // just an extra newline here for more vertical space
                std::cout << '\n';

                printPlayerInfo(turnPlayer);

                // This feels awful
                if(turnPlayer == &player1)
                        std::cout << "\nThe other player has " << player2.totalScore << " points.";
                else
                        std::cout << "\nThe other player has " << player1.totalScore << " points.";

                std::cout << "\n1 - Throw\n2 - Stand (new total score will be "
                          << turnPlayer->totalScore + turnPlayer->partialScore
                          << ")\n";
                std::cin >> choice;

                // clearing the state and stream
                std::cin.clear();
                // 32767 because that's the largest signed value guaranteed to
                // fit in a (2-byte) integer on all platforms.
                std::cin.ignore(32767, '\n');

                system("clear");

                if (choice == 1) {
                        // once the user chooses to throw a dice, the die value
                        // should now be assigned a random value.
                        dieValue = (std::rand() % 6) + 1;

                        std::cout << "The value shown is " << dieValue << '\n';

                        if (dieValue == 1) {
                                turnPlayer->partialScore = 0;
                                std::cout << "Skipping turn\n";
                                // Now all we have to do is switch players
                                // replace this with togglePlayer(turnPlayer);
                                // once it is ready to be used
                                if (turnPlayer->number == PlayerNumber::ONE)
                                        turnPlayer = &player2;
                                else
                                        turnPlayer = &player1;
                        } else {
                                // We could do this here, so that the player
                                // doesn't need to decide to Stand anymore,
                                // because he already won. But I decided to not
                                // do this, so that players close to winning can
                                // choose to taunt the other player.
                                //
                                // if ( (turnPlayer->partialScore + dieValue +
                                // turnPlayer->totalScore) >= 100)
                                //       break;

                                // once the die has been thrown and its value
                                // isn't 1, add its value to the partial score
                                turnPlayer->partialScore += dieValue;
                                std::cout << "Added to partial score\n";
                        }
                }
                // considering anything else to mean "Stand"
                else {
                        // if the player stands, then he gets all the score he
                        // gathered by now
                        turnPlayer->totalScore += turnPlayer->partialScore;

                        // if it happens that the player's score is now >= 100,
                        // there is already a winner. Nothing more needed to be
                        // done here.
                        if (turnPlayer->totalScore >= 100) break;
                        // and of course after doing this we have to reset his
                        // partial score
                        turnPlayer->partialScore = 0;

                        // Now all we have to do is switch turnPlayers
                        std::cout << "Switching players\n\n";
                        // replace this with togglePlayer(turnPlayer); once it
                        // is ready to be used
                        if (turnPlayer->number == PlayerNumber::ONE)
                                turnPlayer = &player2;
                        else
                                turnPlayer = &player1;
                }
        }

        // announcing the winner
        std::cout << "Player " << getPlayerNumber(turnPlayer) << " wins with "
                  << turnPlayer->totalScore << " points!\n";

        // temporary variable to store the winner's score to compare it tho the
        // loser's.
        int tmp{turnPlayer->totalScore};

        // replace this with togglePlayer(turnPlayer); once it
        // is ready to be used
        if (turnPlayer->number == PlayerNumber::ONE)
                turnPlayer = &player2;
        else
                turnPlayer = &player1;

        // announcing the loser and the score difference from both players.
        std::cout << "Player " << getPlayerNumber(turnPlayer) << " lost with "
                  << turnPlayer->totalScore << " points. A difference of "
                  << tmp - turnPlayer->totalScore
                  << " points from the winner!\n";

        return 0;
}

std::string getPlayerNumber(Player *player) {
        // Return the appropriate string. If it isn't found, return "UNDEFINED"
        switch (player->number) {
                case PlayerNumber::ONE:
                        return "ONE";
                case PlayerNumber::TWO:
                        return "TWO";
                default:
                        return "UNDEFINED";
        }
}

void printWelcome() { std::cout << "\tDice Game\n\n"; }
void printPlayerInfo(Player *player) {
        std::cout << "Player " << getPlayerNumber(player)
                  << " (Total: " << player->totalScore
                  << "; Partial: " << player->partialScore << ")";
}
