#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

bool keepPlaying = true;

vector<string> playerHand;
vector<string> dealerHand;

int playerHandCount = 0;
int dealerHandCount = 0;
int playerAces = 0;
int dealerAces = 0;
int tempCard;
int balance;
int bet;

int dealCard(int&, int&, int&);
void startGame(int&);
void startBet(int&, int&);
void convertCard(vector<string>&, int&);
void printHandsFirst(vector<string>, vector<string>);
void hitOrStay(int&, int&, int&, vector<string>&);
void dealerPlay(int&, int&, int&, vector<string>&);
void compareCards(int, int, int, int&);
void keepPlayingQuestion(bool&, int);


int main()
{

    srand(time(NULL));

    startGame(balance);

    do{
        startBet(balance, bet);

        //Player Cards
        dealCard(playerHandCount, playerAces, tempCard);
        convertCard(playerHand, tempCard);
        dealCard(playerHandCount, playerAces, tempCard);
        convertCard(playerHand, tempCard);

        //Dealer Cards
        dealCard(dealerHandCount, dealerAces, tempCard);
        convertCard(dealerHand, tempCard);
        dealCard(dealerHandCount, dealerAces, tempCard);
        convertCard(dealerHand, tempCard);

        printHandsFirst(dealerHand, playerHand);

        hitOrStay(playerHandCount, playerAces, tempCard, playerHand);

        dealerPlay(dealerHandCount, dealerAces, tempCard, dealerHand);

        compareCards(playerHandCount, dealerHandCount, bet, balance);

        if (balance != 0){
            keepPlayingQuestion(keepPlaying, balance);
        } else {
            cout << "\n You've gone broke! Come back with more money!" << endl;
            break;
        }

        playerHand.clear();
        dealerHand.clear();
        playerHandCount = 0;
        dealerHandCount = 0;
        playerAces = 0;
        dealerAces = 0;

    } while (keepPlaying);


    return 0;
}

void startGame(int& startBal)
{
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "|" << setfill(' ') << setw(34);
    cout << "Welcome to my Casino" << setw(15) << "|" <<endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "|" << setfill(' ') << setw(42);
    cout << "How much would you like to deposit?";
    cout << setw(7) << "|" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    cout << "\n Deposit Amount : $";
    cin >> startBal;

    if (cin.fail())
    {
        do
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n\nError: Not a valid deposit, please try again." << endl;
            cout << "\n Deposit Amount : $";
            cin >> startBal;
        } while (cin.fail());
    }
}

void startBet(int& balance, int& bet){
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "|" << setfill(' ') << setw(38);
    cout << "What would you like to bet?" << setw(11) << "|" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    cout << "\n Bet Amount : $";
    cin >> bet;

    if (bet > balance || cin.fail()){
        do
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n\nError: Not a valid bet amount, please try again." << endl;
            cout << "\n Bet Amount : $";
            cin >> bet;
        } while (bet > balance || cin.fail());
    }

    balance -= bet;
}

int dealCard(int& total, int& aces, int& card){
    card = (rand()%11)+1;
    if (card == 1){
       total += 11;
        aces += 1;
    }else if (card == 11){
        total += card;
        aces += 1;
    } else {
        total += card;
    }
    return card;
}

void convertCard(vector<string>& hand, int& card){
    switch (card) {
        case 1:
        case 11:
            hand.push_back("[A]");
            break;
        case 2:
            hand.push_back("[2]");
            break;
        case 3:
            hand.push_back("[3]");
            break;
        case 4:
            hand.push_back("[4]");
            break;
        case 5:
            hand.push_back("[5]");
            break;
        case 6:
            hand.push_back("[6]");
            break;
        case 7:
            hand.push_back("[7]");
            break;
        case 8:
            hand.push_back("[8]");
            break;
        case 9:
            hand.push_back("[9]");
            break;
        case 10:
            hand.push_back("[K]");
            break;
    }
}

