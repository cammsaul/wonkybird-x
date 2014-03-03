//
//  MainScene.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "MainScene.h"

using namespace cocos2d;

MainScene::MainScene():
	staticBackgroundLayer_ { nullptr }
{}


bool MainScene::init() {
	if (!CCScene::init()) { return false; }
	
	staticBackgroundLayer_ = std::unique_ptr<StaticBackgroundLayer> { new StaticBackgroundLayer{} };
	addChild(staticBackgroundLayer_.get());
	
	scrollingBackgroundLayer_ = std::unique_ptr<ScrollingBackgroundLayer> { new ScrollingBackgroundLayer{} };
	addChild(scrollingBackgroundLayer_.get());
	
	return true;
}