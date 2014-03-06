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
	impl(new Impl())
{
	s_mainScene = this;
	
	impl->staticBackgroundLayer_ = new StaticBackgroundLayer();
	impl->gameplayLayer_ = new GameplayLayer();
	impl->scrollingBackgroundLayer_ = new ScrollingBackgroundLayer();
	impl->hudLayer_ = new HUDLayer();
	
	addChild(impl->staticBackgroundLayer_.Get(), 0); // z-order
	addChild(impl->gameplayLayer_.Get(), 2);
	addChild(impl->scrollingBackgroundLayer_.Get(), 1);
	addChild(impl->hudLayer_.Get(), 3);
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Return_to_Earth.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Shaker_2.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("Perc_2.wav");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Return_to_Earth.mp3", true);
	
	scheduleUpdate();
}

Box2DLayer& MainScene::GetBox2DLayer() {
	return *s_mainScene->impl->gameplayLayer_.Get();
}

void MainScene::update(float dt) {
	GameManager::sharedInstance().update();
	
	if (!GStateIsMainMenu()) {
		impl->hudLayer_->setLocalZOrder(300);
		impl->gameplayLayer_->setLocalZOrder(200);
	} else {
		// flip the zOrders when Bird's flies past the buttons
		static bool lockToggle = false; ///< disable further toggling until Bird is back to negative y velocity
		if (impl->gameplayLayer_->CurrentBird()->Y() > 300 && !lockToggle) {
			lockToggle = true;
			auto temp = impl->hudLayer_->getZOrder();
			impl->hudLayer_->setLocalZOrder(impl->gameplayLayer_->getLocalZOrder());
			impl->gameplayLayer_->setLocalZOrder(temp);
		} else if (impl->gameplayLayer_->CurrentBird()->Y() < 150) {
			lockToggle = false;
		}
	}
	if (GState() != LastFrameState()) {
		if (GStateIsGameOver()) {
			SimpleAudioEngine::getInstance()->playEffect("Perc_2.wav");
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		} else if (LastFrameState() != GStateMainMenu && GStateIsGetReady()) {
			SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		}
	}
}