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
    function route(handle,pathname) {
        console.log("About to route a request for " + pathname);
        if(typeof handle[pathname] === 'function'){
            handle[pathname]();
        }else{
            console.log("No request handler found for " + pathname);
        }
    }
    exports.route = route;
* server.js
#
    var http = require("http");
    var url = require("url");

    function start(route,handle) {
        function onRequest(request, response) {
            var pathname = url.parse(request.url).pathname;
            console.log("Request for " + pathname + " received.");

            route(handle,pathname);

            response.writeHead(200, {"Content-Type": "text/plain"});
            response.write("Hello World");
            response.end();
        }
        http.createServer(onRequest).listen(8888);
            console.log("Server has started.");
    }
    exports.start = start;

* 在index中，将router对象传递到server中，server随后可以调用这个route函数，但实际不需要这些名词，这是个动作行为，只需要调用就行了。
* 设计一个requestHandlers让路由有路可循。
* requestHandlers.js
#
    function start() {
        console.log("Request handler 'start' was called.");
    }
    function upload() {
        console.log("Request handler 'upload' was called.");
    }
    exports.start = start;
    exports.upload = upload;
* index.js
#
    var server = require("./server");
    var router = require("./router");
    var requestHandlers = require("./requestHandlers");

    var handle = {}
    handle["/"] = requestHandlers.start;
    handle["/start"] = requestHandlers.start;
    handle["/upload"] = requestHandlers.upload;
    server.start(router.route,handle);

> 让请求处理程序作出响应
* 在最终的各个函数加入return，令：
#
    请求http://localhost:8888/start,浏览器会输出“Hello Start”，
    请求http://localhost:8888/upload会输出“Hello Upload”，
    请求http://localhost:8888/foo 会输出“404 Not found”。

> 阻塞与非阻塞
* requestHandlers, 加入阻塞，10秒后方返回
#
    function start() {
	console.log("Request handler 'start' was called.");
	function sleep(milliSeconds){
		var startTime = new Date().getTime();
		while(new Date().getTime()<startTime + milliSeconds);
	}
	sleep(10000);
	return "Go Start!";
    }
    function upload() {
        console.log("Request handler 'upload' was called.");
        return "Go Upload";
    }
    exports.start = start;
    exports.upload = upload;
    
* 先运行http://localhost:8888/start 再运行http://localhost:8888/upload 发现upload需要等待start运行完毕。
* ”再node中除了代码，所有一切都是并行执行的“ 即，Node.js可以再不新增额外线程的情况下，依然可以对任务进行并行处理，它通过event loop来实现并行操作，我们可以利用这一点，尽量避免阻塞操作。
* 为了使用非阻塞操作，我们需要使用`回调`，将函数作为参数传递给其它需要花时间做处理的函数。

> 以非阻塞操作进行请求响应

* 现阶段： 请求处理程序(server, router, handler) -> 请求路由 -> 服务器 -> 将请求处理程序返回的内容传递给HTTP。
* 新的实现方式：将服务器传递给内容，即将response对象通过请求路由传递给请求处理程序，处理程序根据对象上的函数进行响应。

* 三处更改 1. server
#
	var http = require("http");
	var url = require("url");

	function start(route, handle){
		function onRequest(request, response){
			var pathname = url.parse(request.url).pathname;
			console.log("Request for " + pathname + " received.");
			//新增第三个参数response
			route(handle, pathname, response);
		}
		http.createServer(onRequest).listen(8888);
		console.log("Server has started.")
	}

	exports.start = start;

* 3. router
#
	function route(handle, pathname, response){
		console.log("About to route a request for " + pathname);
		if(typeof handle[pathname] === 'function'){
			handle[pathname](response);
		}else{
			console.log("No request handler found for " + pathname);
			response.writeHead(404, {"Content-Type": "text/plain"});
			response.write("不是404 not found");
			response.end();
		}
	}

exports.route = route;
* 2. requestHandlers
#
	var exec = require("child_process").exec;

	function start(response){
		console.log("Request handler 'start' was called");
		//阻塞测试
		exec("find /",{timeout:100,maxBuffer:20000*1024}, function(error, stdout,stderr){
			response.writeHead(200,{"Content-Type" : "text/plain"});
			response.write(stdout);
			response.end();
		});
	}

	function upload(response){
		console.log("Request handler 'upload' was called.");
		response.writeHead(200, {"Content-Type":"text/plain"});
		response.write("Hello Upload");
		response.end();
	}

	exports.start = start;
	exports.upload = upload;

> 处理POST请求

