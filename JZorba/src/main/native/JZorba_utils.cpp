#include <stdint.h>

#include "jzorba.h"

using namespace zorba;


extern "C" {

// JZorba attribute setter
void setJObjectAttr__void(JNIEnv * env, jclass objClass, const char* fieldName, void* attrValue) {
    jfieldID fieldID = env->GetStaticFieldID(objClass, fieldName, "J");
    uintptr_t ptrValue = reinterpret_cast<uintptr_t>(attrValue);
    env->SetStaticLongField(objClass, fieldID, (long)ptrValue);
    fflush(stdout);
};

// JZorbaQuery attribute setter
void setJQueryAttr__void(JNIEnv * env, jobject obj, const char* fieldName, void* attrValue) {
    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldID = env->GetFieldID(objClass, fieldName, "J");
    uintptr_t ptrValue = reinterpret_cast<uintptr_t>(attrValue);
    env->SetLongField(obj, fieldID, (long)ptrValue);
};

void setJQueryAttr__String(JNIEnv * env, jobject obj, const char* fieldName, const jstring& attrValue) {
    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldID = env->GetFieldID(objClass, fieldName, "Ljava/lang/String;");
    // TODO: re-think it, as may be slow
    env->SetObjectField(obj, fieldID, attrValue);
};

jstring getJQueryAttr__String(JNIEnv * env, jobject obj, const char* fieldName) {
    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldID = env->GetFieldID(objClass, fieldName, "Ljava/lang/String;");
    jstring jCharField = (jstring)(env->GetObjectField(obj, fieldID));
    return jCharField;
};


// JZorba attribute getter
unsigned long getJObjectAttr__void(JNIEnv * env, jclass objClass, const char* fieldName) {
    jfieldID fieldID = env->GetStaticFieldID(objClass, fieldName, "J");
    unsigned long pointerValue = env->GetStaticLongField(objClass, fieldID);
    return pointerValue;
};

void setJObjectAttr__proxy(JNIEnv * env, jclass objClass, JZorbaProxy* attrValue) {
    void *pZorba = attrValue;
    setJObjectAttr__void(env, objClass, "cZorbaProxy", pZorba);
};


JZorbaProxy* getJObjectAttr__proxy(JNIEnv * env, jclass objClass) {
    unsigned long ptr = getJObjectAttr__void(env, objClass, "cZorbaProxy");
    return reinterpret_cast<JZorbaProxy*>(ptr);
};

JZorbaProxy* getJQueryAttr__proxy(JNIEnv * env, jobject obj) {
    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldID = env->GetFieldID(objClass, "zorba", "J");
    jobject zorba = env->GetObjectField(obj, fieldID);
    jclass zorbaClass = env->GetObjectClass(zorba);
    return getJObjectAttr__proxy(env, zorbaClass);
};


JZorbaQueryProxy* getJQueryAttr__JZorbaQueryProxy(JNIEnv * env, jobject obj) {
    jclass objClass = env->GetObjectClass(obj);
    jfieldID fieldID = env->GetFieldID(objClass, "cZorbaQryProxy", "J");
    unsigned long ptr = env->GetLongField(obj, fieldID);
    return reinterpret_cast<JZorbaQueryProxy*>(ptr);
};

};
