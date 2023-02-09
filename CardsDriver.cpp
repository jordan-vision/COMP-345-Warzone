#include "Cards.h"

int main() {

    const int DECK_SIZE = 17;
    const int HAND_SIZE = 2;

    Deck myDeck;
    Hand myHand;

    myDeck.fillDeck(DECK_SIZE);

    cout << myDeck << "\n" << endl;

    for (int i = 0; i < HAND_SIZE; i++) 
        myDeck.draw(&myHand);
    
    cout << myHand << "\n" << endl;
    
    for (int i = 0; i < HAND_SIZE; i++)         
        myHand.handCards[0]->play(&myHand, &myDeck);

    cout << myDeck << "\n" << endl;

    cout << myHand << "\n" << endl;
        
    return 0;
}
