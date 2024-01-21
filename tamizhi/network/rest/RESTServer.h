#pragma once

#include <server_http.hpp>
#include <server_https.hpp>

#include "tamizhi/core/base/Core.h"
#include "tamizhi/network/rest/RESTExceptionHandler.h"

typedef SimpleWeb::Server<SimpleWeb::HTTP> HttpServer;
typedef SimpleWeb::Server<SimpleWeb::HTTPS> HttpsServer;
namespace tmz
{

class nwRESTServer : public crExtendedSingleton<nwRESTServer>, public crThread
{
    TMZ_EXTENDED_SINGLETON(nwRESTServer);
    using BaseType = crThread;
    using RestFunction = std::function<void(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)>;
    using RestSecureFunction = std::function<void(tmzSP<HttpsServer::Response> response, tmzSP<HttpsServer::Request> request)>;

public:
    // Constructor.
    nwRESTServer(bool secure = false);
    // Destructor.
    ~nwRESTServer() override;

    // Set the server type.
    void isSecure(const bool& secure = false) const;
    // Set the port.
    void setPort(const uint16_t& port);
    // Register new POST request.
    bool registerPOSTRequest(const std::string& resourcePost, const RestFunction& restFunction);
    bool registerPOSTRequest(const std::string& resourcePost, const RestSecureFunction& restFunction);
    // Register new GET request.
    bool registerGETRequest(const std::string& resourcePost, const RestFunction& restFunction);
    bool registerGETRequest(const std::string& resourcePost, const RestSecureFunction& restFunction);

    // Start the server.
    void start();
    // Stop the server.
    void stop();

private:
    void startInternal();

private:
    // Is the connection secure.
    bool mSecure = false;
    // If the rest server is started.
    bool mStarted = false;
    // HTTP Server.
    tmzSP<HttpServer> mServer;
    // HTTPS Server.
    tmzSP<HttpsServer> mSecureServer;
    // Worker thread pool.
    tmzSP<crThreadPool> mThreadPool;
    // Security Certificate.
    // crFilePath mSecurityCert;
    // Security key.
    // crFilePath mSecurityKey;
    // Sef of registered calls.
    tmzSet<std::string> mRestCalls;
    // Port.
    std::promise<unsigned short> mServerPort;
};
} // namespace tmz
