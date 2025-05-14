// Author: Adam Maciaszek
#include "Blackjack.h"

// initializes variables
Blackjack::Blackjack(){
    std::string players[3] = {"Null", "Player", "Dealer"};
    value = 0;
    has_ace = false;
    position = 0;
    dealer_value = 0;
    player_value = 0;
    player_ace = 0;
    dealer_ace = 0;
}

// creates a 52 card deck by combining suits and ranks
void Blackjack::Create_Deck(){
    const int RANK_SIZE = 13;
    const int SUIT_SIZE = 4;
    for (int i = 0; i < RANK_SIZE; ++i){
        for (int j = 0; j < SUIT_SIZE; ++j){
            std::string card;
            card = rank[i] + suit[j];
            Deck.push_back(card);
        }
    }
}

// shuffles the 52 card deck 312 times as a typical Blackjack dealer would have 312 cards in a deck
void Blackjack::shuffle(){
    srand(time(0));
    const int NUM_SWAPS = 312;

    for (int i = 0; i < NUM_SWAPS; i++){
        int random_index_1 = rand() % Deck.size();
        int random_index_2 = rand() % Deck.size();

        std::string Temp = Deck[random_index_1];
        Deck[random_index_1] = Deck[random_index_2];
        Deck[random_index_2] = Temp;
    }
}

// Draws a card from the top of the deck using FIFO/ a queue
std::string Blackjack::Draw_Card(){
    player_card = Deck[position];
    position++;
    return player_card;
}



bool Blackjack::Hit(){
    return true;
}



int Blackjack::Get_Value(std::string player_card, int &ace_count){
    std::string player_rank = player_card.substr(0, 1);
    if (player_rank == "A"){ace_count++; return 11;}
    if (player_rank == "K"){return 10;}
    if (player_rank == "Q"){return 10;}
    if (player_rank == "J"){return 10;}
    if (player_rank == "T"){return 10;}
    return stoi(player_rank);
}



void Blackjack::Hand_Value(std::vector<std::string> player_deck, int &player_value, int ace_count){
    player_value = 0; // resets value everytime it is calculated
    ace_count = 0;
    for (int i = 0; i < player_deck.size(); i++){
        player_value += Get_Value(player_deck[i], ace_count);
    }
    while (ace_count > 0 && player_value > 21){
        player_value -= 10;
        ace_count--;
    }
}

int Blackjack::winner(){
    if ((player_value > dealer_value) && player_value < 22){
        return 1;
    }
    if ((player_value == 21) && Player.size() == 2){
        return 1;
    }
    if ((dealer_value == 21) && Dealer.size() == 2){
        return 2;
    }
    if ((dealer_value > player_value) && dealer_value < 22){
        return 2;
    }
    return 0;
}

bool Blackjack::gameover(){
    if (player_value == 21 && Player.size() == 2){
        std::cout << "Blackjack!" << std::endl;
        return true;
    }
    if (dealer_value == 21 && Dealer.size() == 2){
        std::cout << "The dealer got a blackjack!" << std::endl;
        return true;
    }
    if ((dealer_value >= 21) || (player_value >= 21)){
        std::cout << "gameover" << std::endl;
        return true;
    }
    if (winner() == 1 || winner() == 2){
        std::cout << "gameover" << std::endl;
        return true;
    }
    return false;
}

std::string Blackjack::to_lower(std::string &input){
    std::string string = input;
    std::string letter;
    input = "";
    for (int i = 0; i < string.length(); i++){
        letter = tolower(string[i]);
        input += letter;
    }
    return input;
}


void Blackjack::play(){
    Create_Deck();
    shuffle();
    bool play_again = true;

    while (!gameover()){
        bool full = false;
        while (!full){
            Player.push_back(Draw_Card());
            Dealer.push_back(Draw_Card());
            if (Dealer.size() == 2){
                full = true;
            }

        }
        Hand_Value(Player, player_value, player_ace);
        Hand_Value(Dealer, dealer_value, dealer_ace);
        bool stand = false;
        while (!stand){
            std::cout << "Your hand: ";
            for (int i = 0; i < Player.size(); ++i){
                std::cout << Player[i] << "\t";
            }

            Hand_Value(Player, player_value, player_ace);
            gameover();
            winner();

            std::cout << std::endl << "Hand value: " << player_value << std::endl;

            std::string choice;
            std::cout << std::endl << "Dealer's card: " << Dealer[0] << Dealer[1];
            std::cout << std::endl << "Would you like to hit or stand?" << std::endl;
            std::cin >> choice;
            to_lower(choice);
            if (choice == "hit"){
                Player.push_back(Draw_Card());
            }
            if (choice == "stand"){
                stand = true;
            }
        }
        while (dealer_value <= 16){ // dealer hits for 16 and below and stands on 17 or above
            Hand_Value(Dealer, dealer_value, dealer_ace);
            }
            Dealer.push_back(Draw_Card());
        }
        std::cout << "Dealer value: " << dealer_value << std::endl;
        std::cout << "Dealer hand: ";
        for (int i = 0; i < Dealer.size(); ++i){
                std::cout << Dealer[i] << "\t";
        }
        std::cout << std::endl;

    // std::string play_choice;
    // std::cout << "The winner is: " << winner() << std::endl;
    // std::cout << "Would you like to play again? (yes/no) ";
    // std::cin >> play_choice;
    // if (play_choice == "yes"){
    //     play_again == true;
    // }
    // if (play_choice == "no"){
    //     play_again = false;
    // }
}


int main(){
    Blackjack Game;
    Game.play();
    return 0;
}
