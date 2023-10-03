#include "myhead.h"


void PlayingSong::SetMusic(int id){
	this->id = id;
	this->playing = 0;
	//应该要在https://github.com/Binaryify/NeteaseCloudMusicApi
	//中分析使用官方的api，构造一个官方的请求类，因为时间问题，此处使用了网上找的第三方代理接口

	string url = "/song/detail?ids=" + to_string(this->id); 
	auto [code, data] = net_GET(url);
	//cout<<song_result;
	
	yyjson_doc *doc = yyjson_read(data.c_str(), data.size(), 0);
	yyjson_val *root = yyjson_doc_get_root(doc);
	yyjson_val *temp = yyjson_obj_get(root, "songs");
	temp = yyjson_arr_get(temp,0);
	
	this->name = Utf8ToGbk(yyjson_get_str(yyjson_obj_get(temp, "name")));

	auto alobj = yyjson_obj_get(temp, "al");
	std::string picurl = yyjson_get_str(yyjson_obj_get(alobj, "picUrl"));
	auto [codePic, dataPic] = net_GETNew(picurl);
	this->albumPic = dataPic;
	
	temp = yyjson_obj_get(temp,"ar");
	temp = yyjson_arr_get(temp,0);
	
	this->artist = Utf8ToGbk(yyjson_get_str(yyjson_obj_get(temp, "name")));
	//先解析这两个需要的，剩下的等换上官方的api再解析
	
	yyjson_doc_free(doc);
	
	
	cout<<this->id<<endl;
	if(this->name.length()){
		//如果有音乐就先停止音乐
		mciSendString("close now_mp3", 0, 0, 0);
	}
	string path = "https://music.163.com/song/media/outer/url?id="+to_string(this->id)+".mp3";
    string command = "open \"" + path + "\" type mpegvideo alias now_mp3";
    mciSendString(command.c_str(), NULL, 0, NULL);
    
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
	char sLength[100];
	long lLength;
	mciSendString("status now_mp3 length", sLength, 100, 0);
	lLength = strtol(sLength, NULL, 10);
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
	//不用format，好像是因为编译器不支持c++ 20
	this->totalTime_str = (mm<10?"0":"") + to_string(mm)+":" + (ss<10?"0":"") + to_string(ss);
}
void PlayingSong::getPosition_str(){
	char sPosition[100];
	long lPosition;
	mciSendString("status now_mp3 position", sPosition, 100, 0);
	lPosition = strtol(sPosition, NULL, 10);
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
	this->position_str = (mm<10?"0":"") + to_string(mm)+":" + (ss<10?"0":"") + to_string(ss);
}

void PlayingSong::Play(){
	mciSendString("play now_mp3", NULL, 0, NULL);
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
void PlayingSong::Pause(){
	mciSendString("Pause now_mp3", NULL, 0, NULL);
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
	string command = "play now_mp3 from "+to_string(position)+" to "+to_string(this->totalTime);
	mciSendString(command.c_str(), NULL, 0, NULL);
	if(this->playing == 0){
		this->playing = 1;
		SetTimer(HWNDM[H_PlayingControl],163,1000,NULL);
	}
}
int PlayingSong::getVolume(){
	char volume[100]; 
	mciSendString("status now_mp3 volume", volume, sizeof(volume), 0);
	return atoi(volume);
}
void PlayingSong::setVolume(int Vnum){
	string command = "setaudio now_mp3 volume to "+to_string(Vnum);
	mciSendString(command.c_str(), 0, 0, 0);
}
