#include "Cards.h"
#include "Player.h"
#include "Orders.h"

int main() {

    // Constants to store deck/hand size
    const int DECK_SIZE = 17;
    const int HAND_SIZE = 2;

    // Create player and deck objects
    Player myPlayer;
    Deck myDeck;
    Hand hand;
    
    myPlayer.myHand = &hand;
    OrdersList ord;
    myPlayer.myOrders = &ord;

    // Fills deck according to size (will round to nearest multiple of 5)
    myDeck.fillDeck(DECK_SIZE);

    // Outputs cards in deck (not shuffled)
    cout << myDeck << "\n" << endl;

    // Draws cards from deck into player hand
    for (int i = 0; i < HAND_SIZE; i++) 
        myPlayer.myHand->handCards.push_back(myDeck.drawCard());
    
    
    // Outputs player hand
    cout << myPlayer.myHand << "\n" << endl;

    // Plays all cards in player hand
    for (int i = 0; i < HAND_SIZE; i++) {
        myPlayer.myHand->handCards[0]->play(&myPlayer, &myDeck);
    }     
    
    // Outputs cards in deck (is shuffled)
    cout << myDeck << "\n" << endl;

    // Outputs player hand (empty)
    cout << myPlayer.myHand << "\n" << endl;
        
    return 0;
}
