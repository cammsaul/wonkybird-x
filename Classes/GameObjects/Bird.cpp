//
//  Bird.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//


#include "Bird.h"

string Bird::SpriteNameWithSuffix(string suffix) {
	printf("typeinfo: %s\n", typeid(this).name());
	return "Toucan" + string("_") + suffix + ".png";
}


Bird::Bird(const string& spriteFrameName):
	GameSprite(spriteFrameName),
	state_((enum State)-1) // next call will trigger animation change
{
	static const vector<unsigned> frameNums { 1, 2, 3, 2 };
	auto frames = CCUniquePtr<CCArray>(CCArray::create());
	for (auto frameNum : frameNums) {
		auto frame = CCUniquePtr<CCAnimationFrame>();
		frame->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SpriteNameWithSuffix(to_string(frameNum)).c_str()), 0.01f, nullptr);
		frames->addObject(frame.get());
	}
	
	flappingAnimation_ = CCUniquePtr<CCAnimation>(CCAnimation::create(frames.get(), 0.04f));
	
	static const vector<unsigned> frameNums2 { 1, 2 };
	auto frames2 = CCUniquePtr<CCArray>(CCArray::create());
	for (auto frameNum : frameNums2) {
		auto frame = CCUniquePtr<CCAnimationFrame>();
		frame->initWithSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SpriteNameWithSuffix(to_string(frameNum)).c_str()), 0.05f, nullptr);
		frames2->addObject(frame.get());
	}
	fallingAnimation_ = CCUniquePtr<CCAnimation>(CCAnimation::create(frames.get(), 0.10f));
	
	SetState(State::Flapping);
}

void Bird::SetState(enum Bird::State state) {
	if (state_ == state) return;
	stopAllActions();
	
	state_ = state;
	switch (state) {
		case State::Dead: {
			printf("Bird -> dead.\n");
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("Dead"));
		} break;
		case State::Flapping: {
			runAction(CCRepeatForever::create(CCAnimate::create(flappingAnimation_.get())));
		} break;
		case State::Falling: {
			runAction(CCRepeatForever::create(CCAnimate::create(fallingAnimation_.get())));
		} break;
		default: assert(!"unhandled state for bird!");
	}
}

Bird::~Bird() {
	printf("~Bird()\n");
}