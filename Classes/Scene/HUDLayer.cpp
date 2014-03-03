//
//  HUDLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "HUDLayer.h"
#include "Constants.h"

HUDLayer::HUDLayer():
GameLayer("HUD"),
sprites_()
{
	sprites_["Title.png"] = unique_ptr<CCSprite>(new CCSprite());
	auto titleLabel = sprites_["Title.png"].get();
	titleLabel->initWithSpriteFrameName("Title.png");
	titleLabel->setPosition({ScreenHalfWidth(), ScreenHeight() * 0.75f});
	addChild(titleLabel);
}