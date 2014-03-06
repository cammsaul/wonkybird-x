//
//  MainScene.h
//  WonkyBird
//
//  Created by Cam Saul on 3/3/14.
//
//

#ifndef WONKYBIRD_MAINSCENE_H
#define WONKYBIRD_MAINSCENE_H

#include "Box2DLayer.h"

class MainScene : public Scene {
public:
	MainScene();
//	virtual ~MainScene();
	
	virtual void update(float dt) override;
	
	static Box2DLayer& GetBox2DLayer();
private:
	struct Impl;
	unique_ptr<Impl> impl_;
};

#endif
