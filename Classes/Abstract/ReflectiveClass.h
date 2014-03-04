//
//  NamedClass.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_NAMEDCLASS_H
#define WONKYBIRD_NAMEDCLASS_H

/// WonkyBird with cocos2d-iOS uses a lot of reflection to look up sprite filenames,
/// rather than rework all that we'll just add an abstract class that knows its own name
class Metaclass { // should be a singleton
public:
	Metaclass(const string& name):
		name_(name)
	{}
	
	Metaclass(const Metaclass&) = delete; // no copying!
	Metaclass& operator=(const Metaclass&) = delete;
	Metaclass(Metaclass&&) = delete;
	Metaclass& operator=(Metaclass&&) = delete;
	
	bool operator==(const Metaclass& another) {
		return Name() == another.Name();
	}
	
	virtual const string& Name() const { return name_; }
private:
	const string name_;
};

class ReflectiveClass {
public:
	virtual const Metaclass* const MetaClass() const = 0;
};

#endif
