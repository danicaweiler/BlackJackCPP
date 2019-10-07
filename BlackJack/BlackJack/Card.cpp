#include "Card.h"

Card::Card()
{
	this->cardNumber = 0;
	this->suit = 0;
	this->dealt = false;
}

Card::Card(char cardNum, char suit)
{
	this->cardNumber = cardNum;
	this->suit = suit;
	this->dealt = false;
}

Card::~Card()
{
}

void Card::SetDealt(bool dealt)
{
	this->dealt = dealt;
}

bool Card::GetDealt()
{
	return this->dealt;
}

void Card::ConvertSuitToWord(char* word)
{

	if (suit == 'd')
	{
		strcpy(word, "Diamonds");
	}
	else if (suit == 's')
	{
		strcpy(word, "Spades");
	}
	else if (suit == 'h')
	{
		strcpy(word, "Hearts");
	}
	else if (suit == 'c')
	{
		strcpy(word, "Clubs");
	}

}

char Card::ConvertFaceCard()
{
	if (cardNumber == ACE)
	{
		return 'A';
	}
	else if (cardNumber == JACK)
	{
		return 'J';
	}
	else if (cardNumber == QUEEN)
	{
		return 'Q';
	}
	else if (cardNumber == KING)
	{
		return 'K';
	}
	else
	{
		char numToChar[BUF] = {};
		itoa(cardNumber, numToChar, 10);
		return numToChar[0];
	}
}

char Card::ConvertSuitToSymbol()
{
	if (suit == 'd')
	{
		return 5;
	}
	else if (suit == 's')
	{
		return 4;
	}
	else if (suit == 'h')
	{
		return 3;
	}
	else if (suit == 'c')
	{
		return 6;
	}
}

void Card::print(std::ostream& stream, bool symbol)
{
	char word[BUF] = "";
	this->ConvertSuitToWord(word);

	if (symbol)
		cout << " " << ConvertSuitToSymbol();


	if (this->ConvertFaceCard() == '1')
	{
		cout << 10;
	}
	else
	{
		cout << this->ConvertFaceCard();
	}

	if (!symbol)
		cout << " " << word << " ";
}

std::ostream & operator<<(std::ostream & stream, Card & card)
{
	//Can be altered to use words not symbols - true means use symbols/false means use words
	//as symbols do not work on all OS ~ symbols word on Windows 7
	card.print(stream, false);
	return stream;
}

int operator+(Card const &c1, Card const &c2)
{
	int value = 0;
	//c1 and c2 are the same card so only use one to get result, operator used to trigger to be able get info
	if (c1.cardNumber > 10)
	{
		value += 10;
	}
	else
	{
		value += c1.cardNumber;
	}
	
	return value;
}
