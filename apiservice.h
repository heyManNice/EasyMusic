#ifndef EASYMUSIC_APISERVICE_H_
#define EASYMUSIC_APISERVICE_H_

#include <vector>
#include <string>
#include <string_view>

#include <nlohmann/json.hpp>

namespace apiservice {
	struct Artist
	{
		uint32_t id;
		std::string name;
	};
	typedef std::vector<Artist> Artists;
	void from_json(const nlohmann::json& j, Artist& artist_);

	struct Album
	{
		uint32_t id;
		std::string name;
	};
	void from_json(const nlohmann::json& j, Album& album_);

	struct Song
	{
		std::string name;
		uint32_t id;
		Artists artists;
		Album album;
		uint32_t duration;
	};
	typedef std::vector<Song> Songs;
	void from_json(const nlohmann::json& j, Song& song_);

	struct SignalSong
	{
		Song song;
		std::string albumPicUrl;
	};
	struct SongResult
	{
		SignalSong song;
		int code;
	};
	void from_json(const nlohmann::json& j, SignalSong& song_);
	void from_json(const nlohmann::json& j, SongResult& sonyresult_);

	struct SearchResult
	{
		Songs songs;
		bool hasMore;
		uint32_t songCount;
		int code;
	};

	void from_json(const nlohmann::json& j, SearchResult& searchresult_);

	template<typename T, typename Input>
	T parse(Input sv) {
		return (T)nlohmann::json::parse(sv);
	}

}

#endif // !EASYMUSIC_APISERVICE_H_
