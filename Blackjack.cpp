// Author: Adam Maciaszek
#include "Blackjack.h"

// initializes variables
Blackjack::Blackjack(){
    position = 0;
    dealer_value = 0;
    user_value = 0;
    user_ace = 0;
    dealer_ace = 0;
    full = false;
    win = 0;
    loss = 0;
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
    std::string player_card = Deck[position];
    position++;
    return player_card;
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


//calculates the hand value and adjusts the value for aces
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

    if ((user_value > dealer_value) && user_value < 22 && full){
        return 1;
    }
    if (user_value == 21 && User.size() == 2){
        std::cout << "Blackjack" << std::endl;
        return 1;
    }
    if (dealer_value > 21 || user_value == 21){
        return 1;
    }
    if (dealer_value == 21 && Dealer.size() == 2){
        std::cout << "The dealer got a blackjack!" << std::endl;
        return 2;
    }
    if ((dealer_value > user_value) && dealer_value < 22 && full){
        return 2;
    }
    if (user_value > 21 || dealer_value == 21){
        return 2;
    }
    return 0;
}

bool Blackjack::gameover(){
    if (winner() == 1){
        return true;
    }
    if (winner() == 2){
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

void Blackjack::game_history(){
    std::ifstream fin("Game_History.txt");  
    if (fin){
        fin >> win >> loss;
    }
    fin.close();

    int result = winner();
    if (result == 1){win++;}
    if (result == 2){loss++;}
    std::cout << "Win / Loss = " << win << " / " << loss << std::endl;
    fin.close();
    std::ofstream fout("Game_History.txt");
    fout << win << std::endl << loss << std::endl;
    fout.close();
}


void Blackjack::play(){
    Create_Deck();
    shuffle();
    for (int i = 0; i < 2; i++){
        User.push_back(Draw_Card());
        Dealer.push_back(Draw_Card());
    }
    Hand_Value(User, user_value, user_ace);
    Hand_Value(Dealer, dealer_value, dealer_ace);
    bool stand = false;
    while (!stand && !gameover()){
        std::cout << "Your hand: ";
        for (int i = 0; i < User.size(); ++i){
            std::cout << User[i] << std::setw(2) << "";
        }

        std::cout << std::endl << "Hand value: " << user_value << std::endl;

        std::string choice;
        std::cout << std::endl << "Dealer's card: " << Dealer[0];
        std::cout << std::endl << "Would you like to hit or stand?" << std::endl;
        std::cin >> choice;
        to_lower(choice);
        if (choice == "hit"){
            User.push_back(Draw_Card());
            Hand_Value(User, user_value, user_ace);
        }
        if (choice == "stand"){
            stand = true;
        }
    }
    if (user_value < 21){//dealer should not draw any cards if the player gets a blackjack or bust
        while (dealer_value <= 16){ // dealer hits for 16 and below and stands on 17 or above
            Dealer.push_back(Draw_Card());
            Hand_Value(Dealer, dealer_value, dealer_ace);
        }
    }
    full = true;
    std::cout << std::endl << "Hand value: " << user_value << std::endl;
    std::cout << "Dealer value: " << dealer_value << std::endl;
    std::cout << std::endl;
    game_history();
}
