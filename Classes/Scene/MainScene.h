//
//  MainScene.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_MAINSCENE_H
#define WONKYBIRD_MAINSCENE_H

#include "StaticBackgroundLayer.h"
#include "ScrollingBackgroundLayer.h"
#include "GameplayLayer.h"
#include "HUDLayer.h"

class MainScene : public cocos2d::CCScene {
public:
	MainScene();
	
	virtual bool init() override;
	
//	virtual void update(float dt) override;
private:
	std::unique_ptr<StaticBackgroundLayer> staticBackgroundLayer_;
	std::unique_ptr<ScrollingBackgroundLayer> scrollingBackgroundLayer_;
	std::unique_ptr<GameplayLayer> gameplayLayer_;
	std::unique_ptr<HUDLayer> hudLayer_;
};

#endif
