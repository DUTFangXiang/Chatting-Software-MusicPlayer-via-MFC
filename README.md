# Chatting-Software-MusicPlayer-via-MFC
　　基于MFC的单文档框架搭建的，在实现聊天系统客户端与服务器搭建与功能实现基础上，还增加了自己的想法，即MCI音乐播放器的功能
## 功能介绍
-----------------------------------------------------------------------------------------------------------------
### 1、MCI播放器功能：
　　MCI播放器的设计是利用MFC应用程序、媒体控制接口MCI的基本知识而设计的。
  
　　本次设计简单，是建立在服务器客户端上构建的一个非模态对话框搭建的。
  
　　MCI（Media Control Interface）媒体控制接口是MircroSoft提供的一组多媒体设备和文件的标准接口，它的好处是可以方便地控制绝大多数多媒体设备包括音频、视频、影碟、录像等多媒体设备，而不需要知道它们的内部工作状况。它所支持的媒体格式包括avi、wav、mpeg等等。
  
　　作为关键核心的地方，我本次制作了一个简约风格的音乐播放器，并且放在了服务器上，可以实现边监听端口与客户端聊天，边听音乐。这样客户端的端口就需要制作成非模态对话框

### 2、基于TCP/IP协议的聊天功能
　　在这里，MFC提供了一个异步类CAsyncSocket，它封装了异步、非阻塞Socket的基本功能，用它做常用的网络通信软件很方便。
  
　　但它屏蔽了Socket的异步、非阻塞等概念，开发人员无需了解异步、非阻塞Socket的原理和工作机制。提到CAsyncSocket类我们就要想到CSocket类。CSocket是MFC在CAsyncSocket基础上派生的一个同步阻塞Socket的封装类。在运作机理上它与CAsyncSocket类有很大不同。 Socket事件首先是作为一个消息发给CSocketWnd窗口对象，这个消息肯定需要经过线程消息队列的分发，最终CSocketWnd窗口对象收到这些消息就调用相应的回调函数（OnConnect()等）。
  
　　所以，CSocket在调用Connect()之后，如果返回一个WSAEWOULDBLOCK错误时，它马上进入一个消息循环，就是从当前线程的消息队列里取关心的消息，如果取到了WM_PAINT消息，则刷新窗口，如果取到的是Socket发来的消息，则根据Socket是否有操作错误码，调用相应的回调函数（OnConnect()等）。
  
　　而CAsyncSocket的Create()函数，除了创建了一个套接字以外，还创建了个CSocketWnd窗口对象，并使用WSAAsyncSelect()将这个SOCKET与该窗口对象关联，以让该窗口对象处理来自Socket的事件(消息)，然而CSocketWnd收到事件之后，只是简单地回调CAsyncSocket::OnReceive()，CAsyncSocket::OnSend()，CAsyncSocket::OnAccept()，CAsyncSocket::OnConnect()等虚函数。所以CAsyncSocket的派生类，只需要在这些虚函数里添加发送和接收的代码。
  
　　这里，由于本次设计功能简单，并且无需考虑太多，所以使用的是CAsyncSocket类，这样既节约了设计时间，同时也方便了在程序设计上的布局与平台搭建，异步非阻塞更适合我本次设计的系统。
