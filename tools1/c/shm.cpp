/**
**********************************************************************************************************************************************************************************************************************************
* @file:	deletefiles.cpp
* @author:	alina
* @date:	2023.04.15. 10:26:17 Saturday
* @brief:	共享内存及Linux信号的基本操作
**********************************************************************************************************************************************************************************************************************************
**/

#include "_public.h"

CSEM sem;  // 创建一个给共享内存加锁的信号量

struct st_pid {
  int pid;
  char name[51];
};

int main(int argc, char *argv[]) {
  int shmid;
  if (argc < 2) {
    printf("using: ./shm procname\n");
    return 0;
  }
  // 获取或者创建共享内存，键值为0x5005
  if ((shmid = shmget(0x5005, sizeof(st_pid), 0640 | IPC_CREAT)) == -1) {
    printf("shmget(0x5050) failed\n");
    return -1;
  }

  // 如果信号量存在，获取信号量；如果没有信号量则创建信号量，key=0x5005
  if (sem.init(0x5005) == false) {
    printf("sem.init(0x5005) failed\n");
    return -1;
  }
  // 用于指向共享内存的结构体变量
  st_pid *stpid = 0;
  // 把共享内存连接到当前进程的地址空间
  if ((stpid = (st_pid *)shmat(shmid, 0, 0)) == (st_pid *)-1) {
    printf("shmat failed\n");
    return -1;
  }

  // 显示当前时间与信号量
  printf("time=%ld,val=%d\n", time(0), sem.value());
  // 加锁
  sem.P();
  printf("time=%ld,val=%d\n", time(0), sem.value());
  printf("pid = %d, name = %s\n", stpid->pid, stpid->name);
  stpid->pid = getpid();
  sleep(10);
  strcpy(stpid->name, argv[1]);
  printf("pid = %d, name = %s\n", stpid->pid, stpid->name);
  printf("time=%ld,val=%d\n", time(0), sem.value());
  // 解锁
  sem.V();
  // 显示当前时间与信号量
  printf("time=%ld,val=%d\n", time(0), sem.value());
  // 把共享内存从当前进程地址空间分离
  shmdt(stpid);
  // 删除共享内存
  if ((shmctl(shmid, IPC_RMID, 0)) == -1) {
    printf("shmctl failed\n");
    return -1;
  }
  return 0;
}
