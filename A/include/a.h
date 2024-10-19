//
// Created by 이채호 on 24. 10. 12.
//

#ifndef DYNAMIC_SERVER_A_H
#define DYNAMIC_SERVER_A_H

#include "IEndpointProvider.h"
#include "IHttpServer.h"

class A final : public IEndpointProvider {
public:
    void addEndpoint(IHttpServer& server) const override;
};

#endif //DYNAMIC_SERVER_A_H
