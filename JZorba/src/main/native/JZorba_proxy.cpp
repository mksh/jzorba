#include "jzorba.h"

using namespace zorba;

JZorbaProxy::JZorbaProxy() {
    this->store = StoreManager::getStore();
    this->zorba = Zorba::getInstance(this->store);
    this->staticCtx = this->zorba->createStaticContext();
    this->dataMgr = this->zorba->getXmlDataManager();
};

JZorbaProxy::~JZorbaProxy() {
    delete this->staticCtx.release();
    this->zorba->shutdown();
    StoreManager::shutdownStore(this->store);
};

Zorba* JZorbaProxy::getZorba() {
    return this->zorba;
};

XmlDataManager* JZorbaProxy::getXmlDataManager() {
    return this->dataMgr.get();
};

StaticContext* JZorbaProxy::getStaticContext() {
    return this->staticCtx.get();
};

JZorbaQueryProxy::JZorbaQueryProxy(JZorbaProxy* zorbaProxy, const String& querySource) {
    this->zorbaProxy = zorbaProxy;
    Zorba* zorba = zorbaProxy->getZorba();
    StaticContext* staticCtx = zorbaProxy->getStaticContext();
    this->query = zorba->compileQuery(querySource, staticCtx);

};

JZorbaProxy* JZorbaQueryProxy::getZorbaProxy() {
    return this->zorbaProxy;
};

XQuery* JZorbaQueryProxy::getXQuery() {
    return this->query.get();
};

JZorbaQueryProxy::~JZorbaQueryProxy() {
    delete this->query.release();
};
