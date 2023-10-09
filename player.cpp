#include "myhead.h"

#include <chrono>

#include "apiservice.h"

void Player::SetMusic(int id){
	this->id = id;
	this->playing = 0;
	//应该要在https://github.com/Binaryify/NeteaseCloudMusicApi
	//中分析使用官方的api，构造一个官方的请求类，因为时间问题，此处使用了网上找的第三方代理接口

	auto [code, songresult] = apiservice::GetSong(this->id);
	if (code)
	{
		//TODO: exit
	}
	if (songresult->code != 200)
	{
		//TODO: exit
	}
	auto& song = songresult->song.song;
	
	this->name = utf8_to_utf16le(song.name);

	auto [codePic, dataPic] = apiservice::HTTP_Get(songresult->song.albumPicUrl);
	if (codePic)
	{
		//TODO: exit
	}
	this->albumPic = dataPic;
	
	this->artist = utf8_to_utf16le(song.artists[0].name);
	//先解析这两个需要的，剩下的等换上官方的api再解析
	
	//std::cout<<this->id<<endl;
	auto ps = PlayerService::GetInstance();
	ps->Close();
	auto path = std::format(LR"(https://music.163.com/song/media/outer/url?id={}.mp3)", this->id);
	ps->OpenUrl(path);
    
	this->UpdateTotalTime();
	this->UpdatePosition();
    player.newVolume=player.getVolume();
    //重绘底部左下角的歌曲信息
    InvalidateRect(HWNDM[H_PlayingInfo_m], NULL, TRUE);
    //重绘进度条相关信息
	InvalidateRect(HWNDM[H_PlayingControl], NULL, TRUE);
	//重绘右下角按钮
	InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
}
void Player::UpdateTotalTime(){
	auto ps = PlayerService::GetInstance();
	long lLength = ps->getTotalTime();
	this->totalTime=lLength;
	std::chrono::hh_mm_ss time{ std::chrono::milliseconds(lLength) };
	auto mm = time.minutes().count() + time.hours().count() * 60;
	auto ss = time.seconds().count();
	this->totalTime_str = std::format("{}{}:{}{}", (mm < 10 ? "0" : ""), mm, (ss < 10 ? "0" : ""), ss);
}
void Player::UpdatePosition(){
	auto ps = PlayerService::GetInstance();
	long lPosition = ps->getPosition();
	this->position = lPosition;
	std::chrono::hh_mm_ss time{ std::chrono::milliseconds(lPosition) };
	auto mm = time.minutes().count() + time.hours().count() * 60;
	auto ss = time.seconds().count();
	this->position_str = std::format("{}{}:{}{}", (mm < 10 ? "0" : ""), mm, (ss < 10 ? "0" : ""), ss);
}

void Player::Play(){
	auto ps = PlayerService::GetInstance();
	ps->Play();
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
void Player::Pause(){
	auto ps = PlayerService::GetInstance();
	ps->Pause();
	this->playing = 0;
	KillTimer(HWNDM[H_PlayingControl],163);
}

void Player::ProgressLoop(){
	if(!this->playing){
		KillTimer(HWNDM[H_PlayingControl],163);
	}
	this->UpdatePosition();
	InvalidateRect(HWNDM[H_PlayingControl], NULL, TRUE);
	//cout<<"1"<<endl;
}
void Player::PlayFromPosition(long position){
	auto ps = PlayerService::GetInstance();
	ps->PlayFromPosition(position);
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
int Player::getVolume(){
	auto ps = PlayerService::GetInstance();
	return ps->GetVolume();
}
void Player::setVolume(int Vnum){
	auto ps = PlayerService::GetInstance();
	ps->SetVolume(Vnum);
}
