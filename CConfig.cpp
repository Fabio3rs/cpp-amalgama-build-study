#pragma once
/**
 *@file CConfig.cpp
 * @author Fabio Rossini Sluzala ()
 * @brief Config class definitions
 * @version 0.1
 *
 */
#include "stdafx.hpp"

class CConfig {
    std::unordered_map<std::string, std::string> data;

  public:
    /**
     *@brief Configuration singleton instance
     *
     * @return CConfig&
     */
    static auto config() -> CConfig &;

    /**
     *@brief Searches a variable in the config and if it is not exists return a
     *empty string
     *
     * @param key The variable name
     * @return std::string
     */
    auto operator[](const std::string &key) const noexcept -> std::string;

    /**
     *@brief Searches a variable in the config and if it is not exists return a
     *custom default value
     *
     * @param key The variable name
     * @param default_ret The default return
     * @return std::string
     */
    auto at(const std::string &key,
            std::string &&default_ret = "") const noexcept -> std::string;

    void set(const std::string &key, const std::string &value) {
        data[key] = value;
    }

    auto getAll() const
        -> const std::unordered_map<std::string, std::string> & {
        return data;
    }

    /**
     *@brief Reads and parses envp variable
     *
     * @param envp environment variables received in the third parameter of the
     *main function
     */
    void load_from_envp(const char *const *envp);

    auto operator=(const CConfig &) -> CConfig & = delete;
    CConfig(const CConfig &) = delete;

    auto operator=(CConfig &&) -> CConfig & = default;
    CConfig(CConfig &&) = default;

    ~CConfig() = default;

  private:
    CConfig() noexcept = default;
};

auto CConfig::config() -> CConfig & {
    static CConfig conf;
    return conf;
}

auto CConfig::operator[](const std::string &key) const noexcept -> std::string {
    auto it = data.find(key);
    if (it == data.end()) {
        return "";
    }

    return it->second;
}

auto CConfig::at(const std::string &key,
                 std::string &&default_ret) const noexcept -> std::string {
    auto it = data.find(key);
    if (it == data.end()) {
        return std::move(default_ret);
    }

    return it->second;
}

void CConfig::load_from_envp(const char *const *envp) {
    const char *const *env = envp;
    std::string line;
    std::string key;
    std::string val;
    for (/**/; *env != nullptr; ++env) {
        line = *env;

        size_t pos = line.find_first_of('=');

        if (pos == std::string::npos) {
            continue;
        }

        key = line.substr(0, pos);
        val = line.substr(pos + 1);

        data[key] = val;
    }
}
