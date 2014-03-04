//
//  GameManager.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameManager.h"

shared_ptr<GameManager> GameManager::sharedInstance_ = make_shared<GameManager>();

shared_ptr<GameManager> GameManager::sharedInstance() {
	return sharedInstance_;
}

GameManager::GameManager():
	gameState_((GameState)(GStateMainMenu|GStateRound1)),
	round1Score_(0),
	round2Score_(0)
{
	if (GameManager::sharedInstance()) assert(!"Created a duplicate GameManager!");
}

void GameManager::update() {
	lastState_ = GState();
}


#pragma mark - Global Helper functions

NSUInteger CurrentRoundScore() {
	return GState() & GStateRound1 ? GameManager::sharedInstance()->Round1Score() : GameManager::sharedInstance()->Round2Score();
}

GameState LastState() {
	return GameManager::sharedInstance()->LastState();
}

GameState GState() {
	return GameManager::sharedInstance()->GState();
}

void SetGState(int gState) {
	GameManager::sharedInstance()->SetGState((GameState)gState);
}