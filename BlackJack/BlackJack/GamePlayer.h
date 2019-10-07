#ifndef GAMEPLAYER_H
#define GAMEPLAYER_H

#include "Player.h"
#include "constants.h"

class GamePlayer: public Player
{
private:

	const static int ENDVALUE = 21;
	int hasAce;

public:
	/* CONSTRUCTORS */
	GamePlayer();
	GamePlayer(std::vector<Card> cards);

	/* DESRUCTOR */
	~GamePlayer();

	/* methods */
	int DetermineIfOver(int checkTotal);
	int CalculateHandTotal();
	void PrintHand();
	int GetHasAce();
	void SetHasAce(int ace);
};

#endif // !GAMEPLAYER_H

