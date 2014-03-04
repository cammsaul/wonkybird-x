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