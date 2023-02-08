#include "Cards.h"

/****************************************************************/
/************************** DECK CLASS **************************/
/****************************************************************/

/******************* DECK CONSTRUCTOR *******************/
Deck::Deck() {

};

/******************** DECK DESTRUCTOR *******************/
Deck::~Deck() {

    for (Card* card : deckCards) 
        delete card;    
};

/***************** DECK COPY CONSTRUCTOR *****************/
Deck::Deck(const Deck &deck) {

    for (Card* card : deck.deckCards) 
        deckCards.push_back(new Card(*card));
};

/**************** DECK ASSIGNMENT OPERATOR ***************/
Deck& Deck::operator =(const Deck &deck) {

    deckCards = deck.deckCards;
    return *this;
};

/***************** DECK STREAM OPERATOR *****************/
ostream& operator<<(std::ostream& out, const Deck& deck) {
                                           
    out << setw(15) << "------------------- DECK CARDS ------------------ \n";
    out << left << setw(15) << "Card Type" << left << setw(20)<< "Card Reference" << left << setw(20) << "Type Reference" << endl;
    for (int i = 0; i < deck.deckCards.size(); i++)
        out << deck.deckCards[i];

    return out; 
}

/******************* DECK DRAW FUNCTION *******************/
void Deck::draw(Hand* playerHand) {

    // DECK SHUFFLER
    auto randomSeed = random_device {};                         // Generates random seed    (ensures each run will generate new unique shuffle)
    auto random = default_random_engine { randomSeed() };       // Generates random number  
    shuffle(deckCards.begin(), deckCards.end(), random);        // Shuffles vector according to random

    Card* pCard = deckCards.back();             // Stores card pointer from back of deck
    playerHand->handCards.push_back(pCard);     // Adds card to player hand
    deckCards.pop_back();                       // Removes card from deck
};

/******************* DECK FILL FUNCTION *******************/
void Deck::fillDeck(int deckSize) {

    int adjustedSize = ((deckSize + 5/2) / 5);  // Nearest multiple of 5 (divided by 5 to account for each type)

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

    for (int i = 0; i < deckCards.size(); i++)
    {
        CardType cType = *(deckCards[i]->cardType);

        cout << left << setw(5) << (i + 1)
             << left << setw(15) << CardTypeString[static_cast<int>(cType)]
             << left << setw(20) << deckCards[i]->cardType
             << left << setw(20) << &deckCards[i]
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

    delete cardType;
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

/***************** CARD STREAM OPERATOR *****************/
ostream& operator<<(std::ostream& out, const Card* card) {

    out << left << setw(15) << CardTypeString[static_cast<int>(*(card->cardType))]
             << left << setw(20) << static_cast<void const *>(card)
             << left << setw(20) << card->cardType
             << endl;

    return out;
}

/******************* CARD PLAY FUNCTION *******************/
void Card::play(Hand* playerHand, Deck* mainDeck) {

    //add to player list of orders

    auto element = find(playerHand->handCards.begin(), playerHand->handCards.end(), this);  // Finds element
    int elementIndex = distance(playerHand->handCards.begin(), element);                    // Gets element index

    mainDeck->deckCards.push_back(move(this));  // Moves card pointer back to deck
    playerHand->handCards.erase(element);       // Erases card pointer from hand
};

/****************************************************************/
/************************** HAND CLASS **************************/
/****************************************************************/

/******************* HAND CONSTRUCTOR *******************/
Hand::Hand() {

};

/******************** HAND DESTRUCTOR *******************/
Hand::~Hand() {

    for (Card* card : handCards) 
        delete card;    
};

/***************** HAND COPY CONSTRUCTOR *****************/
Hand::Hand(const Hand &hand) {

    for (Card* card : hand.handCards) 
        handCards.push_back(new Card(*card));
};

/**************** HAND ASSIGNMENT OPERATOR ***************/
Hand& Hand::operator =(const Hand &hand) {

    handCards = hand.handCards;
    return *this;
};

/***************** HAND STREAM OPERATOR *****************/
ostream& operator<<(std::ostream& out, const Hand& hand) {

    out << setw(15) << "------------------ Player Hand ------------------ \n";
    out << left << setw(15) << "Card Type" << left << setw(20)<< "Card Reference" << left << setw(20) << "Type Reference" << endl;
    for (int i = 0; i < hand.handCards.size(); i++)
        out << hand.handCards[i];

    return out; 
};