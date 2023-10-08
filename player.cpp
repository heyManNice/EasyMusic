#include "myhead.h"

#include "apiservice.h"

void PlayingSong::SetMusic(int id){
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
	
	this->name = Utf8ToGbk(song.name);

	auto [codePic, dataPic] = apiservice::HTTP_Get(songresult->song.albumPicUrl);
	if (codePic)
	{
		//TODO: exit
	}
	this->albumPic = dataPic;
	
	this->artist = Utf8ToGbk(song.artists[0].name);
	//先解析这两个需要的，剩下的等换上官方的api再解析
	
	//std::cout<<this->id<<endl;
	if(this->name.length()){
		//如果有音乐就先停止音乐
		mciSendStringW(L"close now_mp3", 0, 0, 0);
	}
	std::wstring path = L"https://music.163.com/song/media/outer/url?id="+std::to_wstring(this->id)+L".mp3";
    std::wstring command = L"open \"" + path + L"\" type mpegvideo alias now_mp3";
    mciSendStringW(command.c_str(), NULL, 0, NULL);
    
	this->getTotalTime_str();
	this->getPosition_str();
    player.newVolume=player.getVolume();
    //重绘底部左下角的歌曲信息
    InvalidateRect(HWNDM[H_PlayingInfo_m], NULL, TRUE);
    //重绘进度条相关信息
	InvalidateRect(HWNDM[H_PlayingControl], NULL, TRUE);
	//重绘右下角按钮
	InvalidateRect(HWNDM[H_PlayingSet_m], NULL, TRUE);
}
void PlayingSong::getTotalTime_str(){
	wchar_t sLength[100];
	long lLength;
	mciSendStringW(L"status now_mp3 length", sLength, 100, 0);
	lLength = wcstol(sLength, NULL, 10);
	this->totalTime=lLength;
	//计算歌曲长度
	int mm = 0;
	int ss;
	lLength = lLength/1000;
	while(lLength>59){
		lLength-=60;
		mm++;
	}
	ss=lLength;
	this->totalTime_str = std::format("{}{}:{}{}", (mm < 10 ? "0" : ""), mm, (ss < 10 ? "0" : ""), ss);
}
void PlayingSong::getPosition_str(){
	wchar_t sPosition[100];
	long lPosition;
	mciSendStringW(L"status now_mp3 position", sPosition, 100, 0);
	lPosition = wcstol(sPosition, NULL, 10);
	this->position = lPosition;
	//cout<<lPosition<<endl;
	//计算当前播放的长度
	int mm = 0;
	int ss;
	lPosition = lPosition/1000;
	while(lPosition>59){
		lPosition-=60;
		mm++;
	}
	ss=lPosition;
	this->position_str = std::format("{}{}:{}{}", (mm < 10 ? "0" : ""), mm, (ss < 10 ? "0" : ""), ss);
}

void PlayingSong::Play(){
	mciSendStringW(L"play now_mp3", NULL, 0, NULL);
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
void PlayingSong::Pause(){
	mciSendStringW(L"Pause now_mp3", NULL, 0, NULL);
	this->playing = 0;
	KillTimer(HWNDM[H_PlayingControl],163);
}

void PlayingSong::ProgressLoop(){
	if(!this->playing){
		KillTimer(HWNDM[H_PlayingControl],163);
	}
	this->getPosition_str();
	InvalidateRect(HWNDM[H_PlayingControl], NULL, TRUE);
	//cout<<"1"<<endl;
}
void PlayingSong::PlayFromPosition(long position){
	std::wstring command = L"play now_mp3 from "+std::to_wstring(position)+L" to "+std::to_wstring(this->totalTime);
	mciSendStringW(command.c_str(), NULL, 0, NULL);
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
int PlayingSong::getVolume(){
	wchar_t volume[100]; 
	mciSendStringW(L"status now_mp3 volume", volume, sizeof(volume), 0);
	return _wtoi(volume);
}
void PlayingSong::setVolume(int Vnum){
	std::wstring command = L"setaudio now_mp3 volume to "+std::to_wstring(Vnum);
	mciSendStringW(command.c_str(), 0, 0, 0);
}
