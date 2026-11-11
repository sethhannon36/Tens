#include "Tens.h"

#include <stdlib.h>
#include <time.h>

void TensInit(int players) 
{
    player_count = players;
    int num_decks = (players / 3) + 1;

    // use time to seed number generation
    srand(time(NULL));

    // allocate memory
    card_registry = malloc(sizeof(Card) * num_decks * 52);
    card_positions = malloc(sizeof(short) * num_decks * 52);

    // build deck
    card_count = 0;
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 1; j <= 13; j++) 
        {
            // add one deck for every 3 players
            for (int k = 0; k < num_decks; k++) 
            {
                card_registry[card_count] = (Card){j, i, false, -1, -1};
                card_positions[card_count] = 0; // set location to deck
                card_count++;
            }
        }
    }

    // deal cards to players
    for (int player = 0; player < player_count; player++) 
    {
        // deal table cards (face up and face down)
        for (int i = 0; i < 4; i++) 
        {
            /* Deal face down card */
            // get random card from the deck
            int down_card_id = Tens_GetRandomCard();

            // find next unowned card
            while ( Tens_GetCardPosition(down_card_id) != TENS_DECK_INDEX ) 
            {
                down_card_id = (down_card_id + 1) % card_count;
            }

            // assign card and set it face down
            Tens_MoveCardTo(down_card_id, Tens_GetPlayerSetId(player));
            card_registry[down_card_id].face_down = true;

            /* Deal Face-up card on top */
            // get random card from the deck
            int up_card_id = Tens_GetRandomCard();

            // find next unowned card
            while ( Tens_GetCardPosition(up_card_id) != TENS_DECK_INDEX ) 
            {
                up_card_id = (up_card_id + 1) % card_count;
            }

            // assign card
            Tens_MoveCardTo(up_card_id, Tens_GetPlayerSetId(player));
            card_registry[up_card_id].face_down = false;

            // set card covering flags
            card_registry[down_card_id].covered_by = up_card_id;
            card_registry[up_card_id].covers = down_card_id;

        }

        // deal each player 7 hand cards
        for (int i = 0; i < 7; i++) 
        {
            /* Deal face down card */
            // get random card from the deck
            int card_id = Tens_GetRandomCard();

            // find next unowned card
            while ( Tens_GetCardPosition(card_id) != TENS_DECK_INDEX ) 
            {
                card_id = (card_id + 1) % card_count;
            }

            // assign card and set it face down
            Tens_MoveCardTo(card_id, Tens_GetPlayerSetId(player));

        }
    }
}

void TensDestroy() {
    // destroy all cards and free pointer
    free( card_registry );
    card_registry = NULL;

    free( card_positions );
    card_positions = NULL;
}

int Tens_GetRandomCard() {
    return (rand() % card_count);
}

int Tens_GetCardCount() {
    return card_count;
}

void Tens_NextPlayer() {
    active_player++;
    if ( active_player > player_count + 2) active_player = 2;
}

void Tens_MoveCardTo(int card_id, int set_id) {
    card_positions[card_id] = set_id;
}

void Tens_PlayCard(int id) {
    Tens_MoveCardTo(id, TENS_PILE_INDEX);
}

void Tens_TakeCards(int set_id) {
    for (int i = 0; i < card_count; i++) {
        Tens_MoveCardTo(i, set_id);
    }
}

void Tens_GetCardsFromSet(int set_id, int* target) {
    int index = 0;

    // iterate through all cards
    for (int i = 0; i < card_count; i++) {
        // check if card i is in the set
        if (card_positions[i] == set_id) {
            // update the array with the ID
            target[index] = i;
            index++;
        }
    }
}

int Tens_CountCardsInSet(int set_id) {
    int counter = 0;
    for (int i = 0; i < card_count; i++) {
        if (card_positions[i] == set_id) counter++;
    }
    return counter;
}

int Tens_GetCardValue(int card_id) {
    return card_registry[card_id].value;
}

enum Suit Tens_GetCardSuit(int card_id) {
    return card_registry[card_id].suit;
}

bool Tens_IsCardFaceDown(int card_id) {
    return card_registry[card_id].face_down;
}

int Tens_GetCardCoveredBy(int card_id) {
    return card_registry[card_id].covered_by;
}

int Tens_GetCardCovers(int card_id) {
    return card_registry[card_id].covers;
}

int Tens_GetCardPosition(int card_id) {
    return card_positions[card_id];
}

int Tens_GetPlayerSetId(int player_id) {
    return player_id + 2;
}