#ifndef EASYMUSIC_PLAYER_SERVICE_H_
#define EASYMUSIC_PLAYER_SERVICE_H_

#include <string>
#include <string_view>
#include <mutex>

class PlayerService;
namespace {
	static std::once_flag _psflag;
	static PlayerService* _psinstance;
}

class PlayerService {
public:
	static PlayerService* GetInstance()
	{
		std::call_once(_psflag, []() {
			_psinstance = new PlayerService();
			});
		return _psinstance;
	}

	~PlayerService() {};

	void Play();
	void Pause();
	void PlayFromPosition(long position);

	long getTotalTime();
	long getPosition();

	void OpenUrl(std::wstring_view url);
	void Close();

	void SetVolume(int vol);

	inline bool IsPlaying() { return this->m_isPlaying; };
	inline uint8_t GetVolume() { return this->m_volume; };

private:
	PlayerService() {};
	PlayerService(const PlayerService&) = delete;
	PlayerService(PlayerService&&) = delete;

	bool m_isPlaying = false;
	uint8_t m_volume = 100;
};


#endif // !EASYMUSIC_PLAYER_SERVICE_H_
