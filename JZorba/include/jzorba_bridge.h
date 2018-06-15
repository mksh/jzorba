#ifndef _JZORBA_BRIDGE_H
#define _JZORBA_BRIDGE_H

#include <jni.h>
#include "jzorba_proxy.h"

extern "C" {

    // Bridge methods for C++ <-> Java state interaction.

    // JZorbaQuery manipulators.
    // manipulate void
    void setJQueryAttr__void(JNIEnv *, jobject, const char*, void*);

    // manipulate strings
    void setJQueryAttr__String(JNIEnv *, jobject, const char*, const jstring&);
    jstring getJQueryAttr__String(JNIEnv *, jobject , const char*);

    // Getters and setters for JZorba
    // manipulate void
    void setJObjectAttr__void(JNIEnv* , jclass, const char*, void*);
    unsigned long getJObjectAttr__void(JNIEnv* , jclass, const char*);

    // manipulate typed
    JZorbaProxy* getJObjectAttr__proxy(JNIEnv*, jclass);
    void setJObjectAttr__proxy(JNIEnv* , jclass, JZorbaProxy*);
    JZorbaProxy* getJQueryAttr__proxy(JNIEnv * env, jobject obj);

    // JZorbaQueryProxy access
    JZorbaQueryProxy* getJQueryAttr__JZorbaQueryProxy(JNIEnv *, jobject);

    void throwJVMQueryException(JNIEnv*, jobject, const std::exception&);

}

#endif
