// #include "backward.cpp"
#include "nlohmann/json.hpp"
#include "tamizhi/core/base/BackwardWrapper.h"
#include "tamizhi/core/base/Core.h"
#include "tamizhi/network/rest/RESTServer.h"
#define UNW_LOCAL_ONLY
#include <cxxabi.h>
#include <execinfo.h>
#include <libunwind.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)
{
    tmzPrint("[Handler] Hello World!");
    nlohmann::json j;
    j << request->content;
    // tmzSleep(10000);
    response->write("Handler exection");
    tmzPrint("[Handler] Execution completed");
}

void handler1(tmzSP<HttpServer::Response> response, tmzSP<HttpServer::Request> request)
{
    tmzPrint("[Handler1] Hello World!");
    nlohmann::json j;
    j << request->content;
    // tmzSleep(1000);
    response->write("Handler1 exection");
    tmzPrint("[Handler1] Execution completed");
}

void myFaultHandler(int sig)
{
    std::cerr << "Segmentation fault! Printing stack trace:" << std::endl;

    unw_cursor_t cursor;
    unw_context_t context;

    // Get the current context
    unw_getcontext(&context);
    unw_init_local(&cursor, &context);

    int n = 0;
    while (unw_step(&cursor))
    {
        unw_word_t ip, sp, off;

        unw_get_reg(&cursor, UNW_REG_IP, &ip);
        unw_get_reg(&cursor, UNW_REG_SP, &sp);

        char symbol[256] = {"<unknown>"};
        char* name = symbol;

        if (!unw_get_proc_name(&cursor, symbol, sizeof(symbol), &off))
        {
            int status;
            if ((name = abi::__cxa_demangle(symbol, NULL, NULL, &status)) == 0)
                name = symbol;
        }

        printf("#%-2d 0x%016" PRIxPTR " sp=0x%016" PRIxPTR " %s + 0x%" PRIxPTR "\n", ++n, static_cast<uintptr_t>(ip), static_cast<uintptr_t>(sp), name, static_cast<uintptr_t>(off));
        // fmsPrint("#%-2d 0x%016" PRIxPTR " sp=0x%016" PRIxPTR " %s + 0x%" PRIxPTR, n, static_cast<uintptr_t>(ip), static_cast<uintptr_t>(sp), name, static_cast<uintptr_t>(off));

        if (name != symbol)
            free(name);
    }

    std::cerr << "End of stack trace." << std::endl;
    exit(1);
}

void handlerd(int sig)
{
    void* array[20];
    size_t size;

    // get void*'s for all entries on the stack
    size = backtrace(array, 20);

    // print out all the frames to stderr
    fprintf(stderr, "Error: signal %d:\n", sig);
    backtrace_symbols_fd(array, size, STDERR_FILENO);
    exit(1);
}

int main()
{
    // signal(SIGABRT, myFaultHandler);
    // signal(SIGINT, myFaultHandler);
    // signal(SIGSEGV, myFaultHandler);
    // signal(SIGPIPE, SIG_IGN);
    // tmzSleep(10000);
    // backward::SignalHandling sh;
    tmz::nwRESTServer server{false};
    server.setPort(8080);

    server.registerPOSTRequest("hello", std::bind(&handler, std::placeholders::_1, std::placeholders::_2));
    server.registerPOSTRequest("hello", std::bind(&handler, std::placeholders::_1, std::placeholders::_2));
    server.registerPOSTRequest("hello1", std::bind(&handler1, std::placeholders::_1, std::placeholders::_2));
    server.start();
    tmzSleep(10000000);
    return 0;
}
