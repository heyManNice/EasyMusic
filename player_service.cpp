#include "player_service.h"

#include <format>

#include <windows.h>

void PlayerService::Play()
{
	mciSendStringW(L"play now_mp3", NULL, 0, NULL);
	this->m_isPlaying = true;
}

void PlayerService::Pause()
{
	mciSendStringW(L"Pause now_mp3", NULL, 0, NULL);
	this->m_isPlaying = false;
}

void PlayerService::PlayFromPosition(long position)
{
	auto command = std::format("play now_mp3 from {} to {}", position, this->getTotalTime());
	mciSendStringA(command.c_str(), NULL, 0, NULL);
	this->m_isPlaying = true;
}

long PlayerService::getTotalTime()
{
	char buf[32];
	mciSendStringA("status now_mp3 length", buf, 32, 0);
	return strtol(buf, NULL, 10);
}

long PlayerService::getPosition()
{
	char buf[32];
	mciSendStringA("status now_mp3 position", buf, 32, 0);
	return strtol(buf, NULL, 10);
}

void PlayerService::OpenUrl(std::wstring_view url)
{
	auto command = std::format(LR"(open "{}" type mpegvideo alias now_mp3)", url);
	mciSendStringW(command.c_str(), NULL, 0, NULL);
}

void PlayerService::Close()
{
	mciSendStringW(L"close now_mp3", 0, 0, 0);
}

void PlayerService::SetVolume(int vol)
{
	auto command = std::format("setaudio now_mp3 volume to {}", vol);
	this->m_volume = vol;
	mciSendStringA(command.c_str(), 0, 0, 0);
}
