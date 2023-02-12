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

    // Initialize vectors
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
        myPlayer.myHand->handCards.push_back(myDeck.draw());
    
    
    // Outputs player hand
    cout << myPlayer.myHand << "\n" << endl;

    // Track used in loops
    int index = -1;
    int size = myPlayer.myHand->handCards.size();

    for (int i = 0; i < size; i++) {

        size = myPlayer.myHand->handCards.size();

        // Validate input
        while (index < 0 || index > size) {

            cout << setw(15) << "--- Please choose which card you wish to play --- \n";
            cout << myPlayer.myHand;
            cout << "Press 0 to cancel action \n" << endl;
            cout << "What card (index) do you wish to play? : ";
            cin >> index;
        }

        // Play card if choice successful
        if (index != 0) {
            myPlayer.myHand->handCards[index - 1]->play(&myPlayer, &myDeck);
        }
        else 
            cout << "Play action has been cancelled! \n" << endl;

        index = -1; // Reset variable
    }

    // Outputs cards in deck (is shuffled)
    cout << myDeck << "\n" << endl;

    // Outputs player hand (empty)
    cout << myPlayer.myHand << "\n" << endl;
        
    return 0;
}