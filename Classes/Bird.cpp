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
	return this->MetaClass()->Name() + "_" + suffix + ".png";
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

void Bird::InitializeAnimations(Texture2D* texture) {
	GamePtr<SpriteFrame> spriteFrame { SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteNameWithSuffix("1").c_str()) };
	initWithTexture(texture, spriteFrame->getRect());
	setDisplayFrame(spriteFrame.Get());
	
	{
		static const vector<unsigned> frameNums { 1, 2, 3, 2 };
		auto frames = Vector<SpriteFrame*>();
		for (auto frameNum : frameNums) {
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteNameWithSuffix(::to_string(frameNum)));
			frames.pushBack(frame);
		}
		flappingAnimation_ = std::move(GamePtr<Animation>(Animation::createWithSpriteFrames(frames, 0.04f)));
	}
	{
		static const vector<unsigned> frameNums { 1, 2 };
		auto frames = Vector<SpriteFrame*>();
		for (auto frameNum : frameNums) {
			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteNameWithSuffix(::to_string(frameNum)));
			frames.pushBack(frame);
		}
		fallingAnimation_ = GamePtr<Animation>(Animation::createWithSpriteFrames(frames, 0.1f));
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
			setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(SpriteNameWithSuffix("Dead").c_str()));
		} break;
		case State::Flapping: {
			runAction(CCRepeatForever::create(CCAnimate::create(flappingAnimation_.Get())));
		} break;
		case State::Falling: {
			runAction(CCRepeatForever::create(CCAnimate::create(fallingAnimation_.Get())));
		} break;
		default: assert(!"unhandled state for bird!");
	}
}

void Bird::Update(float dt) {
	GameNode::Update(dt);
	
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
	
	setRotation(RotationBox2DDegrees() * (isFlippedX() ? -1.0f : 1.0f));
	if (getRotation() > 90)  setRotation(90);
	if (getRotation() < -90) setRotation(-90);
				
	const bool lowYVelocity = abs(YVelocity()) < 0.1f;
	Body()->ApplyTorque(-(RotationBox2D() + AngularVelocity()) + (lowYVelocity ? 0 : YVelocity()), true);
	
	if (GStateIsMainMenu()) {
		SetState(YVelocity() < 0.2f ? State::Falling : State::Flapping);
		
		static const float MinXVelocityBeforeFlipping = 0.2f; ///< don't flipX until we're going at least this amount to prevent thrashing
		if		(XVelocity() < -MinXVelocityBeforeFlipping /* -1 */) setFlippedX(true);
		else if (XVelocity() > MinXVelocityBeforeFlipping)			 setFlippedX(false);
	}
	else if (GStateIsGetReady()) {
		setFlippedX(false);
		SetState(State::Flapping);
	}
	else if (GStateIsActive()) {
		setFlippedX(false);
		
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