#ifndef DEALER_H
#define DEALER_H

#include "Player.h"

class Dealer : public Player
{
private:
	/* CONSTANTSs */
	const static int OVER = 17;
	const static int HIGH = 21;

public:
	/* CONSTRUCTORS */
	Dealer();
	Dealer(std::vector<Card> cards);

	/* DESTRUCTOR */
	~Dealer();

	/* METHODS */
	int DetermineIfOver(int checkTotal);
	void PrintHand(); //overload before virtual functions from parent class
	void PrintHand(int HideCard);
	int CalculateHandTotal(); //same, unused
	int CalculateHandTotal(int HideCard);
};

#endif // !DEALER_H