> NodeJS and JS

* Node.js是一个让javascript运行在浏览器之外的平台。

> What can Node.js do
* 内置了HTTP服务器
* 开发功能
  * 具有复杂逻辑的`网站`
  * 基于社交网络的大规模`Web应用`
  * Web `Socket服务器`
  * TCP/UDP套接字应用程序
  * 命令行工具
  * 交互式`终端程序`
  * 带有`图形用户界面`的本地应用程序
  * 单元测试工具
  * 客户端javascript编辑器

> 异步式I/O与事件驱动
* Node.js使用的是单线程模型
  * 对于所用I/O都采用异步式的请求方式，避免频繁上下文更换。
  * 回调机制，非阻塞，如`exec("find /",{timeout:100,maxBuffer:20000*1024}, functionA(error, stdout,stderr)})
  * 使用`事件循环`，不断地检查有没有为处理的事件，依次予以处理。
  * 对于网络攻击，只是放入事件请求队列，不会增大性能开销。

> 模块和包
* 模块
  * 例如http是Node.js的一个模块，内部用C++实现，外部用JavaScript封装，通过require('http')获取模块，使用其中的对象。
  * 用exports将对象封装到模块中
* 包：将文件夹封装为一个模块
