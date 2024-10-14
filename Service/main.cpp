#include <iostream>
#include "crow.h"

#ifdef DEBUG

#else

#include "filesystem"

#endif


#ifdef _WIN32
#include <Windows.h>

#else

#include <dlfcn.h>

#endif


#ifdef ENABLE_A_ENDPOINT

#include "a.h"

#endif

#ifdef ENABLE_B_ENDPOINT

#include "b.h"

#endif

namespace fs = std::filesystem;

void load_and_register(const std::string& library_path, crow::SimpleApp& app) {
#ifdef _WIN32
    HMODULE handle = LoadLibrary(library_path.c_str());
        if (!handle) {
            std::cerr << "Failed to load " << library_path << std::endl;
            return;
        }
        auto register_route = (void(*)(crow::SimpleApp&))GetProcAddress(handle, "register_routes");
#else
    void* handle = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load " << library_path << std::endl;
        return;
    }
    auto register_route = (void (*)(crow::SimpleApp&)) dlsym(handle, "register_routes");

#endif

    if (register_route) {
        register_route(app);
    } else {
        std::cerr << "Failed to find register_routes in " << library_path << std::endl;
    }
}

void load_plugins(crow::SimpleApp& app) {
#ifdef DEBUG
#ifdef ENABLE_A_ENDPOINT
    register_a(app);
#endif

#ifdef ENABLE_B_ENDPOINT
    register_b(app);
#endif

#else
    std::string plugin_dir = "./plugins";
    // 릴리즈 모드에서는 DLL 동적 로딩
    for (const auto& entry: fs::directory_iterator(plugin_dir)) {
        std::string path = entry.path().string();
        if (path.find(".dll") != std::string::npos || path.find(".so") != std::string::npos) {
            load_and_register(path, app);
        }
    }
#endif
}

int main() {

    crow::SimpleApp app;

    CROW_ROUTE(app, "/t").methods(crow::HTTPMethod::Get)([](const crow::request& request) -> crow::response {
        return {200, ""};
    });
    std::cout << "Hello, World!" << std::endl;

    load_plugins(app);

#ifdef DEBUGGG
    std::cout << "" << std::endl;
#endif

    app.port(3000).run();
    return 0;
}
