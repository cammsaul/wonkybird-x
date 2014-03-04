EXECUTABLE = WonkyBird

INCLUDES = -include ../proj.ios/Prefix.pch -I.. -I../Classes -I../Classes/Abstract -I../Classes/GameObjects -I../Classes/Scene -I../Classes/Singletons

SOURCES = main.cpp \
	../Classes/Abstract/Box2DItem.cpp \
	../Classes/Abstract/Box2DLayer.cpp \
	../Classes/Abstract/GameLayer.cpp \
	../Classes/Abstract/GameSprite.cpp \
	../Classes/Abstract/GLES-Render.cpp \
	../Classes/Abstract/ReflectiveClass.cpp \
	../Classes/Abstract/TiledMapWithBox2D.cpp \
	../Classes/GameObjects/Bird.cpp \
	../Classes/GameObjects/Pigeon.cpp \
	../Classes/GameObjects/Pipe.cpp \
	../Classes/GameObjects/Toucan.cpp \
	../Classes/Scene/GameplayLayer.cpp \
	../Classes/Scene/HUDLayer.cpp \
	../Classes/Scene/MainScene.cpp \
	../Classes/Scene/ScrollingBackgroundLayer.cpp \
	../Classes/Scene/StaticBackgroundLayer.cpp \
	../Classes/Singletons/AppDelegate.cpp \
	../Classes/Singletons/GameManager.cpp

CXXFLAGS = "-std=c++11"

COCOS_ROOT = ../../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

SHAREDLIBS += -lcocos2d
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
