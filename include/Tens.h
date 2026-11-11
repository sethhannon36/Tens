#ifndef TENS
#define TENS

#include "Card.h"

#define TENS_DECK_INDEX 0
#define TENS_PILE_INDEX 1
#define TENS_CARD_FACE_UP 0
#define TENS_CARD_FACE_DOWN 1
#define TENS_CARD_NOT_COVERED -1
#define TENS_CARD_NOT_COVERS -1
#define PLAYER_ID 0

Card* card_registry; // index is the card's ID
int* card_positions; // card index stores set index
int card_count;
int player_count;
int active_player;


void TensInit(int players);
void TensDestroy();
int Tens_GetRandomCard();
int Tens_GetCardCount();
void Tens_NextPlayer();
void Tens_MoveCardTo(int card_id, int set_id);
void Tens_PlayCard(int id);
void Tens_TakeCards(int player);
void Tens_GetCardsFromSet(int set_id, int* target);
int Tens_CountCardsInSet(int set_id);
int Tens_GetCardValue(int card_id);
enum Suit Tens_GetCardSuit(int card_id);
bool Tens_IsCardFaceDown(int card_id);
int Tens_GetCardCoveredBy(int card_id);
int Tens_GetCardCovers(int card_id);
int Tens_GetCardPosition(int card_id);
int Tens_GetPlayerSetId(int player_id);



#endif