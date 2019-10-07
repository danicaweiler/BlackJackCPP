#ifndef BLACKJACK_H
#define BLACKJACK_H

#include"Dealer.h"
#include"GamePlayer.h"
#include "Deck.h"
#include "Windows.h"
#include "constants.h"
#include <vector>
#include <string>
#include <conio.h>
#include <string>
#include <sstream>
#include <iostream>


class BlackJack
{
private:
	/* CONSTANTS */
	const static int WINSCORE = 21;
	const static int HIGHVAL = 17;
	const static int HIDEDEALERCARD = 0;
	const static int NOHIDECARD = 2;
	const static int WAIT = 500;
    const static int WAITMULTIPLIER = 2;
       
	GamePlayer player;
	Dealer dealer;
	Deck deck;

	// Needed to alter the text colour in the console //
	HANDLE hConsoleHandle;
	WORD OriginalColors;

	/* PRIVATE METHODS */
	void PrintTitle();
	void ClearScreen();
	int AcePrompt();
	bool DrawAgainPrompt();
	void DetermineHigherPlayer(int playerScore, int dealerScore);
	void PrintScore(int score);
    void MainGameLoop(int &topOfDeck, std::vector<Card> &hand);
    void DeterminePlayerResult(int playerOver);
    bool DealerGameLoop(int playerTotal, int & topOfDeck, std::vector<Card> & hand);
    void DetermineDealerResult(int dealerOver, int playerTotal, int & dealerTotal);
    void CheckAces(int &playerTotal);

public:
	/* CONSTRUCTORS */
	BlackJack();

	/* DESTRUCTOR */
	~BlackJack();

	/* METHOD */
	void StartGame();
};

#endif // !BLACKJACK_H
