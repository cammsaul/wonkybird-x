//
//  Bird.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#include <cmath>

#include "Bird.h"

string Bird::SpriteNameWithSuffix(string suffix) {
	return MetaClass()->Name() + "_" + suffix + ".png";
}


Bird::Bird():
	ReflectiveClass(),
	GameSprite(),
	state_((enum State)-1) // next call will trigger animation change
{
//	BodyDef()->gravityScale = 2.0f;
	static bool hasLoadedShapeDefs = false;
	if (!hasLoadedShapeDefs) {
		hasLoadedShapeDefs = true;
		#warning Need to load the shape cache here
	}
}

void Bird::InitializeAnimations(CCTexture2D* texture) {
	if (hasInitializedAnimations_) return;
	
	CCUniquePtr<CCSpriteFrame> spriteFrame { CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SpriteNameWithSuffix("1").c_str()) };
	initWithTexture(texture, spriteFrame->getRect());
	setDisplayFrame(spriteFrame.get());
	
	{
		static const vector<unsigned> frameNums { 1, 2, 3, 2 };
		auto frames = CCUniquePtr<CCArray>(CCArray::create());
		for (auto frameNum : frameNums) {
			auto frame = CCUniquePtr<CCSpriteFrame>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SpriteNameWithSuffix(::to_string(frameNum)).c_str()));
			frames->addObject(frame.get());
		}
		flappingAnimation_ = CCUniquePtr<CCAnimation>(CCAnimation::createWithSpriteFrames(frames.get(), 0.04f));
	}
	{
		static const vector<unsigned> frameNums2 { 1, 2 };
		auto frames2 = CCUniquePtr<CCArray>(CCArray::create());
		for (auto frameNum : frameNums2) {
			auto frame = CCUniquePtr<CCSpriteFrame>(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SpriteNameWithSuffix(::to_string(frameNum)).c_str()));
			frames2->addObject(frame.get());
		}
		fallingAnimation_ = CCUniquePtr<CCAnimation>(CCAnimation::createWithSpriteFrames(frames2.get(), 0.1f));
	}
	
	SetState(Bird::State::Flapping);
}

void Bird::SetState(enum Bird::State state) {
	if (state_ == state) return;
	stopAllActions();
	
	state_ = state;
	switch (state) {
		case State::Dead: {
			printf("Bird -> dead.\n");
			setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(SpriteNameWithSuffix("Dead").c_str()));
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

void Bird::Update(float dt) {
	GameSprite::Update(dt);
	
	if (state_ == State::Dead) return;
	
	// clamp to screen as needed
	if (GStateIsMainMenu() || GStateIsActive()) {
		const float minX = 0;
		const float maxX = ScreenWidth();
		if (X() < minX) {
			SetX(minX);
			SetXVelocity(1);
		} else if (X() > maxX) {
			SetXVelocity(-1);
			SetX(maxX);
		}
		if		(Y() < 0)				SetYVelocity(1);
		else if (Y() > ScreenHeight())	SetYVelocity(-1);
	}
	
	setRotation(RotationBox2DDegrees() * (isFlipX() ? -1.0f : 1.0f));
	if (getRotation() > 90)  setRotation(90);
	if (getRotation() < -90) setRotation(-90);
				
	const bool lowYVelocity = abs(YVelocity()) < 0.1f;
	Body()->ApplyTorque(-(RotationBox2D() + AngularVelocity()) + (lowYVelocity ? 0 : YVelocity()));
	
	if (GStateIsMainMenu()) {
		SetState(YVelocity() < 0.2f ? State::Falling : State::Flapping);
		
		static const float MinXVelocityBeforeFlipping = 0.2f; ///< don't flipX until we're going at least this amount to prevent thrashing
		if		(XVelocity() < -MinXVelocityBeforeFlipping /* -1 */) setFlipX(true);
		else if (XVelocity() > MinXVelocityBeforeFlipping)			 setFlipX(false);
	}
	else if (GStateIsGetReady()) {
		setFlipX(false);
		SetState(State::Flapping);
	}
	else if (GStateIsActive()) {
		setFlipX(false);
		
		if (IsOffscreen() || !Body()->IsAwake() || (YVelocity() == 0 && State() == State::Falling)) {
			SetState(State::Dead);
		} else if (YVelocity() <= 0.2f) {
			SetState(State::Falling);
		} else {
			SetState(State::Flapping);
		}
	}
}

const Metaclass* const Bird::MetaClass() const {
	static const Metaclass m = { "Bird" };
	return &m;
}

Bird::~Bird() {
	printf("~Bird()\n");
}