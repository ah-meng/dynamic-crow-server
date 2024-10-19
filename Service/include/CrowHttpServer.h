//
// Created by 이채호 on 24. 10. 18.
//

#ifndef DYNAMIC_SERVER_CROWHTTPSERVER_H
#define DYNAMIC_SERVER_CROWHTTPSERVER_H


#include <functional>
#include "IHttpServer.h"
#include "crow/app.h"

class CrowHttpServer final : public IHttpServer {
public:
    CrowHttpServer();

private:
    crow::SimpleApp app;

public:
    void addEndpoint(HttpMethod method, std::string url, std::function<std::string()> handler) override;

    void start(int port) override;

    ~CrowHttpServer() override = default;

private:
    static crow::HTTPMethod HttpMethodConverter(HttpMethod method);
};


#endif //DYNAMIC_SERVER_CROWHTTPSERVER_H
