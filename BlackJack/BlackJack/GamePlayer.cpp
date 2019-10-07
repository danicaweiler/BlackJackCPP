#include "GamePlayer.h"

GamePlayer::GamePlayer()
{
}

GamePlayer::GamePlayer(std::vector<Card> cards) : Player(cards)
{
	hasAce = 0;
}


GamePlayer::~GamePlayer()
{
}

int GamePlayer::CalculateHandTotal()
{
	int total = 0;
	for (std::vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it)
	{
		int t = *it + *it;
		if (t == 1) hasAce++; //check if that card was an ace
		total += t;
	}
	return total;
}

int GamePlayer::DetermineIfOver(int checkTotal)
{
	if (checkTotal > ENDVALUE)
	{
		return OVER; //Over 21
	}
	else if (checkTotal == ENDVALUE)
	{
		return RIGHTON; // 21 right on
	}
	else
	{
		return UNDER; //Under
	}
}


void GamePlayer::PrintHand()
{
	cout << "\n  --- Player's Hand ---\n";

	for (std::vector<Card>::iterator it = hand.begin(); it != hand.end(); ++it)
		std::cout << ' ' << *it << endl;
	std::cout << endl;

}

int GamePlayer::GetHasAce()
{
	return hasAce;
}

void GamePlayer::SetHasAce(int ace)
{
	hasAce = ace;
}