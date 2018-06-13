#include <algorithm>

#include "jzorba.h"

using namespace std;
using namespace zorba;
// String --> Zorba string
// string --> c++ string
// const char* --> c-style string

extern "C" {


JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorba_initZorba
  (JNIEnv * env, jclass jClassObj) {
    /**
     * Initialize current JZorba instance.
     *
     */
    JZorbaProxy* proxy = new JZorbaProxy();

    setJObjectAttr__proxy(env, jClassObj, proxy);


};


JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorba_shutdownZorba
  (JNIEnv * env, jclass jClassObj) {
    /**
     * Destroy current JZorba instance.
     *
     */
    JZorbaProxy* proxy = getJObjectAttr__proxy(env, jClassObj);
    delete proxy;
    // Fill static pointer value with zero
    setJObjectAttr__proxy(env, jClassObj, NULL);
};


JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorba_addURIPath
  (JNIEnv * env, jobject that, jstring uriPath) {
    /**
     * Add URI Path to Zorba.
     *
     */
    vector<String> zorbaPaths;
    const char *path = env->GetStringUTFChars(uriPath, 0);
    String zorbaPath = String(path);

    JZorbaProxy* proxy = getJObjectAttr__proxy(env, env->GetObjectClass(that));
    StaticContext* staticContext = proxy->getStaticContext();

    staticContext->getURIPath(zorbaPaths);

    if(find(zorbaPaths.begin(), zorbaPaths.end(), zorbaPath) == zorbaPaths.end()) {
        // Add new path.
        zorbaPaths.push_back(zorbaPath);
        staticContext->setURIPath(zorbaPaths);
    };

  };

JNIEXPORT jobjectArray JNICALL Java_io_github_mksh_jzorba_JZorba_getURIPath
  (JNIEnv * env, jobject that) {

    vector<String> zorbaPaths;

    getJObjectAttr__proxy(env, env->GetObjectClass(that))->getStaticContext()->getURIPath(zorbaPaths);

    jclass jStringClass = env->FindClass("java/lang/String");
    jobjectArray javaPaths =  (jobjectArray)(env->NewObjectArray(
                                    zorbaPaths.size(),
                                    jStringClass,
                                    env->NewStringUTF("")
                                ));

    int num = 0;
    for (
        vector<String>::iterator zorbaPathIterator = zorbaPaths.begin();
        zorbaPathIterator != zorbaPaths.end();
        zorbaPathIterator++, num++
    ) {
        String path = *zorbaPathIterator;
        const char* zorbaPathChr = path.c_str();
        env->SetObjectArrayElement(javaPaths, num ,env->NewStringUTF(zorbaPathChr));
    }

    return javaPaths;

  };

};

/*
JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorba_loadDocument
  (JNIEnv *, jobject, jstring, jstring) {};

JNIEXPORT jstring JNICALL Java_io_github_mksh_jzorba_JZorba_getDocument
  (JNIEnv *, jobject, jstring) {};

JNIEXPORT jobject JNICALL Java_io_github_mksh_jzorba_JZorba_removeDocument
  (JNIEnv *, jobject, jstring) {};

*/
