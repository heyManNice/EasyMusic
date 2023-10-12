#include "config_service.h"

void from_json(const nlohmann::json& j, Account& account_){
    account_.cookie = j["cookie"].get<std::string>();
}

void to_json(nlohmann::json& j, const Account& account_){
    j = nlohmann::json{ {"cookie", account_.cookie}};
}

void from_json(const nlohmann::json& j, Config& config_){
    config_.accounts = j["accounts"].get<Accounts>();
    config_.apiurl = j["accounts"].get<std::string>();
    config_.proxy = j["proxy"].get<std::string>();
}

void to_json(nlohmann::json& j, const Config& config_){
    j = nlohmann::json{ {"accounts", config_.accounts}, {"apiurl", config_.apiurl}, {"proxy", config_.proxy}};
}