// Copyright (c) 2019, cz. All rights reserved.
#include "service_tunnel.h"
#include "http_tunnel.h"

namespace common_cz {

    IServiceTunnel::IServiceTunnel() {}

    IServiceTunnel::~IServiceTunnel() {}

    IServiceTunnel* CreateHttpTunnel() {
        return reinterpret_cast<IServiceTunnel*>(new HttpTunnel());
    }
}
