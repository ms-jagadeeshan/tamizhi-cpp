#include "tamizhi/textConverter/api/RESTInterface.h"
#include "tamizhi/textConverter/converter/Converter.h"
#include "textConverter/mapping/Mapping.h"

/********************************************************************/

tmz::tcRestInterface::tcRestInterface(const tmzRP<tmz::TextConverter>& textConverter)
    : mTextConverter(textConverter)
{
}

/********************************************************************/

void tmz::tcRestInterface::init()
{
    mRestServer.registerGETRequest("mapping/getLangList", std::bind(&tmz::tcRestInterface::getLangList, this, std::placeholders::_1, std::placeholders::_2));
    mRestServer.registerGETRequest("mapping/getEncodingList", std::bind(&tmz::tcRestInterface::getEncodingList, this, std::placeholders::_1, std::placeholders::_2));
    mRestServer.registerGETRequest("mapping/getMapping", std::bind(&tmz::tcRestInterface::getMapping, this, std::placeholders::_1, std::placeholders::_2));
    mRestServer.registerPOSTRequest("mapping/convert", std::bind(&tmz::tcRestInterface::convertCallback, this, std::placeholders::_1, std::placeholders::_2));
}

/********************************************************************/

void tmz::tcRestInterface::start()
{
    mRestServer.setPort(8080);
    mRestServer.start();
}

/********************************************************************/

void tmz::tcRestInterface::getLangList(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)
{
    try
    {
        auto langs = mTextConverter->mappingManager()->getLangList();
        json jresp(langs);

        SimpleWeb::CaseInsensitiveMultimap header;
        header.emplace("Content-Type", "application/json");
        response->write(jresp.dump(), header);
    }
    catch (const std::exception& e)
    {
        response->write(SimpleWeb::StatusCode::client_error_bad_request, "Bad Request: " + std::string(e.what()));
    }
}

/********************************************************************/

void tmz::tcRestInterface::getEncodingList(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)
{
    try
    {
        auto queryFields = request->parse_query_string();
        auto it = queryFields.find("lang");
        std::string langCode = (it != queryFields.end()) ? it->second : "";

        auto encodings = mTextConverter->mappingManager()->getEncodingList(langCode);

        json jresp(encodings);
        SimpleWeb::CaseInsensitiveMultimap header;
        header.emplace("Content-Type", "application/json");
        response->write(jresp.dump(), header);
    }
    catch (const std::exception& e)
    {
        nwRestExceptionHandler<HttpServer::Response>::handleExceptions(response, e);
    }
}

/********************************************************************/

void tmz::tcRestInterface::getMapping(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)
{
    try
    {
        constexpr char PARAM_NAME[] = "name";
        constexpr char PARAM_TYPE[] = "type";

        auto queryFields = request->parse_query_string();

        // Check if 'name' parameter is present
        auto nameIt = queryFields.find(PARAM_NAME);
        if (nameIt == queryFields.end())
        {
            throw std::invalid_argument("name parameter not given");
        }
        std::string encodeName = nameIt->second;

        // Check if 'type' parameter is present
        auto typeIt = queryFields.find(PARAM_TYPE);
        if (typeIt == queryFields.end())
        {
            throw std::invalid_argument("type parameter not given");
        }
        int mappingType = std::stoi(typeIt->second);

        auto mapping = mTextConverter->mappingManager()->getMapping(encodeName, static_cast<tcConversionType>(mappingType));

        if (!mapping)
        {
            response->write("Mapping not found");
        }
        else
        {
            json jresp(*mapping->mapping());
            SimpleWeb::CaseInsensitiveMultimap header;
            header.emplace("Content-Type", "application/json");
            response->write(jresp.dump(), header);
        }
    }
    catch (const std::exception& e)
    {
        nwRestExceptionHandler<HttpServer::Response>::handleExceptions(response, e);
    }
}

/********************************************************************/

void tmz::tcRestInterface::convertCallback(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)
{
    try
    {
        json jreq, jresp;
        jreq = json::parse(request->content.string());

        std::string text = jreq["text"];
        std::string encodeName = jreq["name"];
        int mappingType = jreq["type"];

        tmzPrint("%s", request->header.find("Content-Type")->second.c_str());
        auto result = mTextConverter->convert(encodeName, static_cast<tcConversionType>(mappingType), text);

        SimpleWeb::CaseInsensitiveMultimap header;
        header.emplace("Content-Type", "application/text");
        header.emplace("Access-Control-Allow-Origin", "*");
        header.emplace("Access-Control-Allow-Methods", "*");
        header.emplace("Access-Control-Max-Age", "1728000");
        header.emplace("Access-Control-Allow-Headers", "*");
        response->write(result, header);
    }
    catch (const std::exception& e)
    {
        nwRestExceptionHandler<HttpServer::Response>::handleExceptions(response, e);
    }
}

/********************************************************************/
