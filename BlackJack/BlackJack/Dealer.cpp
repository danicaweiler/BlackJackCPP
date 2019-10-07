#include "Dealer.h"

Dealer::Dealer()
{
}

Dealer::Dealer(std::vector<Card> cards) : Player(cards)
{
}


Dealer::~Dealer()
{
}

int Dealer::DetermineIfOver(int checkTotal)
{
	if (checkTotal > HIGH)
	{
		return 1; //Over 21
	}
	else if (checkTotal == HIGH)
	{
		return 3; // 21 right on
	}
	else if (checkTotal >= OVER)
	{
		return	2; //over 17
	}
	else
	{
		return 0; //Under
	}
		
}


void Dealer::PrintHand()
{

}

void Dealer::PrintHand(int HideCard)
{
	cout << "\n  --- Dealer's Hand ---\n";
	int i = HideCard;
	for (std::vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (i != 1)
		{
			std::cout << ' ' << *it << endl;
		}
		else //hide card 2 in hand
		{
			std::cout << "  -- " << endl;
		}
		i++;
	}
	std::cout << endl;

}

int Dealer::CalculateHandTotal()
{
	return 0;
}

int Dealer::CalculateHandTotal(int HideCard)
{
	int skip = HideCard;
	int total = 0;
	for (std::vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		if (skip == 1) //do nothing, we want to skip it, its the hidden card
		{
		}
		else
		{
			total += *it + *it;
		}

		skip += 1;
	}
	return total;
}