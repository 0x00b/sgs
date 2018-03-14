LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp\
                   ../../Classes/AppDelegate.cpp\
                   ../../Classes/HelloWorldScene.cpp\
				   ../../Classes/Fight/FightMainScene.cpp\
				   ../../Classes/Home/ReadyHomeScene2.cpp\
				   ../../Classes/libs/base64.cpp\
				   ../../Classes/libs/jsoncpp.cpp\
				   ../../Classes/Login/LoginScene.cpp\
				   ../../Classes/Mode/SelectModeScene.cpp\
				   ../../Classes/model/card.cpp\
				   ../../Classes/model/gameattr.cpp\
				   ../../Classes/model/hero.cpp\
				   ../../Classes/model/player.cpp\
				   ../../Classes/model/room.cpp\
				   ../../Classes/model/sgscard.cpp\
				   ../../Classes/model/sgsgameattr.cpp\
				   ../../Classes/Pop/SearchHomeLayer.cpp\
				   ../../Classes/SelectHero2Layer/SelectHero2Layer.cpp\
				   ../../Classes/Do_function.cpp\
				   ../../Classes/Do_function_mm.cpp\
				   ../../Classes/ppacket.cpp\
				   ../../Classes/text.cpp\
				   ../../Classes/Login/RegisterScene.cpp\
				   ../../Classes/Fight/FightEndLoseLayer.cpp\
				   ../../Classes/Fight/FightEndWinLayer.cpp\
				   ../../Classes/HeroDetail/HeroDetail.cpp\
				   ../../Classes/CardInfo/CardInfoScene.cpp
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
					$(LOCAL_PATH)/../../Classes/boost.asio.1.0.159\
					$(LOCAL_PATH)/../../Classes/boost.asio.1.0.159/boost\
					$(LOCAL_PATH)/../../Classes/boost.asio.1.0.159/boost/asio\
					$(LOCAL_PATH)/../../Classes/Fight\
					$(LOCAL_PATH)/../../Classes/Home\
					$(LOCAL_PATH)/../../Classes/jsonproto\
					$(LOCAL_PATH)/../../Classes/libs\
					$(LOCAL_PATH)/../../Classes/Login\
					$(LOCAL_PATH)/../../Classes/Mode\
					$(LOCAL_PATH)/../../Classes/model\
					$(LOCAL_PATH)/../../Classes/Pop\
					$(LOCAL_PATH)/../../Classes/PopHeroDetail\
					$(LOCAL_PATH)/../../Classes/SelectHero2Layer\
					$(LOCAL_PATH)/../../Classes/CardInfo
								   

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
