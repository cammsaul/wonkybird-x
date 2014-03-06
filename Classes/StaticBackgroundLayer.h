//
//  StaticBackgroundLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_STATICBACKGROUNDLAYER_H
#define WONKYBIRD_STATICBACKGROUNDLAYER_H

#import "GameLayer.h"

class StaticBackgroundLayer : public BasicLayer {
public:
	StaticBackgroundLayer();
		
	virtual void update(float dt) override;
private:
	GamePtr<Sprite> dayBackground_;
	GamePtr<Sprite> nightBackground_;
	GamePtr<Sprite> toucanBackground_;
	GamePtr<Sprite> currentBackground_;
	
	bool isDay_;
	bool IsDay() const { return isDay_; }
	void SetIsDay(bool isDay);
	
	GamePtr<Sprite> DayBackground();
	GamePtr<Sprite> NightBackground();
	GamePtr<Sprite> ToucanBackground();
	
	void SetCurrentBackground(GamePtr<Sprite> background);
	GamePtr<Sprite> AddBackground(const string& filename, int zIndex = 0);
};

#endif
