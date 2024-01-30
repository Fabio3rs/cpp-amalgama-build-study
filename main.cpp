#include "stdafx.hpp"

#include "CConfig.cpp"
#include <unistd.h>

#include "A.cpp"
#include "B.cpp"

int main() {
    CConfig::config().load_from_envp(environ);
    std::cout << "Hello, World!" << std::endl;

    for (const auto &[key, value] : CConfig::config().getAll()) {
        std::cout << key << " = " << value << std::endl;
    }

    foo();
    bar();
    testB();
    return 0;
}
