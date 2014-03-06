//
//  GamePtr.h
//  WonkyBird
//
//  Created by Cam Saul on 3/4/14.
//
//

#ifndef WONKYBIRD_GamePtr_H
#define WONKYBIRD_GamePtr_H

#include <cxxabi.h>

inline string readable_name(const char *mangled_name) {
	int status ;
	char *temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
	if(temp) {
		string result{temp};
		free(temp);
		return result;
	}
	else return mangled_name ;
}

template <class T>
class GamePtr {
public:
	GamePtr(T* obj):
		obj_(obj)
	{
		if (obj_ != nullptr) {
			obj_->retain();
		}
	}
	
	// copying
	GamePtr(const GamePtr& rhs) {
		if (this != &rhs) {
			obj_ = rhs.obj_;
			if (obj_) obj_->retain();
		}
	}
	
	GamePtr& operator=(const GamePtr& rhs) {
		if (this != &rhs) {
			obj_ = rhs.obj_;
			if (obj_) obj_->retain();
		}
		return *this;
	}
	
	// moving ok
	GamePtr(GamePtr&& rhs) {
		obj_ = rhs.obj_;
		rhs.obj_ = nullptr;
	}
	
	GamePtr& operator=(GamePtr&& rhs) {
		if (this != &rhs) {
			obj_ = rhs.obj_;
			rhs.obj_ = nullptr;
		}
		return *this;
	}
	
	GamePtr() {
		if (obj_) {
			obj_->release();
		}
	}
	
	T* operator*() { return Get(); }
	T* operator->() { return Get(); }
	T* Get() {
		if (!obj_) {
			throw runtime_error { "nullptr dereference in GamePtr<" + readable_name(typeid(T).name()) + ">" };
		}
		return obj_;
	}
	
	const T* operator*() const { return Get(); }
	const T* operator->() const { return Get(); }
	const T* Get() const { return obj_; }
	
	operator bool() const { return obj_ != nullptr; }
private:
	T* obj_ = nullptr;
};

#endif
