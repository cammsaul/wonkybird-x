//
//  MainScene.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "MainScene.h"
#include "GameManager.h"
#include "StaticBackgroundLayer.h"
#include "ScrollingBackgroundLayer.h"
#include "GameplayLayer.h"
#include "HUDLayer.h"

static MainScene *s_mainScene = nullptr;

struct MainScene::Impl {
	GamePtr<StaticBackgroundLayer>		staticBackgroundLayer_;
	GamePtr<GameplayLayer>				gameplayLayer_;
	GamePtr<ScrollingBackgroundLayer>	scrollingBackgroundLayer_;
	GamePtr<HUDLayer>					hudLayer_;
};

MainScene::MainScene():
	impl_(new Impl())
{
	s_mainScene = this;
	
	impl_->staticBackgroundLayer_ = new StaticBackgroundLayer();
	impl_->gameplayLayer_ = new GameplayLayer();
	impl_->scrollingBackgroundLayer_ = new ScrollingBackgroundLayer();
	impl_->hudLayer_ = new HUDLayer();
	
	addChild(impl_->staticBackgroundLayer_.Get(), 0); // z-order
	addChild(impl_->gameplayLayer_.Get(), 2);
	addChild(impl_->scrollingBackgroundLayer_.Get(), 1);
	addChild(impl_->hudLayer_.Get(), 3);
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Return_to_Earth.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Shaker_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Perc_2.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Return_to_Earth.mp3", true);
	
	scheduleUpdate();
}

Box2DLayer& MainScene::GetBox2DLayer() {
	return *s_mainScene->impl_->gameplayLayer_.Get();
}

void MainScene::update(float dt) {
	GameManager::sharedInstance().update();
}