# 开发框架头文件路径
PUBINCL = -I/project/public

# 开发框架cpp文件路径
PUBCPP = /project/public/_public.cpp

# 编译参数
CFLAGS = -g

all: procctl shm HBMechanism checkproc test gzipfiles deletefiles ftpclient

procctl:procctl.cpp
	g++ $(CFLAGS) -o procctl procctl.cpp $(PUBINCL) $(PUBCPP) -lm -lc

	cp procctl ../bin/.

shm:shm.cpp
	g++ $(CFLAGS) -o shm shm.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp shm ../bin/.

HBMechanism:HBMechanism.cpp
	g++ $(CFLAGS) -o HBMechanism HBMechanism.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp HBMechanism ../bin/.

checkproc:checkproc.cpp
	g++ $(CFLAGS) -o checkproc checkproc.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp checkproc ../bin/.

test:test.cpp
	g++ $(CFLAGS) -o test test.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp test ../bin/.

gzipfiles:gzipfiles.cpp
	g++ $(CFLAGS) -o gzipfiles gzipfiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp gzipfiles ../bin/.

deletefiles:deletefiles.cpp
	g++ $(CFLAGS) -o deletefiles deletefiles.cpp $(PUBINCL) $(PUBCPP) -lm -lc
	cp deletefiles ../bin/.

ftpclient:ftpclient.cpp
	g++ $(CFLAGS) -o ftpclient ftpclient.cpp /project/public/_ftp.cpp $(PUBCPP) $(PUBINCL) -L/project/public -lftp -lm -lc
	cp ftpclient ../bin/.

clean:
	rm -f procctl shm HBMechanism checkproc test gzipfiles deletefiles ftpclient
