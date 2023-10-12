#ifndef EASYMUSIC_CONFIG_SERVICE_H_
#define EASYMUSIC_CONFIG_SERVICE_H_

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

struct Account
{
    std::string cookie;
};
void from_json(const nlohmann::json &j, Account &account_);
void to_json(nlohmann::json &j, const Account &account_);

typedef std::vector<Account> Accounts;

struct Config
{
    std::string apiurl;
    std::string proxy;
    Accounts accounts;
};
void from_json(const nlohmann::json &j, Config &config_);
void to_json(nlohmann::json &j, const Config &config_);

class config_service
{
private:
    Config m_config_;
    std::string m_path_;

public:
    config_service(const std::string& path) :m_path_(path) {};

    void Load() {this->Load(this->m_path_);};
    void Save() {this->Save(this->m_path_);};
    void Load(const std::string& path);
    void Save(const std::string& path);

    Config *GetConfig() { return &this->m_config_; };
};

#endif // EASYMUSIC_CONFIG_SERVICE_H_
