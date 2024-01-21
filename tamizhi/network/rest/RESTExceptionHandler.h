#pragma once

#include "tamizhi/core/base/Core.h"
#include <iostream>
#include <server_http.hpp>
#include <server_https.hpp>
#include <stdexcept>

template <typename ResponseType>
class nwRestExceptionHandler
{
public:
    static void handleExceptions(const tmzSP<ResponseType>& response, const std::exception& e);

private:
    static void handleInvalidArgument(const tmzSP<ResponseType>& response, const std::exception& e);
    static void handleRuntimeError(const tmzSP<ResponseType>& response, const std::exception& e);
    static void handleGenericError(const tmzSP<ResponseType>& response, const std::exception& e);
};

template <typename ResponseType>
void nwRestExceptionHandler<ResponseType>::handleExceptions(
    const tmzSP<ResponseType>& response, const std::exception& e)
{
    try
    {
        // Handle specific exception types
        if (dynamic_cast<const std::invalid_argument*>(&e) != nullptr)
        {
            handleInvalidArgument(response, e);
        }
        else if (dynamic_cast<const std::runtime_error*>(&e) != nullptr)
        {
            handleRuntimeError(response, e);
        }
        else
        {
            // Default case for other exceptions
            handleGenericError(response, e);
        }
    }
    catch (const std::exception& innerException)
    {
        // Handle any unexpected errors during error handling
        std::cerr << "Error in error handling: " << innerException.what() << std::endl;
        response->write(SimpleWeb::StatusCode::server_error_internal_server_error, "Unexpected error");
    }
}

template <typename ResponseType>
void nwRestExceptionHandler<ResponseType>::handleInvalidArgument(
    const tmzSP<ResponseType>& response, const std::exception& e)
{
    response->write(SimpleWeb::StatusCode::client_error_bad_request, "Invalid argument: " + std::string(e.what()));
}

template <typename ResponseType>
void nwRestExceptionHandler<ResponseType>::handleRuntimeError(
    const tmzSP<ResponseType>& response, const std::exception& e)
{
    response->write(SimpleWeb::StatusCode::server_error_internal_server_error, "Runtime error: " + std::string(e.what()));
}

template <typename ResponseType>
void nwRestExceptionHandler<ResponseType>::handleGenericError(
    const tmzSP<ResponseType>& response, const std::exception& e)
{
    response->write(SimpleWeb::StatusCode::server_error_internal_server_error, "Unexpected error: " + std::string(e.what()));
}
