//
// Created by 이채호 on 24. 10. 12.
//

#ifndef DYNAMIC_SERVER_B_H
#define DYNAMIC_SERVER_B_H

#include "IEndpointProvider.h"
#include "IHttpServer.h"

class B final : public IEndpointProvider {
public:
    void addEndpoint(IHttpServer& server) const override;
private:
    int test = 40;
};

#endif //DYNAMIC_SERVER_B_H
