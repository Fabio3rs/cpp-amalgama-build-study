#pragma once

#include "ChronoUtils.cpp"

void foo() {
    std::cout << __FILE__ << " " << __LINE__ << "  "
              << ChronoUtils::GetDateAndTime() << std::endl;
}
