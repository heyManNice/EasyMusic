#ifndef EASYMUSIC_PLAYER_SERVICE_H_
#define EASYMUSIC_PLAYER_SERVICE_H_

#include <string>
#include <string_view>

class PlayerService {
public:
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
	bool m_isPlaying = false;
	uint8_t m_volume = 0;
};


#endif // !EASYMUSIC_PLAYER_SERVICE_H_
