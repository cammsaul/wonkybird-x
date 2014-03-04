//
//  GameManager.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "GameManager.h"

unique_ptr<GameManager> GameManager::sharedInstance_ = nullptr;

GameManager& GameManager::sharedInstance() {
	if (!GameManager::sharedInstance_) {
		GameManager::sharedInstance_ = unique_ptr<GameManager>(new GameManager());
	}
	return *sharedInstance_;
}

GameManager::GameManager():
	gameState_((GameState)(GStateMainMenu|GStateRound1)),
	round1Score_(0),
	round2Score_(0)
{
	if (GameManager::sharedInstance_) assert(!"Created a duplicate GameManager!");
}

void GameManager::update() {
	LastFrameState_ = GState();
	LastFrameScore_ = CurrentRoundScore();
}

float GameManager::GameSpeed() const {
	if (GState() & (GStateMainMenu|GStateGameOver)) return 0;
	
	return 1.0f + (ScorePipeXVelocityMultiplier * CurrentRoundScore()) * (IsReversed() ? -1.0f : 1.0f);
}
		
bool GameManager::IsReversed() const {
	return (CurrentRoundScore()/ CrazyBackwardsModeScore) % 2 != 0;
}


#pragma mark - Global Helper functions

NSUInteger CurrentRoundScore() {
	return GState() & GStateRound1 ? GameManager::sharedInstance().Round1Score() : GameManager::sharedInstance().Round2Score();
}

GameState LastFrameState() {
	return GameManager::sharedInstance().LastFrameState();
}

unsigned LastFrameScore() {
	return GameManager::sharedInstance().LastFrameScore();
}

GameState GState() {
	return GameManager::sharedInstance().GState();
}

void SetGState(int gState) {
	GameManager::sharedInstance().SetGState((GameState)gState);
}