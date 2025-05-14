// Author: Adam Maciaszek
#ifndef BLACKJACK__H
#define BLACKJACK__H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>


class Blackjack {
    public:
        Blackjack();

        void play();
        void Create_Deck();
        void Cards();
        void shuffle();

        bool Hit();
        bool Stand();
        bool gameover();

        int Get_Value(std::string player_card, int &ace_count);
        int winner();

        std::string Draw_Card();
        std::string to_lower(std::string &input);
        int Hand_Value(std::vector<std::string> player_deck, int player_value, int ace_count);


    private:
        int value;
        int position;
        int player_value;
        int dealer_value;
        int player_ace;
        int dealer_ace;

        bool has_ace;

        std::string player_card;
        std::string result;
        
        std::vector<std::string> Deck;
        std::vector<std::string> Player;
        std::vector<std::string> Dealer;
        const std::vector<std::string> rank = {"A", "K", "Q", "J", "T",
        "9", "8", "7", "6", "5", "4", "3", "2"};
        const std::vector<std::string> suit = {"S", "C", "H", "D"};

};

#endif