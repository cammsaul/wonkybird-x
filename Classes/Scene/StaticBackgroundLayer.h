//
//  StaticBackgroundLayer.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_STATICBACKGROUNDLAYER_H
#define WONKYBIRD_STATICBACKGROUNDLAYER_H

typedef shared_ptr<CCSprite> BGSprite;

class StaticBackgroundLayer : public CCLayer {
public:
	StaticBackgroundLayer();
		
	virtual void update(float dt) override;
private:
	BGSprite dayBackground_;
	BGSprite nightBackground_;
	BGSprite toucanBackground_;
	BGSprite currentBackground_;
	
	bool isDay_;
	bool IsDay() const { return isDay_; }
	void SetIsDay(bool isDay);
	
	BGSprite DayBackground();
	BGSprite NightBackground();
	BGSprite ToucanBackground();
	
	void SetCurrentBackground(BGSprite background);	
	BGSprite AddBackground(const string& filename, int zIndex = 0);
};

#endif
