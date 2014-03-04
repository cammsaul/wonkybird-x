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

class MainScene : public CCScene {
public:
	virtual bool init() override;
	
	virtual void update(float dt) override;
private:
	unique_ptr<StaticBackgroundLayer> staticBackgroundLayer_;
	unique_ptr<ScrollingBackgroundLayer> scrollingBackgroundLayer_;
	unique_ptr<GameplayLayer> gameplayLayer_;
	unique_ptr<HUDLayer> hudLayer_;
};

#endif
