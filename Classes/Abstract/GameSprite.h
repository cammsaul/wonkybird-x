//
//  GameSprite.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_GAMESPRITE_H
#define WONKYBIRD_GAMESPRITE_H

class GameSprite : public CCSprite {
public:
	GameSprite();
	
	b2Vec2 PositionForBox2D() const;
private:
	b2Body *body_;
	b2BodyDef bodyDef_;
	b2PolygonShape shape_;
	b2FixtureDef fixture_;
};

#endif