#include "apiservice.h"

#include <cpr/cpr.h>

constexpr auto APIDOMAIN = "http://cloud-music.pl-fe.cn";

template<typename InputType>
std::tuple<int, std::string> apiservice::HTTP_Get(InputType url) {
	auto rep = cpr::Get(cpr::Url{ url });
	return std::make_tuple((int)rep.error.code, rep.text);
}

void apiservice::impl::from_json(const nlohmann::json& j, Artist& artist_) {
	artist_.id = j["id"].get<uint32_t>();
	artist_.name = j["name"].get<std::string>();
}

void apiservice::impl::from_json(const nlohmann::json& j, Album& album_) {
	album_.id = j["id"].get<uint32_t>();
	album_.name = j["name"].get<std::string>();
}

void apiservice::impl::from_json(const nlohmann::json& j, Song& song_) {
	song_.name = j["name"].get<std::string>();
	song_.id = j["id"].get<uint32_t>();
	song_.artists = j["artists"].get<Artists>();
	song_.album = j["album"].get<Album>();
	song_.duration = j["duration"].get<uint32_t>();
}

void apiservice::impl::from_json(const nlohmann::json& j, SignalSong& song_) {
	Song song__{};
	song__.name = j["name"].get<std::string>();
	song__.id = j["id"].get<uint32_t>();
	song__.artists = j["ar"].get<Artists>();
	song__.album = j["al"].get<Album>();
	song_.song = song__;
	song_.albumPicUrl = j["al"]["picUrl"].get<std::string>();
}

void apiservice::impl::from_json(const nlohmann::json& j, SongResult& sonyresult_) {
	sonyresult_.song = j["songs"][0].get<SignalSong>();
	sonyresult_.code = j["code"].get<int>();
}

void apiservice::impl::from_json(const nlohmann::json& j, SearchResult& searchresult_) {
	searchresult_.code = j["code"].get<int>();
	auto result = j["result"];
	searchresult_.songs = result["songs"].get<Songs>();
	searchresult_.hasMore = result["hasMore"].get<bool>();
	searchresult_.songCount = result["songCount"].get<uint32_t>();
}

std::tuple<int, apiservice::SongResultPtr> apiservice::GetSong(int id)
{
	std::string url = std::format("{}/song/detail?ids={}", APIDOMAIN,id);
	auto [code, data] = HTTP_Get(url);
	if(code)
		return std::make_tuple<int, SongResultPtr>((int)code, nullptr);
	auto songresult = apiservice::impl::parse<apiservice::impl::SongResult>(data);
	return std::make_tuple<int, SongResultPtr>(0, std::make_shared<apiservice::impl::SongResult>(songresult));
}

std::tuple<int, apiservice::SearchResultPtr> apiservice::SearchSong(std::string_view keyword, int limit)
{
	std::string url = std::format("{}/search?limit={}&keywords={}", APIDOMAIN, limit, keyword);
	auto [code, data] = HTTP_Get(url);
	if (code)
		return std::make_tuple<int, SearchResultPtr>((int)code, nullptr);
	auto songresult = apiservice::impl::parse<apiservice::impl::SearchResult>(data);
	return std::make_tuple<int, SearchResultPtr>(0, std::make_shared<apiservice::impl::SearchResult>(songresult));
}
