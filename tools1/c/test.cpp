/**
**********************************************************************************************************************************************************************************************************************************
* @file:	deletefiles.cpp
* @author:	alina
* @date:	2023.04.15. 10:26:17 Saturday
* @brief:	测试checkproc是否有效
**********************************************************************************************************************************************************************************************************************************
**/

#include "_public.h"

void EXIT(int sig) {
  printf("sig=%d\n", sig);
  if (sig == 2) {
    exit(0);
  }
}

CPActive Active;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("using:./test procname timeout\n\n");
    return 0;
  }
  signal(2, EXIT);
  signal(15, EXIT);
  Active.AddPInfo(atoi(argv[2]), argv[1]);
  while (true) {
    Active.UptATime();  // 注释掉则超时
    sleep(10);
  }
  return 0;
}