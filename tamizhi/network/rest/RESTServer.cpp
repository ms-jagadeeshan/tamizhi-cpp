#include "tamizhi/network/rest/RESTServer.h"

/********************************************************************/

tmz::nwRESTServer::nwRESTServer(bool secure)
{
    if (!tmz::nwRESTServer::IsInitializedVar())
    {
        tmz::nwRESTServer::mIsInit = true;
        tmz::nwRESTServer::startup(secure);
        const auto& ref = getInstance();

        // ref->mThreadPool = std::make_shared<crThreadPool>(std::thread::hardware_concurrency());
        if (!ref->mSecure)
        {
            ref->mServer = std::make_shared<HttpServer>();
            ref->mServer->config.thread_pool_size = 5;
        }
    }
}

/********************************************************************/

tmz::nwRESTServer::~nwRESTServer()
{
    const auto& ref = getInstance();
    ref->stop();
}

/********************************************************************/

void tmz::nwRESTServer::isSecure(const bool& secure) const
{
    const auto& ref = getInstance();
    ref->mSecure = secure;
}

/********************************************************************/

void tmz::nwRESTServer::setPort(const uint16_t& port)
{
    const auto& ref = getInstance();

    if (ref->mSecure)
        ref->mSecureServer->config.port = port;
    else
        ref->mServer->config.port = port;
}

/********************************************************************/

bool tmz::nwRESTServer::registerPOSTRequest(const std::string& resourcePost, const RestFunction& restFunction)
{
    const auto& ref = getInstance();
    checkAndReturnValue(ref->mSecure == false, "[RESTServer] Cannot register POST requests in unsecure mode", false);
    if (ref->mRestCalls.emplace(resourcePost).second)
    {
        std::string resourceStr = "^/" + resourcePost + "$";
        ref->mServer->resource[resourceStr]["POST"] = restFunction;
        // ref->mServer->resource[resourceStr]["POST"] = [&ref, restFunction](tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request) {
        //     ref->mThreadPool->enqueue(restFunction, request, response);
        // };
        return true;
    }
    else
    {
        tmzError("%s Call already registered", resourcePost.c_str());
        return false;
    }
}

/********************************************************************/

bool tmz::nwRESTServer::registerPOSTRequest(const std::string& resourcePost, const RestSecureFunction& restFunction)
{
    const auto& ref = getInstance();
    checkAndReturnValue(ref->mSecure == false, "[RESTServer] Cannot register POST requests in secure mode", false);
    if (ref->mRestCalls.emplace(resourcePost).second)
    {
        std::string resourceStr = "^/" + resourcePost + "$";
        ref->mSecureServer->resource[resourceStr]["POST"] = restFunction;
        // ref->mSecureServer->resource[resourceStr]["POST"] = [&ref, restFunction](tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request) {
        //     ref->mThreadPool->enqueue(restFunction, request, response);
        // };
        return true;
    }
    else
    {
        tmzError("%s Call already registered", resourcePost.c_str());
        return false;
    }
}

/********************************************************************/

bool tmz::nwRESTServer::registerGETRequest(const std::string& resourcePost, const RestFunction& restFunction)
{

    const auto& ref = getInstance();
    checkAndReturnValue(ref->mSecure == false, "[RESTServer] Cannot register GET requests in unsecure mode", false);
    if (ref->mRestCalls.emplace(resourcePost).second)
    {
        std::string resourceStr = "^/" + resourcePost + "$";
        ref->mServer->resource[resourceStr]["GET"] = restFunction;
        //     [&ref, restFunction, this](tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request) {
        //     ref->mThreadPool->enqueue(restFunction, request, response);
        // };
        return true;
    }
    else
    {
        tmzError("%s Call already registered", resourcePost.c_str());
        return false;
    }
}

/********************************************************************/

bool tmz::nwRESTServer::registerGETRequest(const std::string& resourcePost, const RestSecureFunction& restFunction)
{

    const auto& ref = getInstance();
    checkAndReturnValue(ref->mSecure == false, "[RESTServer] Cannot register GET requests in secure mode", false);
    if (ref->mRestCalls.emplace(resourcePost).second)
    {
        std::string resourceStr = "^/" + resourcePost + "$";
        ref->mSecureServer->resource[resourceStr]["GET"] = restFunction;
        //     [&ref, restFunction, this](tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request) {
        //     ref->mThreadPool->enqueue(restFunction, request, response);
        // };
        return true;
    }
    else
    {
        tmzError("%s Call already registered", resourcePost.c_str());
        return false;
    }
}

/********************************************************************/

void tmz::nwRESTServer::start()
{
    const auto& ref = getInstance();
    checkAndReturn(!ref->mStarted, "[REST Server] Server already started.");
    ref->setCallback(std::bind(&tmz::nwRESTServer::startInternal, ref));
    ref->execOnce();
    tmzPrint("[REST Server] Starting server %d", ref->mServerPort.get_future().get());
    if (ref->mThreadPool != nullptr)
        ref->mThreadPool->start();
    ref->mStarted = true;
}

/********************************************************************/

void tmz::nwRESTServer::stop()
{
    const auto& ref = getInstance();
    checkAndReturn(ref->mStarted, "[REST Server] Server is not started yet");
    if (ref->mSecure)
    {
        ref->mSecureServer->stop();
    }
    else
    {
        ref->mServer->stop();
    }
    ref->close();
    ref->mStarted = false;
}

/********************************************************************/

void tmz::nwRESTServer::startInternal()
{
    const auto& ref = getInstance();
    if (ref->mSecure)
    {
        ref->mSecureServer->start([&ref](unsigned short port) {
            ref->mServerPort.set_value(port);
        });
    }
    else
    {
        ref->mServer->start([&ref](unsigned short port) {
            ref->mServerPort.set_value(port);
        });
    }
}

/********************************************************************/
