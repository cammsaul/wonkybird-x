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
	static GameManager& sharedInstance();
	
	GameState GState() const { return gameState_; }
	void SetGState(GameState gState);
	
	GameState LastFrameState()	const { return lastFrameState_; } ///< state of the last frame.
	unsigned LastFrameScore()	const { return lastFrameScore_; } ///< score of the last frame.
	unsigned Round1Score()		const { return round1Score_; }
	unsigned Round2Score()		const { return round2Score_; }
	unsigned TotalScore()		const { return round1Score_ + round2Score_; }
	unsigned BestTotalScore()	const { return TotalScore(); } ///< TODO
	
	float GameSpeed() const;
	bool IsReversed() const; ///< whether game is currently running in reverse
	
	void IncrementScore() { if (GState() & GStateRound1) round1Score_++; else round2Score_++; }
	
	/// internal ///
	void update(); ///< MainScene will take care of calling this
	GameManager();
private:
	bool stateNeedsUpdate_ = false; ///< don't set state immediately in SetGState, wait a loop so everyone will see the GameState != LastState if needed
	GameState  pendingState_ = (GameState) -1;
	GameState lastFrameState_ = (GameState) -1;
	GameState gameState_ = (GameState)(GStateMainMenu|GStateRound1);
	unsigned lastFrameScore_ = -1;
	unsigned round1Score_ = 0;
	unsigned round2Score_ = 0;

	static unique_ptr<GameManager> sharedInstance_;
};

#endif