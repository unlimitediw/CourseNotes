### C++回顾
* 参数传递的不同方式（值传递，引用传递和常量引用返回等）
* 函数或方法返回的不同方式
* 模板函数
* 递归函数
* 常量函数
* 内存分配和释放函数
* 异常处理结构
* 类与模板类
* 类的公有成员,保护成语和私有成员
* 友元
* 操作符重载
* 标准模板库
* 动态分配与释放一维和二维数组
* 求解二次方程
* 生成n个元素的所有排列方式
* 寻找n个元素的最大值

> 模版函数
* destructor负责释放形式参数（a，b，c）
#
    template<class T>
    T abc(T a, T b, T c){
        return a + b + c;
    }

> 引用参数
* 在函数被调用及返回时，操作1:构造函数把实参复制给形参，操作2:当函数返回时启用destructor。而对于引用参数而言不需要这些操作。
#
    template<class T>
    T abc(T& a, T& b, T& c){
        return a + b + c;
    }

> 常量引用参数：这种模式指明的引用参数不能被函数修改
#
    template<class T>
    T constAbc(const T&a, const T&b, const T&c){
        //a = 5 -> error: cannot assign to const
        return a + b + c;
    }

> 引用返回：当函数结束时，返回值所占用的空间将被释放，为了不丢失这个值，需要将这个值从临时变量复制到调用该函数的环境中。
#
    //reference return
    T& refAbc(T a, T b, T& c){
        return a;
    }
