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
	this->ps.Close();
	auto path = std::format(LR"(https://music.163.com/song/media/outer/url?id={}.mp3)", this->id);
	this->ps.OpenUrl(path);
    
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
	long lLength = this->ps.getTotalTime();
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
	long lPosition = this->ps.getPosition();
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
	this->ps.Play();
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
void PlayingSong::Pause(){
	this->ps.Pause();
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
	this->ps.PlayFromPosition(position);
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
int PlayingSong::getVolume(){
	return this->ps.GetVolume();
}
void PlayingSong::setVolume(int Vnum){
	this->ps.SetVolume(Vnum);
}
