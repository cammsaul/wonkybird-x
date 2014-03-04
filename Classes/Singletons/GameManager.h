//
//  GameManager.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GameManager_H
#define WONKYBIRD_GameManager_H

class GameManager {
public:
	static shared_ptr<GameManager> sharedInstance();
	
	GameState GState() const { return gameState_; }
	void SetGState(GameState gState) { gameState_ = gState; }
	
	GameState LastState() const { return lastState_; } ///< state of the last frame.
	
	unsigned Round1Score() { return round1Score_; }
	unsigned Round2Score() { return round2Score_; }
	
	void update(); ///< MainScene will take care of calling this
	
	GameManager();
private:
	GameState lastState_;
	GameState gameState_;
	unsigned round1Score_;
	unsigned round2Score_;

	static shared_ptr<GameManager> sharedInstance_;
};

#endif