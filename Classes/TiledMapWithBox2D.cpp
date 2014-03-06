//
//  TiledMapWithBox2D.cpp
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#include "TiledMapWithBox2D.h"

TiledMapWithBox2D::TiledMapWithBox2D(const string& tmxFile)
{
	initWithTMXFile(tmxFile.c_str());
}

const Point& TiledMapWithBox2D::getPosition() const {
	return TMXTiledMap::getPosition();
}

void TiledMapWithBox2D::setPosition(const Point &position) {
	TMXTiledMap::setPosition(position);
}

const Size& TiledMapWithBox2D::getContentSize() const {
	return TMXTiledMap::getContentSize();
}