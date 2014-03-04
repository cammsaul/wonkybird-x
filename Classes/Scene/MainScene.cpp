//
//  MainScene.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "MainScene.h"
#include "GameManager.h"

bool MainScene::init() {
	if (!CCScene::init()) { return false; }
	
	staticBackgroundLayer_ = unique_ptr<StaticBackgroundLayer> { new StaticBackgroundLayer() };
	addChild(staticBackgroundLayer_.get());
	
	scrollingBackgroundLayer_ = unique_ptr<ScrollingBackgroundLayer> { new ScrollingBackgroundLayer() };
	addChild(scrollingBackgroundLayer_.get());
	
	gameplayLayer_ = unique_ptr<GameplayLayer> { new GameplayLayer() };
	addChild(gameplayLayer_.get());
	
	hudLayer_ = unique_ptr<HUDLayer>{ new HUDLayer() };
	addChild(hudLayer_.get());
	
	this->scheduleUpdate();
	
	return true;
}

void MainScene::update(float dt) {
	GameManager::sharedInstance()->update();
}