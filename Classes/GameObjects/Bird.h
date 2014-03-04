//
//  Bird.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_BIRD_H
#define WONKYBIRD_BIRD_H

class CCDeleter {
public:
	template <class T>
	void operator()(T* p) {
		p->release();
	}
};

template <class T>
class CCUniquePtr : public unique_ptr<T, CCDeleter> {
public:
	CCUniquePtr():
	unique_ptr<T, CCDeleter>(new T())
	{
		unique_ptr<T, CCDeleter>::get()->retain();
	}
	CCUniquePtr(T* item):
	unique_ptr<T, CCDeleter>(item)
	{
		unique_ptr<T, CCDeleter>::get()->retain();
	}
};

#include "GameSprite.h"

class Bird;
using BirdPtr = shared_ptr<Bird>;
using Flock = unordered_set<BirdPtr>;

class Bird : public GameSprite {
public:
	enum class State {
		Dead,
		Falling,
		Flapping
	};
	
	Bird(const string& spriteFrameName);
	virtual ~Bird();
	
	enum State State() const { return state_; }
	virtual void SetState(enum State birdState);
	
	virtual void ApplyTouch(unsigned numFrames) = 0; ///< apply a touch to the bird when GameState is active
	virtual void FlapAroundOnMainScreen(Flock otherBirds) = 0; ///< Instruct the bird to start flapping around main screen
protected:
	enum State state_;
private:
	CCUniquePtr<CCAnimation> flappingAnimation_;
	CCUniquePtr<CCAnimation> fallingAnimation_;
	string SpriteNameWithSuffix(string suffix);
};

#endif