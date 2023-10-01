# 很容易音乐
这是一个致力于用C++和win32api打造的开源第三方网易云音乐。就目前而言，与普通的项目相比，这个项目更像一个“玩具”项目。由于作者是编程新手，水平有限，项目中可能有相当多的问题代码。因此我不建议你从它当中学习我们的编程习惯。

# 开源的目的
此项目以BSD 3-Clause “New” or “Revised” License协议开源。我希望有更多人参与到这个项目的贡献中，促进交流，共同学习与进步。与普通的项目不同的是，这个项目更像一个“玩具”项目，实际上可能并不能产生多大的价值。所以无论你的技术、你的年龄段、你的想法、你的性别如何，只要你对C++、win32api或者此项目感兴趣，任何人都可以参与这个项目的开发。对于新手来说，和我一样，你只管放心大胆的去完成你的想法。而对于老手来说，你可以很容易的发现我们的代码中存在的问题，如果你能从中指出我们的问题，这对我们的帮助会非常大。我希望新手和老手能够友好交流，互相理解互相包容。同时，如果你有任何的想法都可以提出来。
# TODO清单

- [x] 基本播放器类
- [x] 页面导航
- [x] 音乐搜索
- [x] 窗口大小的基本操作
- [x] tooltip提示框
- [ ] 解决GDI资源泄露问题
- [ ] 解决窗口闪烁的问题
- [ ] 登录等用户相关类
- [ ] 音乐播放列表
- [ ] jpeg解析为bitmap
- [ ] 各导航相关页面
- [ ] 动画引擎
- [ ] 切换主题
- [ ] 页面滚动功能
- [ ] 优化项目结构，力争组件化
- [ ] 系统托盘图标
- [ ] 接入网易云官方api
- [ ] 桌面歌词
- [ ] 歌词预览界面
- [ ] 接入系统Thumbnail Toolbar

# 截图
![alt 主页](./SampleImage/1.png)  

![alt 搜索页](./SampleImage/2.png)  

# 原项目编译器
[MinGW GCC13.1.10](https://github.com/niXman/mingw-builds-binaries)

# 原项目编辑器
DEV-C++ 6.7.5

# 用到的Github开源项目
[yyjson](https://github.com/ibireme/yyjson)  
[NeteaseCloudMusicApi](https://github.com/Binaryify/NeteaseCloudMusicApi)

# 目前所使用的线上api来源
[cloud-music.pl-fe.cn](http://cloud-music.pl-fe.cn/)

# 用到的静态链接库
音乐播放：WinMM.Lib  
网络请求：wininet.Lib  
窗口效果：dwmapi.lib  
解析jpeg文件：FreeImage.lib(还未开始使用)  
绘图设备：gdiplus.lib(目前使用gdi)

# 各文件(夹)功能
## 文件夹
lib：静态链接库  
res：资源文件  
yyjson：yyjson解析库相关文件  
SampleImage：readme.md的图片文件
## 头文件
EasyMusic.h：DEV-C++自动生成  
EasyMusic_private.h：DEV-C++自动生成  
FreeImage.h：解析图片  
myhead.h：项目万用头（各种定义都放里面）
## cpp文件
allClass.cpp：窗口类注册  
allProc.cpp：窗口事件循环过程  
foottool.cpp：底部栏  
gdiDevice.cpp：gdi绘图设备复用和安全切换  
headtool.cpp：顶部栏  
Lmenu.cpp：左侧边导航栏  
main.cpp：主程序入口  
mytools.cpp：各种小工具  
network.cpp：网络请求相关  
PlayingSong.cpp：音乐播放器抽象类  
tooltip.cpp：tootip鼠标悬浮提示框
## 其他文件
EasyMusic.dev：DEV-C++的项目工程属性文件  
EasyMusic.ico：项目图标  
Makefile.win：编译规则文件（DEV-C++自动生成）
