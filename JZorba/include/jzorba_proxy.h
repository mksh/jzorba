#ifndef _JZORBA_PROXY_H
#define _JZORBA_PROXY_H

#include <jni.h>

#include <zorba/api_shared_types.h>
#include <zorba/external_module.h>
#include <zorba/function.h>
#include <zorba/zorba.h>
#include <zorba/xquery.h>
#include <zorba/singleton_item_sequence.h>
#include <zorba/store_manager.h>
#include <zorba/xquery_exception.h>
#include <zorba/zorba_string.h>

class JZorbaProxy {
    private:
        void* store;
        zorba::Zorba* zorba;
        zorba::StaticContext_t staticCtx;
        zorba::XmlDataManager_t dataMgr;
    public:
        zorba::Zorba* getZorba();
        zorba::StaticContext* getStaticContext();
        zorba::XmlDataManager* getXmlDataManager();
        JZorbaProxy();
        ~JZorbaProxy();
};

class JZorbaQueryProxy {
    private:
        zorba::XQuery_t query;
        JZorbaProxy* zorbaProxy;
    public:
        zorba::XQuery* getXQuery();
        JZorbaProxy* getZorbaProxy();
        JZorbaQueryProxy(JZorbaProxy* proxy, const zorba::String&);
        ~JZorbaQueryProxy();
};

#endif
