> 最近一次更新：app 层增加接口说明，common 层增加一个 Player 类

## 开发环境需求

* Visual Stdio 2022
* Qt 5.14.2

配置环境：

* Visual Stdio - 下载、选择“使用C++的桌面开发”工作负载
* Qt - [下载](https://download.qt.io/archive/qt/5.14/5.14.2/) ，配置[参考链接](https://blog.csdn.net/qq_45739057/article/details/125037966)（有些可能不需要，但先这么配）
* Qt 官网下载会比较慢，但不推荐用 single 文件夹里的或者镜像（本人下了 2G 的包发现解压不了，而镜像很多版本的文件夹失效了（包括我们配置的 5.14.2）

## 如何编译运行可执行文件？

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -A x64
MSBuild ALL_BUILD.vcxproj /t:build /p:Configuration=Debug
```

### 报错解决方案

* 找不到 Qt.cmake（类似的名字

  * 在最上层的 CMakeList.txt 增加语句（你自己的相应路径） `set(CMAKE_PREFIX_PATH D:/Qt/Qt5.14.2/5.14.2/msvc2017_64/lib/cmake/Qt5)`
* 运行 .exe 文件找不到 *.dll

  * 增加如图所示的环境变量（用户变量） PATH
    ![1720081886589](image/README/1720081886589.png)

## git 规范

* 决定用一个仓库管理，比较方便，[仓库地址](https://github.com/smdrr11037/GoldMiner)
* 每个人在自己的分支上完成负责的部分，分支以自己的 id/名字缩写 命名，并直接推送分支到仓库
* 如果需要 merge，打开 github，创建 Pull Request（最好不要自己通过）
* 等待当前组长审核，通过后 github 会发邮件通知大家拉取新的代码
* 不需要删除旧分支，一个人的改动固定提交到该分支即可

---

```mermaid
gitGraph
   commit id: "初始化项目"
   checkout main
   commit id: "创建 main 分支"
   
   branch Alice
   checkout Alice
   commit id: "Alice: 添加新功能1"
   commit id: "Alice: 完成功能1"

   checkout main
   merge Alice id: "合并 Alice 的功能1"

   branch Bob
   checkout Bob
   commit id: "Bob: 修复 bug"
   commit id: "Bob: 完成修复"

   checkout main
   merge Bob id: "合并 Bob 的修复"

   branch Charlie
   checkout Charlie
   commit id: "Charlie: 添加新功能2"
   commit id: "Charlie: 完成功能2"

   checkout main
   merge Charlie id: "合并 Charlie 的功能2"

   checkout main
```

tips: 本地切换到 CounterDemo 分支（即其他分支）的方法

* `git checkout -b CouterDemo origin/CounterDemo`
* 注意，`pull` 指令只会拉取当前所在分支对应的远程分支，不会更新所有分支

## 命名规范

* 类名/文件名 - 帕斯卡（Pascal）命名法 `ReplacePart.cpp`
* 成员变量名 - `m_replacePart`
* .h 文件要加 `#ifndef` 等等

## linux 编译运行

1. g++ 版本 8.0 以上，有 c++17
2. `sudo apt-get install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools` 安装 qt 库
3. `sudo apt-get install build-essential` 检查一下依赖
4. common 里删了 any.h 头文件，etlbase 里 types 改成 long，any（有上下两处） 改用 std 库
5. CMakeLists.txt 中改用 cxx17
6. 编译

```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
```
