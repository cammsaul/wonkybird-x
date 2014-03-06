//
//  TiledMapWithBox2D.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_TiledMapWithBox2D_H
#define WONKYBIRD_TiledMapWithBox2D_H

#include "GameNode.h"

class TiledMapWithBox2D: public TMXTiledMap, public GameNode {
public:
	TiledMapWithBox2D(const string& tmxFile);
	
	virtual const Point& getPosition() const override;
	virtual void setPosition(const Point &position) override;
	virtual const Size& getContentSize() const override;
};

#endif