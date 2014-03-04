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
	void SetGState(GameState gState) { gameState_ = gState; }
	
	GameState LastFrameState()		const { return LastFrameState_; } ///< state of the last frame.
	unsigned LastFrameScore()	const { return LastFrameScore_; } ///< score of the last frame.
	unsigned Round1Score()		const { return round1Score_; }
	unsigned Round2Score()		const { return round2Score_; }
	unsigned TotalScore()		const { return round1Score_ + round2Score_; }
	unsigned BestTotalScore()	const { return TotalScore(); } ///< TODO
	
	float GameSpeed() const;
	bool IsReversed() const; ///< whether game is currently running in reverse
	
	void update(); ///< MainScene will take care of calling this
	
	GameManager();
private:
	GameState LastFrameState_;
	GameState gameState_;
	unsigned LastFrameScore_;
	unsigned round1Score_;
	unsigned round2Score_;

	static unique_ptr<GameManager> sharedInstance_;
};

#endif