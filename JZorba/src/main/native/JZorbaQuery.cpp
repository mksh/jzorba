#include <algorithm>
#include <string>

#include "jzorba.h"

using namespace std;
using namespace zorba;
// String --> Zorba string
// string --> c++ string
// const char* --> c-style string
// jstring - Java string

#ifdef __cplusplus
extern "C" {
#endif 


JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorbaQuery_doCompile
  (JNIEnv * env, jobject that, jobject jZorba) {

    JZorbaProxy* proxy = getJObjectAttr__proxy(env, env->GetObjectClass(jZorba));
    Zorba* zorbaInstance = proxy->getZorba();
    const StaticContext* staticCtx = proxy->getStaticContext();

    // Convert query source string
    jstring jQ = getJQueryAttr__String(env, that, "querySource");
    // Don't copy chars: access JVM values directly here.
    const char* q = env->GetStringUTFChars(jQ, JNI_FALSE);

    try {
        JZorbaQueryProxy* queryProxy = new JZorbaQueryProxy(proxy, String(q));
        env->ReleaseStringUTFChars(jQ, q);
        setJQueryAttr__void(env, that, "cZorbaQryProxy", queryProxy);
    } catch (XQueryException const& e) {
        setJQueryAttr__String(env, that, "queryErrorSourceURI", env->NewStringUTF(e.source_uri()));
        std::ostringstream ns;
        ns << e.source_line();
        setJQueryAttr__String(env, that, "queryErrorSourceLine", env->NewStringUTF(ns.str().c_str()));
        setJQueryAttr__String(env, that, "queryError", env->NewStringUTF(e.what()));
        throwJVMQueryException(env, that, e);
    } catch (ZorbaException const& e) {
        setJQueryAttr__String(env, that, "queryError", env->NewStringUTF(e.what()));
        throwJVMQueryException(env, that, e);
    };

    // Don't uncomment it: JVM will take care of the string for us :3
    // delete q;
}

JNIEXPORT jstring JNICALL Java_io_github_mksh_jzorba_JZorbaQuery_execute
  (JNIEnv * env, jobject that)
{
    JZorbaQueryProxy* queryProxy = getJQueryAttr__JZorbaQueryProxy(env, that);

    ostringstream os;
    try {
        Zorba_SerializerOptions_t serializationOptions;
        serializationOptions.indent = ZORBA_INDENT_NO;
        serializationOptions.omit_xml_declaration = ZORBA_OMIT_XML_DECLARATION_YES;
        queryProxy->getXQuery()->execute(os, &serializationOptions);
    } catch (const ZorbaException& e) {
        throwJVMQueryException(env, that, e);
    };
    return env->NewStringUTF(os.str().c_str());
};

/*
 * Class:     io_github_mksh_jzorba_JZorbaQuery
 * Method:    loadContextDocument
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorbaQuery_doLoadContextDocument
  (JNIEnv * env, jobject that, jstring documentString) {
    JZorbaQueryProxy* queryProxy = getJQueryAttr__JZorbaQueryProxy(env, that);
    Zorba* zorba = queryProxy->getZorbaProxy()->getZorba();
    XmlDataManager_t xmlDataManager = zorba->getXmlDataManager();
    const char * documentContent = env->GetStringUTFChars(documentString, JNI_FALSE);
    try {
        istringstream is(documentContent);
        Item item = xmlDataManager->parseXML(is);
        // JNI memory access not needed any more.
        env->ReleaseStringUTFChars(documentString, documentContent);
        DynamicContext* context = queryProxy->getXQuery()->getDynamicContext();
        context->setContextItem(item);
    } catch (const ZorbaException& e) {
        env->ReleaseStringUTFChars(documentString, documentContent);
        // Throw an exception if invalid XML is received.
        throwJVMQueryException(env, that, e);
    };
    
  };

/*
 * Class:     io_github_mksh_jzorba_JZorbaQuery
 * Method:    setContextDocument
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_mksh_jzorba_JZorbaQuery_setContextDocument
  (JNIEnv *, jobject, jstring) {

  };

#ifdef __cplusplus
}
#endif
