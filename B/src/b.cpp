//
// Created by 이채호 on 24. 10. 12.
//
#include "b.h"

#ifndef DEBUG
extern "C" [[maybe_unused]] IEndpointProvider* create_object() {
    return new B();
}

extern "C" [[maybe_unused]] void delete_object(IEndpointProvider* object) {
    delete object;
}
#endif

void B::addEndpoint(IHttpServer& server) const {
    server.addEndpoint(HttpMethod::Get, "/b/t", [this] {
        return std::to_string(test);
    });
}