* server
#
	var http = require("http");
	var url = require("url");

	function start(route, handle){
		function onRequest(request, response){
			var postData = "";
			var pathname = url.parse(request.url).pathname;
			console.log("Request for " + pathname + " received.");
			//POST小块
			request.setEncoding("utf8");

			request.addListener("data",function(postDataChunk){
				postData += postDataChunk;
				console.log("received POST data chunk " + postDataChunk + ".");
			});

			request.addListener("end",function(){		
				//新增第三个参数response
				route(handle, pathname, response,postData);
			});
		}
		http.createServer(onRequest).listen(8888);
		console.log("Server has started.")
	}

	exports.start = start;

* router
#
	function route(handle, pathname, response,postData){
		console.log("About to route a request for " + pathname);
		if(typeof handle[pathname] === 'function'){
			handle[pathname](response,postData);
		}else{
			console.log("No request handler found for " + pathname);
			response.writeHead(404, {"Content-Type": "text/plain"});
			response.write("不是404 not found");
			response.end();
		}
	}
	exports.route = route;
* requestHandler
#
	var querystring = require("querystring");

	function start(response,postData){
		console.log("Request handler 'start' was called.");
		var body = '<html>'+
			'<head>'+
			'<meta http-equiv="Content-Type" content="text/html; '+
			'charset=UTF-8" />'+
			'</head>'+
			'<body>'+
			'<form action="/upload" method="post">'+
			'<textarea name="text" rows="20" cols="60"></textarea>'+
			'<input type="submit" value="Submit text" />'+
			'</form>'+
			'</body>'+
			'</html>';
		response.writeHead(200, {"Content-Type": "text/html"});
		response.write(body);
		response.end();
	}

	function upload(response,postData){
		console.log("Request handler 'upload' was called.");
		response.writeHead(200, {"Content-Type":"text/plain"});
		response.write("You sent" + querystring.parse(postData).text);
		response.end();
	}

	exports.start = start;
	exports.upload = upload;

> 上传文件

* 使用formidable, server
#
	var http = require("http");
	var url = require("url");
	function start(route, handle) {
	function onRequest(request, response) {
	var pathname = url.parse(request.url).pathname;
	console.log("Request for " + pathname + " received.");
	route(handle, pathname, response, request);
	}
	http.createServer(onRequest).listen(8888);
	console.log("Server has started.");
	}
	exports.start = start;
* index
#
	var server = require("./server");
	var router = require("./router");
	var requestHandlers = require("./requestHandlers");
	var handle = {}
	handle["/"] = requestHandlers.start;
	handle["/start"] = requestHandlers.start;
	handle["/upload"] = requestHandlers.upload;
	handle["/show"] = requestHandlers.show;
	server.start(router.route, handle);
* router
#
	function route(handle, pathname, response, request) {
		console.log("About to route a request for " + pathname);
		if (typeof handle[pathname] === 'function') {
			handle[pathname](response, request);
		} else {
			console.log("No request handler found for " + pathname);
			response.writeHead(404, {"Content-Type": "text/html"});
			response.write("404 Not found");
			response.end();
		}
	}
	exports.route = route;
* requestHandlers
#
	var querystring = require("querystring"),
	fs = require("fs"),
	formidable = require("formidable");
	function start(response) {
		console.log("Request handler 'start' was called.");
		var body = '<html>'+
			'<head>'+
			'<meta http-equiv="Content-Type" content="text/html; '+
			'charset=UTF-8" />'+
			'</head>'+
			'<body>'+
			'<form action="/upload" enctype="multipart/form-data" '+
			'method="post">'+
			'<input type="file" name="upload" multiple="multiple">'+
			'<input type="submit" value="Upload file" />'+
			'</form>'+
			'</body>'+
			'</html>';
		response.writeHead(200, {"Content-Type": "text/html"});
		response.write(body);
		response.end();
	}
	function upload(response, request) {
		console.log("Request handler 'upload' was called.");
		var form = new formidable.IncomingForm();
		console.log("about to parse");
		form.parse(request, function(error, fields, files) {
			console.log("parsing done");
			fs.renameSync(files.upload.path, "/Users/unlimitediw/Downloads/NodeJS/start/uploadFile/tmp/test.png");
			response.writeHead(200, {"Content-Type": "text/html"});
			response.write("received image:<br/>");
			response.write("<img src='/show' />");
			response.end();
		});
	}
	function show(response, postData) {
		console.log("Request handler 'show' was called.");
		fs.readFile("/Users/unlimitediw/Downloads/NodeJS/start/uploadFile/tmp/test.png", "binary", function(error, file) {
			if(error) {
				response.writeHead(500, {"Content-Type": "text/plain"});
				response.write(error + "\n");
				response.end();
			} else {
				response.writeHead(200, {"Content-Type": "image/png"});
				response.write(file, "binary");
				response.end();
			}
		});
	}
	exports.start = start;
	exports.upload = upload;
	exports.show = show;
