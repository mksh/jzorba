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

JZorbaQueryProxy::JZorbaQueryProxy(Zorba* zorbaInstance, StaticContext* staticContext, const String& querySource) {
    this->query = zorbaInstance->compileQuery(querySource, staticContext);
    this->zorba = zorbaInstance;
};

Zorba* JZorbaQueryProxy::getZorba() {
    return this->zorba;
};

XQuery* JZorbaQueryProxy::getXQuery() {
    return this->query.get();
};

JZorbaQueryProxy::~JZorbaQueryProxy() {
    delete this->query.release();
};
