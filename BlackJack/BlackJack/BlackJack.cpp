#include "BlackJack.h"


BlackJack::BlackJack()
{
	deck = Deck();

	//Used to alter text colour in the console, could have been its out static class but time was limited
	hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO *ConsoleInfo = new CONSOLE_SCREEN_BUFFER_INFO();
	GetConsoleScreenBufferInfo(hConsoleHandle, ConsoleInfo);
	OriginalColors = ConsoleInfo->wAttributes;
}


BlackJack::~BlackJack()
{
}

void BlackJack::StartGame()
{
    PrintTitle();
    cout << " Shuffling Deck...\n";
    deck.shuffle();
    _sleep(WAIT);

    //Deal the initial hands to the player and dealer
    int topOfDeck = 0;
    std::vector<Card> hand = {};
    topOfDeck = deck.deal(CARDPERPLAYER, hand, topOfDeck);
    player = GamePlayer(hand);

    hand.clear();
    topOfDeck = deck.deal(CARDPERPLAYER, hand, topOfDeck);
    dealer = Dealer(hand);

    return MainGameLoop(topOfDeck, hand);
}

void BlackJack::MainGameLoop(int &topOfDeck, std::vector<Card> &hand)
{
    /* ---- Main Game Loop ---- */
    while (true)
    {
        _sleep(WAIT / WAITMULTIPLIER);
        player.PrintHand();
        int playerTotal = player.CalculateHandTotal();

        CheckAces(playerTotal);
        PrintScore(playerTotal);

        int playerOver = player.DetermineIfOver(playerTotal);
        dealer.PrintHand(HIDEDEALERCARD);
        _sleep(WAIT);

        //Prompt for next move if the player hasnt lost yet
        if (playerOver == UNDER) // under high (21) thresholds
        {
            bool choice = DrawAgainPrompt();
            if (choice) //Keep dealing for palyer
            {
                topOfDeck = deck.deal(DRAWCARD, hand, topOfDeck);
                player.AddToHand(hand);
                hand.clear();
            }
            else
            { //switch to dealer loop
                ClearScreen();
                PrintTitle();
                player.PrintHand();
                PrintScore(playerTotal);

                bool retflag = DealerGameLoop(playerTotal, topOfDeck, hand);
                if (retflag) return;
            }
        }
        else
        { //right on 21 or over 21
            return DeterminePlayerResult(playerOver);
        }

        ClearScreen();
        PrintTitle();
    }
}

void BlackJack::DeterminePlayerResult(int playerOver)
{
    if (playerOver == RIGHTON)
    {
        SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "\n\n !!! YOU WIN !!!\n You got 21 right on!\n";
    }
    else if (playerOver == OVER)
    {
        SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
        cout << "\n * Oh no, you're over 21! Good game! *";
    }

    cin.ignore();
    return;
}

bool BlackJack::DealerGameLoop(int playerTotal, int & topOfDeck, std::vector<Card> & hand)
{
    int dealerTotal = 0;
    /* --- Dealers main game loop --- */
    while (dealerTotal < HIGHVAL)
    {
        dealer.PrintHand(HIDEDEALERCARD);
        dealerTotal = dealer.CalculateHandTotal(HIDEDEALERCARD);
        PrintScore(dealerTotal);
        int dealerOver = dealer.DetermineIfOver(dealerTotal);
        _sleep(WAIT * WAITMULTIPLIER);

        if ((dealerOver == OVERTHRESHOLD) || (dealerOver == OVER) || (dealerOver == RIGHTON))//Over 17 but under 21 stop/over 21
        {
            SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED);
            cout << "\n * Dealer has gone over " << HIGHVAL << ", time to reveal the hidden card. *\n";
            SetConsoleTextAttribute(hConsoleHandle, OriginalColors);

            _sleep(WAIT * WAITMULTIPLIER);
            dealer.PrintHand(NOHIDECARD);
            dealerTotal = dealer.CalculateHandTotal(NOHIDECARD);
            dealerOver = dealer.DetermineIfOver(dealerTotal);

            SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED);
            DetermineDealerResult(dealerOver, playerTotal, dealerTotal);
            return true;
        }

        topOfDeck = deck.deal(DRAWCARD, hand, topOfDeck);
        dealer.AddToHand(hand);
        hand.clear();

        SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED);
        cout << "\n Dealer Drawing Card..." << endl;
        SetConsoleTextAttribute(hConsoleHandle, OriginalColors);

        _sleep(WAIT * WAITMULTIPLIER);
    }
    return false;
}

void BlackJack::DetermineDealerResult(int dealerOver, int playerTotal, int & dealerTotal)
{
    if (dealerOver == OVER)
    {
        DetermineHigherPlayer(playerTotal, dealerTotal);
    }
    else if (dealerOver == RIGHTON)
    {
        cout << " The dealer got 21 right on!";
    }
    else //over threshold
    {
        cout << " The dealer finished with " << dealerTotal << "!\n";
        DetermineHigherPlayer(playerTotal, dealerTotal);
    }
    std::cin.ignore();
}

void BlackJack::CheckAces(int &playerTotal)
{
    if (player.GetHasAce() > 0) //Account for possibility of more tha one ace
    {
        for (int aceCount = player.GetHasAce(); aceCount > 0; aceCount--)
        {
            playerTotal += AcePrompt();
            player.SetHasAce(0);
        }
    } //Assume dealer use 1 always
}


void BlackJack::PrintScore(int score)
{
	cout << " Score: " << score << endl;
}

void BlackJack::PrintTitle()
{
	cout <<"\n ************************************\n"
		" **           Black Jack           **\n"
		" ************************************\n\n";
}

void BlackJack::ClearScreen()
{
	system("CLS");
}

int BlackJack::AcePrompt()
{
	char choice = ' ';
	while (true)
	{
		cout << " You drew an Ace! Would you like to count it as:\n a. 1 point\n b. 11 points\n -->";
		choice = getch();
		if ((choice == 'a') || (choice == 'A'))
		{
			cout << endl;
			return 0;
		}
		else if ((choice == 'b') || (choice == 'B'))
		{
			cout << endl;
			return 10;
		}
		else
		{
			cout << "\n Invalid choice. Try Again\n\n";
		}
	}
}

bool BlackJack::DrawAgainPrompt()
{
	char choice = ' ';
	while (true)
	{
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
		cout << "\n Draw Again? Y/N\n --> ";
		SetConsoleTextAttribute(hConsoleHandle, OriginalColors);
		choice = getch(); //Get one char without waiting for enter
		putch(choice);

		if ((choice == 'Y') || (choice == 'y'))
		{
			return true;
		}
		else if ((choice == 'N') || (choice == 'n'))
		{
			return false;
		}
		else
		{
			cout << "\n Invalid choice. Try Again\n\n";
		}
	}
}

void BlackJack::DetermineHigherPlayer(int playerScore, int dealerScore)
{
	if (dealerScore > playerScore)
	{
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << " !!! You Win !!! The dealer was higher at "<<dealerScore<<"! \n";
		//Dealer win
	}
	else if (dealerScore < playerScore)
	{
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << " You were higher at "<<playerScore<<", so you lost!\n";
	    //Player win
	}
	else if (dealerScore == playerScore)
	{
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout <<" You got the same score as the dealer! It's a tie game!\n";
	}
}