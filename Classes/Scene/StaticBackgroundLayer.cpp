//
//  StaticBackgroundLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "StaticBackgroundLayer.h"

using BGSprite = shared_ptr<CCSprite>;

StaticBackgroundLayer::StaticBackgroundLayer():
	dayBackground_			{ nullptr },
	nightBackground_		{ nullptr },
	toucanBackground_		{ nullptr },
	currentBackground_		{ nullptr },
	isDay_					{ true }
{
	SetCurrentBackground(DayBackground());
	scheduleUpdate();
}

void StaticBackgroundLayer::update(float dt) {
	if (CurrentRoundScore() == LastFrameScore()) return;
	
	if (CurrentRoundScore() != 0 && CurrentRoundScore() % CrazySwitchBackgroundsScore == 0) { // flip day / night
		SetIsDay(!IsDay());
	}
	
	if (CurrentRoundScore() > CrazyBackgroundSkewScore) {
		currentBackground_->runAction(CCSkewBy::create(1.0f, CurrentRoundScore(), 0));
	} else {
		currentBackground_->runAction(CCSkewTo::create(1.0f, 0, 0));
	}
	
	if ((random() % CrazyBackgroundToucanChance) == 0) {
		SetCurrentBackground(ToucanBackground());
	}
}

void StaticBackgroundLayer::SetIsDay(bool isDay) {
	if (isDay_ == isDay) return;
	isDay_ = isDay;
	
	SetCurrentBackground(isDay ? DayBackground() : NightBackground());
}

void StaticBackgroundLayer::SetCurrentBackground(BGSprite background) {
	if (currentBackground_ == background) return;
	
	background->setOpacity(0);
	
	// fade out old background
	if (currentBackground_) {
		currentBackground_->runAction(CCFadeOut::create(10.0f));
	}
	
	// fade in new one
	background->runAction(CCFadeIn::create(10.0f));
	
	currentBackground_ = background;
}

BGSprite StaticBackgroundLayer::AddBackground(const string& filename, int zIndex) {
	auto bgSprite = BGSprite { CCSprite::create(filename.c_str()) };
	assert(bgSprite);
	bgSprite->CCNode::setPosition(ScreenHalfWidth(), ScreenHalfHeight());
	addChild(bgSprite.get(), zIndex);
	return bgSprite;
}

BGSprite StaticBackgroundLayer::DayBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background@2x.png", 0);
	}
	return dayBackground_;
}

BGSprite StaticBackgroundLayer::NightBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background_Night@2x.png", 2);
	}
	return dayBackground_;
}

BGSprite StaticBackgroundLayer::ToucanBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background_Toucan@2x.png", 1);
	}
	return dayBackground_;
}
