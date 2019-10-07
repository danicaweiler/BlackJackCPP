#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <vector>

class Player
{
public:
	/* CONSTRUCTORS */
	Player();
	Player(std::vector<Card> cards);

	/* DESTRUCTOR */
	~Player();

	std::vector<Card> GetHand();
	void AddToHand(std::vector<Card> card);

protected:
	std::vector<Card> hand;
	virtual int DetermineIfOver(int checkTotal) = 0;
	virtual void PrintHand() = 0;
	virtual int CalculateHandTotal() = 0;
};

#endif // !PLAYER_H