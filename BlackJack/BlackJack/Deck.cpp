#include "Deck.h"
#include "Card.h"


Deck::Deck()
{
	buildDeck();
}


Deck::~Deck()
{
}


Card Deck::getCard(int index)
{
	return this->card[index];
}

void Deck::shuffle()
{
	srand(time(NULL));
	//Swap two cards x number of times to shuffle position on array
	for (int i = 0; i < SHUFFLE; i++)
	{
		int random = rand() % DECKSIZE; // between 0 - (DECKSIZE-1)
		int random2 = rand() % DECKSIZE;
		std::swap(card[random], card[random2]);
	}
}

int Deck::deal(int numCardsPerPlayer, std::vector<Card> &hand, int top)
{
	Card playerHand[CARDPERSUIT];

	for (int i = 0; i < numCardsPerPlayer; i++)
	{
		card[top].SetDealt(true);
		hand.push_back(card[top]);
		top += 1;
	}

	return top++;
}


void Deck::buildDeck()
{
	int counter = 0;

	// Heart, Diamonds, Spades, Club
	char suitList[SUITCOUNT] = { 'h', 'd', 's', 'c' };

	while (counter < DECKSIZE)
	{
		for (int suit = 0; suit < SUITCOUNT; suit++)
		{
			for (int card = 1; card <= CARDPERSUIT; card++)
			{
				this->card[counter] = Card(card, suitList[suit]);
				counter += 1;
			}
		}
	}
}

