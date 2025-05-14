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

        int Get_Value();

        std::string Draw_Card();


    private:
        int value;
        bool has_ace;
        std::vector<std::string> player_deck;
        std::vector<std::string> Deck;
        std::vector<std::string> Player;
        std::vector<std::string> Dealer;
        const std::vector<std::string> rank = {"A", "K", "Q", "J", "T",
        "9", "8", "7", "6", "5", "4", "3", "2"};
        const std::vector<std::string> suit = {"S", "C", "H", "D"};

};

#endif