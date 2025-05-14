#include "Blackjack.h"


Blackjack::Blackjack(){
    value = 0;
    has_ace = false;

}

void Blackjack::Create_Deck(){
    for (int i = 0; i < rank.size(); ++i){
        for (int j = 0; j < suit.size(); ++j){
            std::string card;
            card = rank[i] + suit[j];
            Deck.push_back(card);
        }
    }
}

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

std::string Blackjack::Draw_Card(){
    int position = 0;
    player_deck.push_back(Deck[position]);
    position++;
    return player_deck;
}



bool Blackjack::Hit(){
    return true;
}

// int Blackjack::Get_Value(){
//     std::string player_rank = deck.substr(0, 1);
//     if (player_rank == "A"){value = 11; has_ace = true;}
//     else if (player_rank == "K"){value = 10;}
//     else if (player_rank == "Q"){value = 10;}
//     else if (player_rank == "J"){value = 10;}
//     else if (player_rank == "T"){value = 10;}
//     else {value = stoi(player_rank);}
//     return value;

// }

void Blackjack::play(){

    bool full = false;
    while (!full){
        Player.Draw_Card();
        Dealer.Draw_Card();
        if (Dealer.size() == 2){
            full = true;
        }

    }
    for (int i = 0; i < Player.size(); ++i){
        std::cout << "Your hand: " << Player[i];
    }

    std::string choice;
    std::cout << std::endl << "Would you like to hit or stand?" << std::endl;
    std::cin >> choice;

}