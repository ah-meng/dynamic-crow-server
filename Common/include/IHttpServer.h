//
// Created by 이채호 on 24. 10. 18.
//

#ifndef DYNAMIC_SERVER_IHTTPSERVER_H
#define DYNAMIC_SERVER_IHTTPSERVER_H

#include <string>
#include <functional>

enum class HttpMethod {
    Get,
    Post,
    Put,
    Delete,
    Patch
};

class IHttpServer {
public:
    virtual void addEndpoint(HttpMethod method, std::string url, std::function<std::string()> handler) = 0;

    virtual void start(int port) = 0;

    virtual ~IHttpServer() = default;

};

#endif //DYNAMIC_SERVER_IHTTPSERVER_H
