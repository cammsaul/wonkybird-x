//
//  GameplayLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMEPLAYLAYER_H
#define WONKYBIRD_GAMEPLAYLAYER_H

#include "Box2DLayer.h"
#include "GameSprite.h"
#include "Bird.h"

class GameplayLayer : public Box2DLayer {
public:
	GameplayLayer();
	
	virtual void update(float dt) override;
	virtual void registerWithTouchDispatcher() override;
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) override;
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) override;
private:
	void UpdateMainMenu();
	void UpdateGetReady();
	void UpdateActive();
	void UpdateGameOver();

//	void AddBird(BirdPtr bird);
	void RemoveBird(BirdPtr bird);
	void AddExtraBirds();
	void RemoveExtraBirds();
	
	template <class BirdT>
	BirdPtr AddBird();
	
	BirdPtr CurrentBird() { return mainBird_; }
	void SetMainBird(BirdPtr bird) { mainBird_ = bird; }
	
	Flock birds_;
	BirdPtr toucan_;
	BirdPtr pigeon_;
	BirdPtr mainBird_;
	GameSprite ground_;
	
	unsigned touchBeginTime_; ///< time current touch began, used to keep track for touch-sensitive birds like Rasta
};

#endif