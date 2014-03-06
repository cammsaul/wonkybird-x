//
//  Pipe.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_Pipe_H
#define WONKYBIRD_Pipe_H

#include "TiledMapWithBox2D.h"

class Pipe : public TiledMapWithBox2D {
public:
	Pipe(unsigned size, bool upsideDown);
	~Pipe();
	
	GamePtr<TMXLayer> Layer() { return layer_; } ///< add the layer to the GameplayLayer, not the TiledMap itself
	
	virtual void Update(float dt) override;
	
	virtual void setPosition(const Point& pos) override;
	virtual const Size& getContentSize() const override;
	
	virtual void AddToWorld(b2World& world) override;
	
	bool Cleared() const { return cleared_; }
private:
	bool upsideDown_;
	unsigned numRows_;
	bool cleared_;
	string layerName_;
	GamePtr<TMXLayer> layer_;
	mutable Size contentSize_;
	Point startPosition_; ///< position pipe was at when it was added to world
};

#endif