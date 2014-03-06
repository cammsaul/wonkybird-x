//
//  Bird.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_BIRD_H
#define WONKYBIRD_BIRD_H

#include "GameNode.h"
#include "ReflectiveClass.h"

class Bird;
typedef GamePtr<Bird> BirdPtr;
typedef vector<BirdPtr> Flock;

class Bird : public ReflectiveClass, public GameSprite {
public:
	enum class State {
		Dead,
		Falling,
		Flapping
	};
	
	Bird();
	virtual ~Bird();
	
	void InitializeAnimations(Texture2D* texture); ///< Call this after creating a new bird to init animations if needed, so Bird can reflect upon class and load the right animations
	
	virtual const Metaclass* const MetaClass() const override;
	
	virtual void Update(float dt) override;
	
	Bird::State GetState() const { return state_; }
	virtual void SetState(Bird::State birdState);
	
	virtual void ApplyTouch(unsigned numFrames) = 0; ///< apply a touch to the bird when GameState is active
	virtual void FlapAroundOnMainScreen(Flock& otherBirds) = 0; ///< Instruct the bird to start flapping around main screen
protected:
	enum State state_;
private:
	GamePtr<Animation> flappingAnimation_;
	GamePtr<Animation> fallingAnimation_;
	
	string SpriteNameWithSuffix(string suffix);
};

#endif