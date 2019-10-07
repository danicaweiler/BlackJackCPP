#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <iostream>     
#include <algorithm>
#include <time.h>
#include <vector>

class Deck
{
private:
	/* CONSTANTS */
	const static int DECKSIZE = 52;		//Account for possible jokers possible with change
	const static int SUITCOUNT = 4;
	const static int CARDPERSUIT = 13;
	const static int SHUFFLE = 500;		//number of swaps to do for shuffle

	Card card[DECKSIZE];
	void buildDeck();

public:
	/* CONSTRUCTORS */
	Deck();

	/* DESTRUCTOR */
	~Deck();
	
	/* METHODS */
	Card getCard(int index);
	void shuffle();
	int deal(int numCardsPerPlayer, std::vector<Card> &hand, int top);

};

#endif // !DECK_H
