// Copyright (c) 2016, ENTROPY GAME GLOBAL LIMITED. All rights reserved.
// file: service_tunnel.h 

#ifndef SERVICE_TUNNEL_H
#define SERVICE_TUNNEL_H
#include <memory>
#include <string>
#include <vector>

namespace common_cz {

    class IServiceTunnel {
    public:
        IServiceTunnel();
        virtual ~IServiceTunnel();
        virtual void SetProtocol(const std::string& proto) = 0;
        virtual void SetDomain(const std::string& domain) = 0;
        virtual void SetTunnelPort(const unsigned short port) = 0;
        virtual void SetPath(const std::string& path) = 0;
        virtual void SetMethod(const std::string& method) = 0;
        virtual void SetHeaders(const std::vector<std::string>& headers) = 0;
        virtual bool Request(
            const std::string& request_body,
            std::string* response,
            unsigned int timeout_second,
            int* response_code) = 0;
        virtual void GetErrorMessage(std::string* error_info) const = 0;
        virtual bool GetResponseHeader(const std::string& key, std::string* value) = 0;
    };

    IServiceTunnel* CreateHttpTunnel();
}

#endif  // DEMO_SAMPLES_COMMON_UTILITY_SERVICE_TUNNEL_H
