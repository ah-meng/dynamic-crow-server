//
// Created by 이채호 on 24. 10. 12.
//
#include "a.h"

#ifndef DEBUG
extern "C" [[maybe_unused]] IEndpointProvider* create_object() {
    return new A();
}

extern "C" [[maybe_unused]] void delete_object(IEndpointProvider* object) {
    delete object;
}
#endif

void A::addEndpoint(IHttpServer& server) const {
    server.addEndpoint(HttpMethod::Get, "/a/t", [this] {
        return "a test";
    });
}
