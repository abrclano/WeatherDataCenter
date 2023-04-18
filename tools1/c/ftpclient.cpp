/**
****************************************************************
* @file:	ftpclient.cpp
* @author:	alina
* @date:	2023.04.18 16:00:29 Tuesday
* @brief:	ftp客户端测试(请自行添加libftp.so路径)
****************************************************************
**/

#include "_ftp.h"

Cftp ftp;

int main(int argc, char* argv[]) {
  // 登录
  if (ftp.login("127.0.0.1:21", "alina", "qq520") == false) {
    printf("ftp.login() failed.\n");
    return -1;
  }
  printf("ftp.login() ok.\n");

  // 获取文件最后修改时间
  if (ftp.mtime("/home/alina/ftplib/upload/README.md") == false) {
    printf("ftp.mtime() failed.\n");
    return -1;
  }
  printf("ftp.mtime() ok. mtime=%s\n", ftp.m_mtime);

  // 获取文件大小
  if (ftp.size("/home/alina/ftplib/upload/README.md") == false) {
    printf("ftp.size() failed.\n");
    return -1;
  }
  printf("ftp.size() ok. size=%d\n", ftp.m_size);

  // 列出路径下的文件名及子目录
  if (ftp.nlist("/home/alina/ftplib", "/tmp/idc/ftp/nlist.lst") == false) {
    printf("ftp.nlist() failed.\n");
    return -1;
  }
  printf("ftp.nlist() ok.\n");

  // 上传文件
  if (ftp.put("/project/tools1/c/ftpclient.cpp",
              "/home/alina/ftplib/upload/ftpclient.cpp", true) == false) {
    printf("ftp.put() failed.\n");
    return -1;
  }
  printf("ftp.put() ok.\n");

  // 下载文件
  if (ftp.get("/home/alina/ftplib/upload/README.md", "/tmp/idc/ftp/README.md",
              true) == false) {
    printf("ftp.get() failed.\n");
    return -1;
  }
  printf("ftp.get() ok.\n");
  // 登出
  ftp.logout();
  return 0;
}
