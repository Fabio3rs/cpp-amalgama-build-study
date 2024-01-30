#pragma once

#include "stdafx.hpp"

class ChronoUtils {
  public:
    static auto
    GetDateAndTime(std::chrono::high_resolution_clock::time_point now =
                       std::chrono::high_resolution_clock::now())
        -> std::string {
        std::time_t tt = std::chrono::high_resolution_clock::to_time_t(now);

        auto mksec = std::chrono::duration_cast<std::chrono::microseconds>(
                         now.time_since_epoch())
                         .count();
        mksec %= 1000000;

        std::string res;

        {
            std::array<char, 32> buf{};

            std::tm tmLocal{};

            size_t strft_res_sz =
                strftime(buf.data(), buf.size(), "%Y/%m/%d %H:%M:%S.",
                         localtime_r(&tt, &tmLocal));

            res.reserve(28);
            res.append(buf.data(), strft_res_sz);
        }

        {
            std::string mksecstr = std::to_string(mksec);
            size_t mksecsz = mksecstr.size();

            if (mksecsz < 6) {
                res.append(6 - mksecsz, '0');
            }

            res += mksecstr;
        }

        return res;
    }
};
