//
// Created by 이채호 on 24. 10. 19.
//

#include "DynamicLoader.h"

DynamicLoader::DynamicLoader(const std::string& path) {
#ifdef _WIN32
    handle = LoadLibrary(path.c_str());
#else
    handle = dlopen(path.c_str(), RTLD_LAZY);
#endif
}

DynamicLoader::~DynamicLoader() {
#ifdef _WIN32
    if (handle) {
        FreeLibrary((HMODULE) handle);
    }
#else
    if (handle != nullptr)
        dlclose(handle);
#endif
}
