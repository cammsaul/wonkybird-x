//
//  NoCopy.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_NoCopy_H
#define WONKYBIRD_NoCopy_H

class NoCopy {
protected:
	NoCopy() = default;
	NoCopy(const NoCopy&) = delete;
	NoCopy& operator=(const NoCopy&) = delete;
};

class NoMove {
protected:
	NoMove() = default;
	NoMove(NoMove&&) = delete;
	NoMove& operator=(NoMove&&) = delete;
};

#endif