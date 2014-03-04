//
//  Bird.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_BIRD_H
#define WONKYBIRD_BIRD_H

#include "GameSprite.h"
#include "ReflectiveClass.h"

class Bird;
using BirdPtr = CCSharedPtr<Bird>;
using Flock = vector<BirdPtr>;

class Bird : public ReflectiveClass, public GameSprite {
public:
	enum class State {
		Dead,
		Falling,
		Flapping
	};
	
	Bird();
	virtual ~Bird();
	
	void InitializeAnimations(CCTexture2D* texture); ///< Call this after creating a new bird to init animations if needed, so Bird can reflect upon class and load the right animations
	
	virtual const Metaclass* const MetaClass() const override;
	
	virtual void Update(float dt) override;
	
	enum State State() const { return state_; }
	virtual void SetState(enum State birdState);
	
	virtual void ApplyTouch(unsigned numFrames) = 0; ///< apply a touch to the bird when GameState is active
	virtual void FlapAroundOnMainScreen(Flock otherBirds) = 0; ///< Instruct the bird to start flapping around main screen
protected:
	enum State state_;
private:
	bool hasInitializedAnimations_;
	CCUniquePtr<CCAnimation> flappingAnimation_;
	CCUniquePtr<CCAnimation> fallingAnimation_;
	
	string SpriteNameWithSuffix(string suffix);
};

#endif