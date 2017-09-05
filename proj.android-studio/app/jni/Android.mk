LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/CustomFunctions/GameBarrageFunctions.cpp \
				   ../../../Classes/CustomFunctions/GameCustomFunction.cpp \
				   ../../../Classes/CustomFunctions/GameEnemyFunctions.cpp \
				   ../../../Classes/GameObjects/GameBaseObject.cpp \
				   ../../../Classes/GameObjects/GameCommonObject.cpp \
				   ../../../Classes/GameObjects/GameEnemy.cpp \
				   ../../../Classes/GameObjects/GameEnemyShot.cpp \
				   ../../../Classes/GameObjects/GameExplosion.cpp \
				   ../../../Classes/GameObjects/GamePlayer.cpp \
				   ../../../Classes/GameObjects/GamePlayerShot.cpp \
				   ../../../Classes/Scenes/SceneLogo.cpp \
				   ../../../Classes/Scenes/SceneStage.cpp \
				   ../../../Classes/AppDelegate.cpp \
				   ../../../Classes/Common.cpp \
				   ../../../Classes/GameUtil.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
