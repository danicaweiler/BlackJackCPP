#include "Player.h"
#include <vector>


Player::Player()
{
}

Player::Player(std::vector<Card> cards)
{
	hand = cards;
}

Player::~Player()
{
}

std::vector<Card> Player::GetHand()
{
	return hand;
}

void Player:: AddToHand(std::vector<Card> card)
{
	hand.push_back(card.front());
}

