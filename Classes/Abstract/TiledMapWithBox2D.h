//
//  TiledMapWithBox2D.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_TiledMapWithBox2D_H
#define WONKYBIRD_TiledMapWithBox2D_H

#include "GameSprite.h"

class TiledMapWithBox2D: public virtual CCTMXTiledMap, public virtual GameNode {
public:
	TiledMapWithBox2D(const string& tmxFile);
};

#endif