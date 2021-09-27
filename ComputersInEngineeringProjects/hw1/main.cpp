/***************************************************
 * Creator: Rafael Rangel                          *
 * Date: 2/10/2021                                 *
 * Project Name: hw1                               *
 * Description: Basic blackjack Dice game          *
 * Input: User commands                            *
 * Output: print statements                        *
 ***************************************************/

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int diceRoll();

int main() {
string playAgain = "1";

    cout << "-------------------------------------Dice Blackjack game--------------------------------------" << endl
         << "Rules: You start by rolling two six sided dice, after you roll, the number on the dice that is" << endl
         << "facing up will be added to you total points, you can choose to stay or roll again. If your    " << endl
         << "current score is greater or equal to 17, then you can only role one dice. If your total number" << endl
         << "is over 21, then you lose and the game ends. " << endl
         << "How to win: you will play against the dealer who will roll two six sided dice and count the " << endl
         << "same way you do, he will roll until his total is greater or equal to 17. You WIN if you total " << endl
         << "is greater than the dealer\'s, you LOSE if the your total is less than the dealer\'s total or if "
         << endl
         << "both totals are 21, you end in a TIE if both your total\'s are the same and not 21." << endl;

    while (playAgain == "1") {
        srand(time(0));

        enum GameState {
            GS_PLAYER_TURN, GS_DEALER_TURN, GS_COMPARISON_DECISION, GS_AUTOMATIC_WIN, GS_AUTOMATIC_LOSE,
            GS_TIE, GS_GAME_OVER
        };
        GameState gameStage;

        int playerTotal = 0;
        int dealerTotal = 0;

        gameStage = GS_PLAYER_TURN;

        string control;
        string explanation; //1

        cout << "---------------------------------------Game Starts---------------------------------------------"<< endl;
        while (gameStage != GS_GAME_OVER) {
            //stage 1
            if (gameStage == GS_PLAYER_TURN) {

                if (playerTotal < 17) {
                    int playerDice = diceRoll();
                    cout << "Dice 1 is " << playerDice << endl;
                    int playerDice1 = diceRoll();
                    cout << "Dice 2 is " << playerDice1 << endl;
                    playerTotal += playerDice + playerDice1;
                    cout << "Your total is  " << playerTotal << endl;
                }
                else if (playerTotal >= 17 && playerTotal < 21)
                {
                    int playerDice = diceRoll();
                    cout << "Dice is " << playerDice << endl;
                    playerTotal += playerDice;
                    cout << "Your total is  " << playerTotal << endl;
                }
                else if (playerTotal == 21)
                {
                    gameStage = GS_DEALER_TURN;
                }
                else if (playerTotal > 21)
                {
                    gameStage = GS_AUTOMATIC_LOSE;
                    explanation = "because you automatically lost by exceeding 21, the dealer didn't even have to play:( ";
                }

                if (playerTotal < 21)
                {
                    cout << "Press 1 to roll again, or 0 to stay" << endl;
                    cin >> control;
                }

                while (control != "0" && control != "1")
                {
                    cout << "Invalid input. Please enter a 1 (to roll again) or a 0 (to stay)" << endl;
                    cin >> control;
                }

                if (control == "0")
                {
                    gameStage = GS_DEALER_TURN;
                }
            }
            //stage 2
            else if (gameStage == GS_DEALER_TURN)
            {
                if (dealerTotal < 17)
                {
                    int dealerDice = diceRoll();
                    cout << "Dice 1 for the dealer is " << dealerDice << endl;
                    int dealerDice1 = diceRoll();
                    cout << "Dice 2 for the dealer is " << dealerDice1 << endl;
                    dealerTotal += dealerDice + dealerDice1;
                    cout << "Dealer\'s total is  " << dealerTotal << endl;
                }
                else if (dealerTotal >= 17 && dealerTotal < 21)
                {
                    gameStage = GS_COMPARISON_DECISION;
                }
                else if (dealerTotal == 21)
                {
                    gameStage = GS_AUTOMATIC_LOSE;
                    explanation = "since the dealer had a total of 21 ";
                }
                else if (dealerTotal > 21)
                {
                    gameStage = GS_AUTOMATIC_WIN;
                    explanation = " because the dealer exceeded 21 ";
                }
            }
            else if (gameStage == GS_COMPARISON_DECISION)
            {
                if (playerTotal > dealerTotal)
                {
                    gameStage = GS_AUTOMATIC_WIN;
                    explanation = "because you had a greater total than the dealer ";
                }
                else if (playerTotal == dealerTotal)
                {
                    gameStage = GS_TIE;
                }
                else if (playerTotal < dealerTotal)
                {
                    gameStage = GS_AUTOMATIC_LOSE;
                    explanation = "because the dealer had a greater total than you ";
                }

            }
            //stage 3
            else if (gameStage == GS_AUTOMATIC_WIN)
            {
                cout << "Congratulations!, you have won the game " << explanation << endl;
                gameStage = GS_GAME_OVER;
            }
            //stage 4
            else if (gameStage == GS_AUTOMATIC_LOSE)
            {
                cout << "Uff, you have lost the game " << explanation << "better luck next time" << endl;
                gameStage = GS_GAME_OVER;
            }
            //stage 5
            else if (gameStage == GS_TIE)
            {
                cout << "You both have the same total points so its a tie" << endl;
                gameStage = GS_GAME_OVER;
            }
        }

        cout << "----------------------------Stats summary---------------------------" << endl;
        cout << "player total is " << playerTotal << endl;
        if (dealerTotal == 0) {
            cout << "dealer didnt even have to play since player lost automatically" << endl;
        } else {
            cout << "dealer total is " << dealerTotal << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;

        cout << "If you wish to play again press 1, if you want to quit the program press any other letter or number" << endl;
        cin >> playAgain;
    }

    return 0;
}

//Function name: diceRoll
//input: none
//output: random number of int type ranging from 1 to six (dice simulator)
//description: function that simulates a dice roll
int diceRoll()
{
    int numberRolled;
    numberRolled = (rand() % 6) + 1;
    return numberRolled;
}