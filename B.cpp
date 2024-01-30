#pragma once

#include "ChronoUtils.cpp"
#include "A.cpp"

void bar() {
    std::cout << __FILE__ << " " << __LINE__ << "  "
              << ChronoUtils::GetDateAndTime() << std::endl;
}

void testB() {
    std::cout << __FILE__ << " " << __LINE__ << "  "
              << ChronoUtils::GetDateAndTime() << std::endl;
    foo();
}
