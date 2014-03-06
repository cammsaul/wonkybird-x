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

// dump a debug message when obj is released, useful for debugging too much copying
class DebugReleaseFn {
public:
	template <typename T>
	static void Release(T* t) {
		printf("Deleted: %s (%d)\n", readable_name(typeid(T).name()).c_str(), t->getReferenceCount());
	}
};

/// no pre-release behavior, default
class NullReleaseFn {
public:
	template <typename T>
	static void Release(T* t){};
};

template <class T, class ReleaseFn = DebugReleaseFn>
class GamePtr {
public:
	GamePtr():
		obj_(nullptr)
	{}
	
	GamePtr(T* obj):
		obj_(obj)
	{
		if (obj_ != nullptr) {
			obj_->retain();
		}
	}
	
	// copying must be done explicitly, to prevent creating wayyy to many objects
	explicit GamePtr(const GamePtr& rhs) {
		if (this != &rhs) {
			obj_ = rhs.obj_;
			if (obj_) obj_->retain();
		}
	}
	
	GamePtr& operator=(const GamePtr&) = delete;
//	GamePtr& operator=(const GamePtr& rhs) {
//		if (this != &rhs) {
//			obj_ = rhs.obj_;
//			if (obj_) obj_->retain();
//		}
//		return *this;
//	}
	
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
	
	~GamePtr() {
		if (obj_) {
			ReleaseFn::Release(obj_);
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
