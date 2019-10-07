#ifndef CARD_H
#define CARD_H
#include <iostream>

#pragma warning(disable : 4996)
using namespace std;

class Card
{
private:
	const static int BUF = 24;
    const static int ACE = 1;
    const static int KING = 13;
    const static int QUEEN = 12;
    const static int JACK = 11;

	int cardNumber;		//2-10, Jack=11, Queen=12, King=13, Ace=1
	char suit;			//Diamonds, Hearts, Spades, Clubs
	bool dealt;			//Track whether this card has been dealt yet

public:

	/* CONSTRUCTORS */
	Card();
	Card(char cardNum, char suit);

	/* DESTRUCTOR */
	~Card();

	/* METHODS */
	void SetDealt(bool delt);
	bool GetDealt();
	char ConvertFaceCard();
	char ConvertSuitToSymbol();
	void ConvertSuitToWord(char* word);

	/* OVERLOADED OPERATORS */
	friend std::ostream& operator<< (std::ostream& stream, Card& card);
	friend int operator + (Card const &, Card const &);
	void print(std::ostream& stream, bool symbol);

};

#endif // !CARD_H