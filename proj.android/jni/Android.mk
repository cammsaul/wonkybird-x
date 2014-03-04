LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
			../../Classes/Abstract/Box2DItem.cpp \
			../../Classes/Abstract/Box2DLayer.cpp \
			../../Classes/Abstract/GameLayer.cpp \
			../../Classes/Abstract/GameSprite.cpp \
			../../Classes/Abstract/GLES-Render.cpp \
			../../Classes/Abstract/ReflectiveClass.cpp \
			../../Classes/Abstract/TiledMapWithBox2D.cpp \
			../../Classes/GameObjects/Bird.cpp \
			../../Classes/GameObjects/Pigeon.cpp \
			../../Classes/GameObjects/Pipe.cpp \
			../../Classes/GameObjects/Toucan.cpp \
			../../Classes/Scene/GameplayLayer.cpp \
			../../Classes/Scene/HUDLayer.cpp \
			../../Classes/Scene/MainScene.cpp \
			../../Classes/Scene/ScrollingBackgroundLayer.cpp \
			../../Classes/Scene/StaticBackgroundLayer.cpp \
			../../Classes/Singletons/AppDelegate.cpp \
			../../Classes/Singletons/GameManager.cpp

SRC_ROOT = $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES := $(SRC_ROOT) $(SRC_ROOT)/Abstract $(SRC_ROOT)/GameObjects $(SRC_ROOT)/Scene $(SRC_ROOT)/Singletons # /Users/cam/cocos2d-x-2.2.2/projects/WonkyBird/proj.ios/Vendor
LOCAL_CPPFLAGS := -std=c++11 -include /Users/cam/WonkyBird-x/proj.ios/Prefix.pch

# LOCAL_LDFLAGS :== --warn-unresolved-symbols -rdynamic

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
# $(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
# $(call import-module,CocosDenshion/android)
# $(call import-module,extensions)
$(call import-module,external/Box2D)
# $(call import-module,external/chipmunk)
