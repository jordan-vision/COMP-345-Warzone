#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm> 
#include <random>


using namespace std;

// Enum and Array for card type 
enum class CardType { Bomb, Reinforcement, Blockade, Airlift, Diplomacy };


// Initializes the classes for use in Card class
class Player;
class Deck; 
class Hand; 

/****************************************************************/
/************************** CARD CLASS **************************/
/****************************************************************/
class Card
{
    private:
    public:
        Card();                                                         // Constructor                                         
        ~Card();                                                        // Destructor
        Card(const Card &card);                                         // Copy Constructor
        Card& operator =(const Card &card);                             // Assignment Operator
        friend ostream& operator <<(ostream& out, const Card* card);    // Stream Operator
        Card(CardType* cardType) : cardType(cardType) {}                // Constructor with parameter

        CardType* cardType;                                             // Card enum type pointer
        
        void play(Player* player, Deck* mainDeck);                    // Uses card from hand and places in deck
};

/****************************************************************/
/************************** DECK CLASS **************************/
/****************************************************************/
class Deck 
{
    private:
    public:
        Deck();                                                         // Constructor
        ~Deck();                                                        // Destructor
        Deck(const Deck &deck);                                         // Copy Constructor
        Deck& operator =(const Deck &deck);                             // Assignment Operator
        friend ostream& operator <<(ostream& out, const Deck& deck);    // Stream Operator

        vector<Card*> deckCards;                                        // Contains Deck Card Pointers
        void fillDeck(int deckSize);                                    // Populates deck with cards

        Card* draw();
        void printDeckOutput();                                         // Prints output of deck 
};

/****************************************************************/
/************************** HAND CLASS **************************/
/****************************************************************/
class Hand
{
    private:
    public:
        Hand();                                                         // Constructor
        ~Hand();                                                        // Destructor
        Hand(const Hand &hand);                                         // Copy Constructor
        Hand& operator =(const Hand &hand);                             // Assignment Operator
        friend ostream& operator <<(ostream& out, const Hand* hand);    // Stream Operator

        vector<Card*> handCards;                                        // Contains Hand Card Pointers
};  