//
//  MainScene.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_MAINSCENE_H
#define WONKYBIRD_MAINSCENE_H

#include <memory>
#include <cocos2d.h>

#include "StaticBackgroundLayer.h"
#include "ScrollingBackgroundLayer.h"
#include "GameplayLayer.h"
#include "HUDLayer.h"

class MainScene : public cocos2d::CCScene {
public:
	virtual bool init() override;

	MainScene();
private:
	std::unique_ptr<StaticBackgroundLayer> staticBackgroundLayer_;
	std::unique_ptr<ScrollingBackgroundLayer> scrollingBackgroundLayer_;
	std::unique_ptr<GameplayLayer> gameplayLayer_;
	std::unique_ptr<HUDLayer> hudLayer_;
};

#endif
