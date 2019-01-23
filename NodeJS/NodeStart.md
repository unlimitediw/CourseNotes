> Micro Project ZERO

* 构造一个HTTP服务器。
* 构造一个`路由`将`请求`对应到`请求处理程序request handler`， 根据请求url给出不同的响应。
* 当请求被服务器接受并通过路由传递后，使用`请求处理程序`。
* 路由也要处理post数据，并且把数据封装成更友好的格式传递给`请求处理程序`，因此需要`请求数据处理功能`。
* 同时要将内容显示出来，因此需要`视图逻辑`。
* 最后需要`上传处理功能`帮助用户上传图片。

> 一个基础的HTTP服务器

* 分析HTTP服务器
#
    var http = require("http"); //请求node自带的http模块，并赋值给变量http
    //调用http模块的函数createServer返回listen方法，并指定http服务器端口号
    //也可以使用匿名传递
    function onRequest(request, response) {
      console.log("Request received.");
      response.writeHead(200, {"Content-Type": "text/plain"});
      response.write("Basic HTTP");
      response.end();
    }
    http.createServer(onRequest).listen(8888);
    console.log("Server has started.");

* 进行函数传递, 向createServer函数传递了一个匿名函数

* Why? - 基于事件驱动的回调
  * 回调：请求任何时候都可能到达，但我们的服务器却在单进程中运行。我们向创建它的方法传递了一个函数，使得无论何时服务器接收到一个请求，这个函数就会被调用。（给某个方法传递了一个函数，这个方法在有相应事件发生时调用这个函数来进行回调）
  
> 服务器是如何处理请求的

* onRequest(request, response)，request和response是可以被用来处理HTTP请求细节的对象。
* 使用response.writeHead()函数发送一个HTTP状态200和HTTP头的内容类型（content-type)并使用response.write()在HTTP相应主体中发送文本。最终调用response.end()完成相应。

> 服务器模块

* 把某段代码编变成模块意味着我们需要把我们希望提供功能的部分导出到请求这个模块的脚本。在此，我们将服务器脚本放入start函数，然后导出函数。
#
    var http = require("http");
    function start() {
    function onRequest(request, response) {
      console.log("Request received.");
      response.writeHead(200, {"Content-Type": "text/plain"});
      response.write("Hello World");
      response.end();
    }
    http.createServer(onRequest).listen(8888);
      console.log("Server has started.");
    }
    exports.start = start;

* 同时使用index.js调用它
#
    var server = require("./server");
    server.start();


> 制作请求的路由

* http + url + query
* 编写路由router.js
#
    function route(pathname) {
      console.log("About to route a request for " + pathname);
    }
    exports.route = route;

* 在index中，