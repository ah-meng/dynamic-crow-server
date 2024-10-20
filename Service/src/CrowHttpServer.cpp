//
// Created by 이채호 on 24. 10. 18.
//

#include "CrowHttpServer.h"

CrowHttpServer::CrowHttpServer() = default;

void CrowHttpServer::addEndpoint(
    const HttpMethod method,
    const std::string url,
    const std::function<std::string()> handler
) {
    app.route_dynamic(url).methods(HttpMethodConverter(method))(handler);
}

crow::HTTPMethod CrowHttpServer::HttpMethodConverter(const HttpMethod method) {
    switch (method) {
        case HttpMethod::Get:
            return crow::HTTPMethod::Get;
        case HttpMethod::Post:
            return crow::HTTPMethod::Post;
        case HttpMethod::Put:
            return crow::HTTPMethod::Put;
        case HttpMethod::Delete:
            return crow::HTTPMethod::Delete;
        case HttpMethod::Patch:
            return crow::HTTPMethod::Patch;
    }
    throw std::runtime_error("Invalid HttpMethod");
}

void CrowHttpServer::start(const int port) {
    app.port(port).run();
}
