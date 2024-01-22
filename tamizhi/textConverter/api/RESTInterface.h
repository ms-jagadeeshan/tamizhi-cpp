#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/network/rest/RESTServer.h"

namespace tmz
{
class TextConverter;

class tcRestInterface
{
public:
    tcRestInterface(const tmzRP<tmz::TextConverter>& textConverter);

    // Initialize.
    void init();
    // Start the rest interface.
    void start();
    // Mapping api callback.
    void getLangList(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request);
    void getEncodingList(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request);
    void getMapping(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request);
    // Convert api callback.
    void convertCallback(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request);

private:
    // Store the text converter
    tmzRP<tmz::TextConverter> mTextConverter;
    // Store the rest server.
    tmz::nwRESTServer mRestServer;
};

} // namespace tmz
