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
	
	CCSharedPtr<CCTMXLayer> Layer() { return layer_; } ///< add the layer to the GameplayLayer, not the TiledMap itself
	
	virtual void Update(float dt) override;
	
	virtual void setPosition(const CCPoint& pos) override;
	virtual const CCSize& getContentSize() const override;
	
	virtual void AddToWorld(b2World& world) override;
	
	bool Cleared() const { return cleared_; }
private:
	bool upsideDown_;
	unsigned numRows_;
	bool cleared_;
	string layerName_;
	CCSharedPtr<CCTMXLayer> layer_;
	mutable CCSize contentSize_;
	CCPoint startPosition_; ///< position pipe was at when it was added to world
};

#endif