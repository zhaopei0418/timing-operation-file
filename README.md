# C11标准＋(WINDOOWS API | LINUX/UNIX/APPLE API)

# 使用的第三方库

log.c https://github.com/rxi/log.c

tiny-regex-c https://github.com/kokke/tiny-regex-c

## 源码编译
```
git clone https://github.com/zhaopei8948/timing-operation-file
cd timing-operation-file
windows {
md build
cd build
cmake -G"MinGW Makefiles" ..\
make

.\tof #查看帮助信息 | .\tof -h
}

linux,apple,unix {
mkdir -v build
cd build
cmake ../
make

./tof | ./tof -h
}
```
![image](https://github.com/zhaopei8948/timing-operation-file/blob/master/images/tof-help.png)
