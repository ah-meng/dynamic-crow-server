#include <iostream>

#ifdef DEBUG

#ifdef ENABLE_A_ENDPOINT

#include "a.h"

#endif

#ifdef ENABLE_B_ENDPOINT

#include "b.h"

#endif
#else

#include "filesystem"

#endif


#include "CrowHttpServer.h"
#include <DynamicLoader.h>
#include "IEndpointProvider.h"

//TEMP, Test
std::vector<std::unique_ptr<IEndpointProvider, std::function<void(IEndpointProvider*)> > > obj_vector;
namespace fs = std::filesystem;

void load_and_register(const std::string& library_path, IHttpServer& app) {
    try {
        auto loader = std::make_shared<DynamicLoader>(library_path);
        const auto create_object = loader->LoadFunctions<IEndpointProvider* (*)()>("create_object");
        const auto delete_object = loader->LoadFunctions<void (*)(IEndpointProvider*)>("delete_object");

        if (!create_object) {
            std::cerr << "Failed to find create_object in " << library_path << std::endl;
            throw std::runtime_error("create_object");
        }
        if (!delete_object) {
            std::cerr << "Failed to find delete_object in " << library_path << std::endl;
            throw std::runtime_error("delete_object");
        }

        //loader 캡쳐 필수!! shared_ptr 의 참조 카운트 및 플러그인 객체가 소멸될 때까지 loader객체의 생존을 위함
        auto custom_deleter = [delete_object, loader](IEndpointProvider* obj) {
            delete_object(obj);
            std::cout << "custom_deleter" << std::endl;
        };
        std::unique_ptr<IEndpointProvider, std::function<void(IEndpointProvider*)> > object(
            create_object(), custom_deleter);
        object->addEndpoint(app);
        obj_vector.push_back(std::move(object));
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::vector<std::string> get_plugins(const std::string& plugin_path) {
    std::vector<std::string> plugins;
    for (const auto& entry: fs::directory_iterator(plugin_path)) {
        std::string path = entry.path().string();
        if (path.find(".dll") != std::string::npos || path.find(".so") != std::string::npos) {
            plugins.push_back(path);
        }
    }
    return plugins;
}

void load_plugins(IHttpServer& app) {
#ifdef DEBUG
#ifdef ENABLE_A_ENDPOINT
    std::unique_ptr<IEndpointProvider, std::function<void(IEndpointProvider*)> > a(new A(), [](IEndpointProvider* obj) {
        delete obj;
    });
    a->addEndpoint(app);

    obj_vector.push_back(std::move(a));
#endif

#ifdef ENABLE_B_ENDPOINT
    std::unique_ptr<IEndpointProvider, std::function<void(IEndpointProvider*)> > b(new B(), [](IEndpointProvider* obj) {
        delete obj;
    });
    b->addEndpoint(app);

    obj_vector.push_back(std::move(b));
#endif

#else
    const std::string plugin_dir = "./plugins";
    // 릴리즈 모드에서는 DLL 동적 로딩
    for (const auto& plugin: get_plugins(plugin_dir))
        load_and_register(plugin, app);
#endif
}

int main() {
    const std::unique_ptr<IHttpServer> server = std::make_unique<CrowHttpServer>();
    server->addEndpoint(HttpMethod::Get, "/t", [] {
        return "test";
    });

    load_plugins(*server);
    server->start(3000);
    return 0;
}
