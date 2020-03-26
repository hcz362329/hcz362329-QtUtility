// Copyright (c) 2016, ENTROPY GAME GLOBAL LIMITED. All rights reserved.
// file: http_tunnel.h

#ifndef HTTP_TUNNEL_H
#define HTTP_TUNNEL_H
#pragma once;

#include <memory>
#include <string>
#include <vector>
#include "service_tunnel.h"

#ifndef SERVICE_PORT_DEFAULT
#define SERVICE_PORT_DEFAULT 80
#endif

#ifndef SERVICE_PROTOCOL_HTTP
#define SERVICE_PROTOCOL_HTTP "http"
#endif

#ifndef SERVICE_PROTOCOL_HTTPS
#define SERVICE_PROTOCOL_HTTPS "https"
#endif

#ifndef SERVICE_PROTOCOL_DEFAULT
#define SERVICE_PROTOCOL_DEFAULT SERVICE_PROTOCOL_HTTP
#endif

#ifndef SERVICE_METHOD_GET
#define SERVICE_METHOD_GET "GET"
#endif

#ifndef SERVICE_METHOD_POST
#define SERVICE_METHOD_POST "POST"
#endif

#ifndef SERVICE_METHOD_DEFAULT
#define SERVICE_METHOD_DEFAULT SERVICE_METHOD_POST
#endif

#ifndef SERVICE_PATH_DEFAULT
#define SERVICE_PATH_DEFAULT "/blank"
#endif

#ifndef SERVICE_REQUEST_TIMEOUT
#define SERVICE_REQUEST_TIMEOUT 10
#endif

#ifndef SERVICE_SUCCESS_RESP_CODE
#define SERVICE_SUCCESS_RESP_CODE 200
#endif

namespace common_cz {

    class HttpTunnel: public IServiceTunnel {
    public:
        HttpTunnel();
        virtual ~HttpTunnel();

        virtual void SetProtocol(const std::string& proto);
        virtual void SetDomain(const std::string& domain);
        virtual void SetTunnelPort(const unsigned short port);
        virtual void SetPath(const std::string& path);
        virtual void SetMethod(const std::string& method);
        virtual void SetHeaders(const std::vector<std::string>& headers);

        virtual bool Request(
            const std::string& request_body,
            std::string* response,
            unsigned int timeout_second,
            int* response_code);
        virtual bool Request(
            const std::string& url,
            const std::string& request_body,
            std::string* response,
            unsigned int timeout_second,
            int* response_code);
        virtual void GetErrorMessage(std::string* error_message) const;
        virtual bool GetResponseHeader(const std::string& key, std::string* value);

    protected:
        struct Impl;
        Impl* impl_;
    };
}  // namespace common_cz

#endif  // DEMO_SAMPLES_COMMON_UTILITY_HTTP_TUNNEL_H
