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
#include "GameNode.h"
#include "Bird.h"
#include "Pipe.h"
#include "GameListener.h"

class GameplayLayer : public Box2DLayer {
public:
	GameplayLayer();
	
	virtual void update(float dt) override;
	virtual bool onTouchBegan(Touch* touch, Event* event) override;
    virtual void onTouchEnded(Touch* touch, Event* event) override;
private:
	void UpdateMainMenu(float dt);
	void UpdateGetReady(float dt);
	void UpdateActive(float dt);
	void UpdateGameOver(float dt);

	void AddExtraBirds();
	void RemoveExtraBirds();
	
	void AddPipe(int size, bool upsideDown);
	void RemoveOldPipes();
	void AddRandomPipeIfNeeded();
	
	template <class BirdT>
	BirdPtr AddBird();
	
	BirdPtr& CurrentBird() { return mainBird_; }
	void SetMainBird(BirdPtr& bird) { mainBird_ = BirdPtr(bird); }
	
	Flock birds_;
	BirdPtr toucan_;
	BirdPtr pigeon_;
	BirdPtr mainBird_;
	GameSprite ground_;
	
	GameListener::Ptr listener_;
	
	deque<GamePtr<Pipe>> pipes_;
	
	unsigned touchBeginTime_; ///< time current touch began, used to keep track for touch-sensitive birds like Rasta
};

#endif