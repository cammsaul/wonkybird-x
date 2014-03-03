//
//  StaticBackgroundLayer.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include "StaticBackgroundLayer.h"
#include "Constants.h"

StaticBackgroundLayer::StaticBackgroundLayer():
	dayBackground_			{ nullptr },
	nightBackground_		{ nullptr },
	toucanBackground_		{ nullptr }
{
	DayBackground(); // will add BG to screengit st
}

unique_ptr<CCSprite> StaticBackgroundLayer::AddBackground(const std::string& filename) {
	auto bgSprite = unique_ptr<CCSprite> { CCSprite::create(filename.c_str()) };
	assert(bgSprite);
	bgSprite->CCNode::setPosition(ScreenHalfWidth(), ScreenHalfHeight());
	addChild(bgSprite.get());
	return bgSprite;
}

CCSprite* StaticBackgroundLayer::DayBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background@2x.png");
	}
	return dayBackground_.get();
}

CCSprite* StaticBackgroundLayer::NightBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background_Night@2x.png");
	}
	return dayBackground_.get();
}

CCSprite* StaticBackgroundLayer::ToucanBackground() {
	if (!dayBackground_) {
		dayBackground_ = AddBackground("Background_Toucan@2x.png");
	}
	return dayBackground_.get();
}

CCSprite* StaticBackgroundLayer::CurrentBackground() {
	return DayBackground(); // TODO
}
