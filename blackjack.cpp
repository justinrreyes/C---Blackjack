#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;

bool pWin = false;
bool dWin = false;

string name;
char answer;
char questionAns = 'y';
int blackjack = 21;
int playerHand = 0;
int dealerHand = 0;
int dealerAces = 0;
int playerAces = 0;
int playerC1;
int playerC2;
int dealerC1;
int dealerC2;
int tempPlayerC;
int tempDealerC;
int deposit;
int balance;
int bet;

string getPlayerInfo(string&, int&);
int getPlayerBet(int&, int&);
int dealCards(int&, int&, int&, int&);
int dealerPlay(int&, int&, int&, bool);
bool compareCards(bool&, bool&, int, int);
int hitOrStay(int&, int&, int&);
void WinOrLose(int&, int&); 
void cardConvert(int);
void showCards();

//cout << (rand()%11)+1;

int main()
{
    // Generates random number seed
    srand(time(NULL));

    getPlayerInfo(name, deposit);

    balance = deposit;

    do{
        getPlayerBet(balance, bet);

        dealCards(playerHand, playerC1, playerC2, playerAces);
        dealCards(dealerHand, dealerC1, dealerC2, dealerAces);

        showCards();

        if (playerHand == 21){
            cout << "BLACKJACK!!!" << endl;
        } else {
                do{
                    hitOrStay(tempPlayerC, playerHand, playerAces);
                    if (playerHand > 21){
                        if (playerAces > 0){
                            playerHand -= 10;
                            playerAces -= 1;
                            cout << " NEW TOTAL: " << playerHand;
                            if (playerHand == 21){
                                cout << "\n\nBLACKJACK!!!" << endl << endl;
                                break;
                            }
                        } else {
                            cout << "\n\nBUST!!!" << endl << endl;
                            break;
                        }
                    } else if (playerHand == 21){
                        cout << "\n\nBLACKJACK!!!" << endl << endl;
                        break;
                    }
                } while (answer != 's');
        }

        dealerPlay(dealerHand, tempDealerC, dealerAces, dWin);

        compareCards(dWin, pWin, playerHand, dealerHand);

        WinOrLose(bet, balance);

        cout << "\nYour New Balance is : $" << balance << endl;

        if (balance <= 0){
            cout << "\nSORRY YOU ARE BROKE! Come back again when you have more money!" << endl;
            break;
        }

        cout << "Would you like to continue? y/n : ";
        cin >> questionAns;
    } while (questionAns == 'y');

    


return 0;

}


string getPlayerInfo(string& name, int& deposit){
    cout << setfill('=') << setw(60) << "" << endl;
    cout << setfill(' ') << setw(10) << "" << "Welcome to My Casino! What is your name?" << endl;
    cout << setfill('=') << setw(60) << "" << endl << endl;
    cout << "Please enter your name: ";
    getline(cin, name);
    cout << endl;

    cout << setfill('=') << setw(60) << "" << endl;
    cout << "Welcome " << name << ", and how much would you like to deposit?" << endl;
    cout << setfill('=') << setw(60) << "" << endl << endl;
    cout << "Please enter your deposit amount: ";
    cin >> deposit;
    cout << endl;

    cout << setfill('=') << setw(60) << "" << endl;
    cout << "Excellent! Let's get the game started!" << endl;
    cout << setfill('=') << setw(60) << "" << endl << endl;

    return name;

}

int getPlayerBet(int& balance, int& bet){
    bool validBet = false;
    cout << setfill('=') << setw(60) << "" << endl;
    cout << "How much would you like to bet?" << endl;
    cout << setfill('=') << setw(60) << "" << endl << endl;
    cout << "Please enter bet amount: ";
    
    do{
        cin >> bet;
        if (bet > balance){
            cout << "You do not have enough money for that!" << endl;
            cout << "How much do you ACTUALLY want to bet? ";
        } else {
            validBet = true;
        }
    } while (!validBet);

    balance -= bet;

    cout << endl;
    cout << setfill('=') << setw(60) << "" << endl;
    cout << "OK! Betting $" << bet << ", Best of Luck!" << endl;
    cout << setfill('=') << setw(60) << "" << endl << endl;

    return bet;
}

int dealCards(int& hand, int& c1, int& c2, int& aces){
    c1 = (rand()%11)+1;
    c2 = (rand()%11)+1;
    hand = c1 + c2;

    if (c1 == 1 || c2 == 1){
        aces += 1;
        hand += 10;
    } else if (c1 == 11 || c2 == 11){
        aces += 1;
    }

    return hand;
}

void cardConvert(int card){
    switch (card) {
        case 1:
        case 11:
            cout << "[A]";
            break;
        case 2:
            cout << "[2]";
            break;
        case 3:
            cout << "[3]";
            break;
        case 4:
            cout << "[4]";
            break;
        case 5:
            cout << "[5]";
            break;
        case 6:
            cout << "[6]";
            break;
        case 7:
            cout << "[7]";
            break;
        case 8:
            cout << "[8]";
            break;
        case 9:
            cout << "[9]";
            break;
        case 10:
            cout << "[10]";
            break;
    }
}

void showCards(){
    cout << "Dealer Hand : ";
    cardConvert(dealerC1);
    cout << " "; 
    cardConvert(dealerC2);
    cout << endl << endl;


    cout << name << "'s Hand : ";
    cardConvert(playerC1);
    cout << " ";
    cardConvert(playerC2);
    cout << endl << endl;
}

int hitOrStay(int& card, int& hand, int& aces){
    cout << "\nHit [h] or Stay [s]? : ";
    cin >> answer;
    cout << endl;
    if (answer == 'h'){
        card = (rand()%11)+1;
        if (card == 1){
            hand += 11;
            aces += 1;
        } else if (card == 11){
            hand += card;
            aces += 1;
        } else {
            hand += card;
        }
        cardConvert(card);
        cout << " Total: " << hand;
    }
    return card;
}

void WinOrLose(int& bet, int& balance){
    if (pWin && !dWin){
        cout << "\nCongratulations, You Won!" << endl;
        balance += (bet/2)*3;
    } else if (pWin && dWin){
        cout << "\nPUSH!" << endl;
        balance += bet;
    } else {
        cout << "\nSorry you lost!" << endl;
    }
}

int dealerPlay(int& hand, int& card, int& aces, bool dWin){
    cout << "Dealers Turn: " << endl << endl;
    do{
        card = (rand()%11)+1;
        hand += card;
        cardConvert(card);
    } while (hand < 16);
    if (hand > 21 && aces <= 0){
        cout << " Total: " << hand << endl;
        cout << "Dealer BUST!!!" << endl;
    } else if (hand > 21 && aces > 0){
        hand -= 10;
        aces -= 1;
        cout << "Dealer New Total: " << hand << endl;
    } else if (hand == 21){
        cout << " Total: " << hand << endl;
        cout << "Dealer BLACKJACK!!!" << endl;
    }
    cout << "\nDealer Total : " << hand << endl;
    return dWin;
}

bool compareCards(bool& dWin, bool& pWin, int pHand, int dHand){
    if (pHand > dHand && pHand <= 21){
        pWin = true;
        dWin = false;
    } else if (dHand > pHand && dHand <= 21){
        pWin = false;
        dWin = true;
    } else if (dHand == pHand && dHand <= 21){
        dWin = true;
        pWin = true;
    } else if (dHand > 21 && pHand > 21){
        dWin = false;
        pWin = false;
    }
    return pWin;
}