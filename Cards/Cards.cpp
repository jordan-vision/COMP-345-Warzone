#include "Cards.h"

/****************************************************************/
/************************** DECK CLASS **************************/
/****************************************************************/

/******************* DECK CONSTRUCTOR *******************/
Deck::Deck() {

    cardCount = 0;
};

/******************** DECK DESTRUCTOR *******************/
Deck::~Deck() {

};

/***************** DECK COPY CONSTRUCTOR *****************/
Deck::Deck(const Deck &deck) {

    deckCards = deck.deckCards;
    cardCount = deck.cardCount;
};

/**************** DECK ASSIGNMENT OPERATOR ***************/
Deck& Deck::operator =(const Deck &deck) {

    deckCards = deck.deckCards;
    cardCount = deck.cardCount;
    return *this;
};

/******************* DECK DRAW FUNCTION *******************/
void Deck::draw(Hand* playerHand) {

    std::random_shuffle(deckCards.begin(), deckCards.end());


    Card* pCard = deckCards.back();
    playerHand->handCards.push_back(pCard);
    deckCards.pop_back();
    cardCount--;
};

/******************* DECK FILL FUNCTION *******************/
void Deck::fillDeck(int deckSize) {

    int adjustedSize = ((deckSize + 5/2) / 5);  // Nearest multiple of 5 (divided by 5 to account for each type)
    cardCount = adjustedSize * 5;               // Track amount of cards in deck

    // Add each type of card according to the adjusted amount
    for (int i = 0; i < adjustedSize; i++) {

        // Push new Card with new CardType to the deck
        deckCards.push_back(new Card(new CardType(CardType::Bomb)));            
        deckCards.push_back(new Card(new CardType(CardType::Reinforcement)));
        deckCards.push_back(new Card(new CardType(CardType::Blockade)));
        deckCards.push_back(new Card(new CardType(CardType::Airlift)));
        deckCards.push_back(new Card(new CardType(CardType::Diplomacy)));      
    }
};

/******************** DECK PRINT OUTPUT *******************/
void Deck::printDeckOutput() {

    cout << left << setw(5) << "#" << left << setw(15) << "Card Type" << left << setw(20)<< "Type Reference" << left << setw(20) << "Card Reference" << endl;
    for (int i = 0; i < cardCount; i++)
    {
        CardType cType = *(deckCards[i]->cardType);

        cout << left << setw(5) << (i + 1)
             << left << setw(15) << CardTypeString[static_cast<int>(cType)]
             << left << setw(20) << deckCards[i]->cardType
             << left << setw(20) << deckCards[i]
             << endl;
    }
};

/****************************************************************/
/************************** CARD CLASS **************************/
/****************************************************************/

/******************* CARD CONSTRUCTOR *******************/
Card::Card() {

};

/******************** CARD DESTRUCTOR *******************/
Card::~Card() {

};

/***************** CARD COPY CONSTRUCTOR *****************/
Card::Card(const Card &card) {

    cardType = card.cardType;
};

/**************** CARD ASSIGNMENT OPERATOR ***************/
Card& Card::operator =(const Card &card) {

    cardType = card.cardType;
    return *this;
};

/******************* CARD PLAY FUNCTION *******************/
void Card::play(Hand* playerHand, Deck* mainDeck) {

    //add to player list of orders
    
    // Remove from Hand
    playerHand->handCards.erase(std::remove(playerHand->handCards.begin(), playerHand->handCards.end(), this), playerHand->handCards.end());
    
    // Add to Deck
    mainDeck->deckCards.push_back(this);
};

/****************************************************************/
/************************** HAND CLASS **************************/
/****************************************************************/

/******************* HAND CONSTRUCTOR *******************/
Hand::Hand() {

};

/******************** HAND DESTRUCTOR *******************/
Hand::~Hand() {

};

/***************** HAND COPY CONSTRUCTOR *****************/
Hand::Hand(const Hand &hand) {

    handCards = hand.handCards;
};

/**************** HAND ASSIGNMENT OPERATOR ***************/
Hand& Hand::operator =(const Hand &hand) {

    handCards = hand.handCards;
    return *this;
};