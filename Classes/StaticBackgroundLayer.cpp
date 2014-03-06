//
//  StaticBackgroundLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "StaticBackgroundLayer.h"

struct StaticBackgroundLayer::Impl {
	StaticBackgroundLayer& this_;
	Impl(StaticBackgroundLayer& t):
		this_(t)
	{}
	
	GamePtr<Sprite> dayBackground_;
	GamePtr<Sprite> nightBackground_;
	GamePtr<Sprite> toucanBackground_;
	GamePtr<Sprite> currentBackground_;
	
	bool isDay_ = true;
	bool IsDay() const { return isDay_; }
	void SetIsDay(bool isDay);
	
	GamePtr<Sprite> DayBackground();
	GamePtr<Sprite> NightBackground();
	GamePtr<Sprite> ToucanBackground();
	
	void SetCurrentBackground(GamePtr<Sprite> background);
	GamePtr<Sprite> AddBackground(const string& filename, int zIndex = 0);
};

StaticBackgroundLayer::StaticBackgroundLayer():
	impl_(new Impl(*this))
{
	impl_->SetCurrentBackground(impl_->DayBackground());
	impl_->currentBackground_->stopAllActions(); // don't fade in the first time
	impl_->currentBackground_->setOpacity(255);
	scheduleUpdate();
}

void StaticBackgroundLayer::update(float dt) {
	if (CurrentRoundScore() == LastFrameScore()) return;
	
	if (CurrentRoundScore() != 0 && CurrentRoundScore() % CrazySwitchBackgroundsScore == 0) { // flip day / night
		impl_->SetIsDay(!impl_->IsDay());
	}
	
	if (CurrentRoundScore() > CrazyBackgroundSkewScore) {
		impl_->currentBackground_->runAction(CCSkewBy::create(1.0f, CurrentRoundScore(), 0));
	} else {
		impl_->currentBackground_->runAction(CCSkewTo::create(1.0f, 0, 0));
	}
	
	if ((random() % CrazyBackgroundToucanChance) == 0) {
		impl_->SetCurrentBackground(impl_->ToucanBackground());
	}
}

void StaticBackgroundLayer::Impl::SetIsDay(bool isDay) {
	if (isDay_ == isDay) return;
	isDay_ = isDay;
	
	SetCurrentBackground(isDay ? DayBackground() : NightBackground());
}

void StaticBackgroundLayer::Impl::SetCurrentBackground(GamePtr<Sprite> background) {
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

GamePtr<Sprite> StaticBackgroundLayer::Impl::AddBackground(const string& filename, int zIndex) {
	auto bgSprite = GamePtr<Sprite> { Sprite::create(filename) };
	assert(bgSprite);
	bgSprite->Node::setPosition(ScreenHalfWidth(), ScreenHalfHeight());
	
	// scale BG as needed
	bgSprite->setScaleX(ScreenWidth() / 640.0f);
	bgSprite->setScaleY(ScreenHeight() / 1136.0f);
	
	this_.addChild(bgSprite.Get(), zIndex);
	return bgSprite;
}

GamePtr<Sprite> StaticBackgroundLayer::Impl::DayBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background@2x.png", 0);
	}
	return dayBackground_;
}

GamePtr<Sprite> StaticBackgroundLayer::Impl::NightBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background_Night@2x.png", 2);
	}
	return dayBackground_;
}

GamePtr<Sprite> StaticBackgroundLayer::Impl::ToucanBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background_Toucan@2x.png", 1);
	}
	return dayBackground_;
}