void printHandsFirst(vector<string> dHand, vector<string> pHand){
    cout << setfill('=') << setw(50) << "" << endl;
    cout <<  "| Dealer Hand : " << dHand[0] << " [X]";
    cout << setfill(' ') << setw(27) << "|" << endl;
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "| Your Hand : " << pHand[0] << " " << pHand[1];
    cout << setfill(' ') << setw(29) << "|" << endl;
    cout << setfill('=') << setw(50) << "" << endl;
}

void hitOrStay(int& total, int& aces, int& card, vector<string>& hand){
    char ans = 'h';
    while (ans != 's' || ans == 'S'){
        cout << "\n Hit or Stay? (h/s): ";
        cin >> ans;
        if (ans == 'h' || ans == 'H'){
            dealCard(total, aces, card);
            convertCard(hand, card);
            cout << " \nNew Hand : ";
            for (string i : hand){
                cout << i << " ";
            }
                if (total == 21){
                    cout << " \n Blackjack!!" << endl;
                    cout << "\nDealer Turn!" << endl;
                    break;
                } else if (total > 21){
                    if (aces > 0){
                        total -= 10;
                        aces -= 1;
                    } else {
                        cout << " \n BUST!!!" << endl;
                        cout << "\nDealer Turn!" << endl;
                        break;
                    }
                }
        } else if (ans == 's' || ans == 'S'){
            cout << "\nDealer Turn!" << endl;
        } else {
            cout << "\nThat is not a valid answer..." << endl;
        }
    }
}

void dealerPlay(int& total, int& aces, int& card, vector<string>& hand){
    cout << "\n Dealer Hand : ";
    for (string i : hand){
        cout << i << " ";
    }
    cout << endl;

    while (total < 17){
        dealCard(total, aces, card);
        convertCard(hand, card);
        cout << "\n Dealer Hand  : ";
            for (string i : hand){
                cout << i << " ";
            }
            cout << endl;

            if (total == 21){
                cout << " \n Blackjack!!" << endl;
                break;
            } else if (total > 21){
                if (aces > 0){
                    total -= 10;
                    aces -= 1;
                } else {
                    cout << "\n Dealer BUST!!!" << endl;
                    break;
                }
            }
    }
}

void compareCards(int playerHandCount, int dealerHandCount, int bet, int& balance){
    if (playerHandCount > dealerHandCount && playerHandCount <= 21){
        balance += (bet/2)*3;
        cout << "\n You Won : $"<< (bet/2)*3 << endl;
        cout << " New Balance : $" << balance << endl;
    } else if (playerHandCount < dealerHandCount && dealerHandCount <= 21){
        cout << "\n You Lose!!!" << endl;
        cout << " New Balance : $" << balance << endl;
    } else if (playerHandCount == dealerHandCount && playerHandCount <= 21){
        balance += bet;
        cout << "\n PUSH!!!" << endl;
        cout << " New Balance : $" << balance << endl;
    } else if (dealerHandCount > 21 && playerHandCount > 21){
        cout << "\n You Lose!!!" << endl;
        cout << " New Balance : $" << balance << endl;
    } else if (dealerHandCount > 21 && playerHandCount <= 21){
        balance += (bet/2)*3;
        cout << "\n You Won : $"<< (bet/2)*3 << endl;
        cout << " New Balance : $" << balance << endl;
    }
}

void keepPlayingQuestion(bool& ans, int balance){
    cout << setfill('=') << setw(50) << "" << endl;
    cout << "|" << setfill(' ') << setw(39);
    cout << "Would you like to keep playing?";
    cout << setw(10) << "|" << endl;
    cout << setfill('=') << setw(50) << "" << endl;

    bool answered = false;
    cout << "\n Keep Playing? (y/n) : ";
    char question;
    cin >> question;

    while (!answered){
        if (question == 'n' || question == 'N'){
            ans = false;
            answered = true;
            cout << "\nYou're walking out of here with $" << balance << endl;
        } else if (question == 'y' || question == 'Y'){
            ans = true;
            answered = true;
        } else {
            cout << "\nThat is not a valid answer..." << endl;
            cout << "\n Keep Playing? (y/n) : ";
            cin >> question;
        }
    }
}