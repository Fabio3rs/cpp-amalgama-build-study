#!/bin/bash

STD=c++17
mkdir -p build

function should_compile() {
    PATHA="$1"
    PATHB="$2"

    TIMEA=$(stat -c %Y "${PATHA}" || echo 0)
    TIMEB=$(stat -c %Y "${PATHB}" || echo 0)

    if [ $TIMEA -gt $TIMEB ]; then
        echo 1
        return
    fi
    echo 0
}

if [ "$(should_compile "stdafx.hpp" "build/stdafx.hpp.pch")" -ne '0' ]; then
    clang++ -x c++-header -std=$STD -o build/stdafx.hpp.pch stdafx.hpp]
fi

if [ "$(should_compile "CConfig.cpp" "build/CConfig.cpp.pch")" -ne '0' ]; then
    clang++ -include-pch build/stdafx.hpp.pch -x c++-header -std=$STD -o build/CConfig.cpp.pch CConfig.cpp
fi

if [ "$(should_compile "ChronoUtils.cpp" "build/ChronoUtils.cpp.pch")" -ne '0' ]; then
    clang++ -include-pch build/stdafx.hpp.pch -x c++-header -std=$STD -o build/ChronoUtils.cpp.pch ChronoUtils.cpp
fi

if [ "$(should_compile "A.cpp" "build/A.cpp.pch")" -ne '0' ]; then
    clang++ -include-pch build/stdafx.hpp.pch -include-pch build/ChronoUtils.cpp.pch -x c++-header -std=$STD -o build/A.cpp.pch A.cpp
fi

if [ "$(should_compile "B.cpp" "build/B.cpp.pch")" -ne '0' ]; then
    clang++ -include-pch build/stdafx.hpp.pch -include-pch build/ChronoUtils.cpp.pch -x c++-header -std=$STD -o build/B.cpp.pch B.cpp
fi

clang++ -std=$STD -include-pch build/stdafx.hpp.pch -include-pch build/ChronoUtils.cpp.pch -include-pch build/A.hpp.pch -include-pch build/B.hpp.pch -include-pch build/CConfig.cpp.pch main.cpp

