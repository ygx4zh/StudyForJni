LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := hello_jni
LOCAL_SRC_FILES := hello.c
include $(BUILD_SHARED_LIBRARY)

# 这是注释
