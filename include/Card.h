#ifndef CARD
#define CARD

enum Suit {
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

typedef struct {
    int value;
    enum Suit suit;

    bool face_down;
    int covered_by;
    int covers;
} Card;

typedef struct {
    int *card_list;
} CardSet;

#endif