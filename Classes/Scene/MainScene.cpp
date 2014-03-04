//
//  MainScene.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "MainScene.h"
#include "GameManager.h"

static MainScene *s_mainScene = nullptr;

bool MainScene::init() {
	if (!CCScene::init()) { return false; }

	s_mainScene = this;
	
	staticBackgroundLayer_ = unique_ptr<StaticBackgroundLayer> { new StaticBackgroundLayer() };
	addChild(staticBackgroundLayer_.get());
	
	gameplayLayer_ = unique_ptr<GameplayLayer> { new GameplayLayer() };
	addChild(gameplayLayer_.get());
	
	scrollingBackgroundLayer_ = unique_ptr<ScrollingBackgroundLayer> { new ScrollingBackgroundLayer() };
	addChild(scrollingBackgroundLayer_.get());
		
	hudLayer_ = unique_ptr<HUDLayer>{ new HUDLayer() };
	addChild(hudLayer_.get());
	
	this->scheduleUpdate();
	
	return true;
}

MainScene& MainScene::SharedInstance() {
	return *s_mainScene;
}

void MainScene::update(float dt) {
	GameManager::sharedInstance().update();
}