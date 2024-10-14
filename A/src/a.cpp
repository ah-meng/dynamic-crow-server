//
// Created by 이채호 on 24. 10. 12.
//
#ifdef DEBUG
#define EXPORT_API
#else
#define EXPORT_API extern "C"
#endif

#ifdef DEBUG
#define REGISTER_ROUTES register_routes_a
#else
#define REGISTER_ROUTES register_routes
#endif
#include "a.h"

EXPORT_API void REGISTER_ROUTES(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/a/t").methods(crow::HTTPMethod::Get)([]() {
        return "a";
    });
}

void register_a(crow::SimpleApp& app) {
    REGISTER_ROUTES(app);
}

