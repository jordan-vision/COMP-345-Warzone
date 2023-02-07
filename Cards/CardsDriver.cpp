#include "Cards.h"
#include "Cards.cpp"

int main() {

    Deck myDeck;
    Hand myHand;

    Card myCard;
    Card otherCard;

    otherCard = myCard;

    Card newCard = myCard;
     
    myDeck.fillDeck(48);
    
    myDeck.printDeckOutput();
    myDeck.draw(&myHand);
    myDeck.printDeckOutput();

    myHand.handCards[0]->play(&myHand, &myDeck);


    return 0;
}

