//
// Created by 이채호 on 24. 10. 19.
//

#ifndef DYNAMICLOADER_H
#define DYNAMICLOADER_H
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


class DynamicLoader {
public:
    explicit DynamicLoader(const std::string& path);

    ~DynamicLoader();

    template<typename T>
    [[nodiscard]] T LoadFunctions(const std::string& functionName);

private:
    void* handle = nullptr;
};


template<typename T>
T DynamicLoader::LoadFunctions(const std::string& functionName) {
#ifdef _WIN32
    T func = reinterpret_cast<T>(GetProcAddress((HMODULE) handle, functionName.c_str()));
#else
    T func = reinterpret_cast<T>(dlsym(handle, functionName.c_str()));
#endif
    return func;
}


#endif //DYNAMICLOADER_H
