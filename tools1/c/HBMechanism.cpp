/**
**********************************************************************************************************************************************************************************************************************************
* @file:	deletefiles.cpp
* @author:	alina
* @date:	2023.04.15. 10:26:17 Saturday
* @brief:	程序的心跳机制
**********************************************************************************************************************************************************************************************************************************
**/

#include <unistd.h>

#include <cstdio>

#include "_public.h"

const int MAXNUNP_ = 1000;
const int SHMKEYP_ = 0x5095;
const int SEMKEYP_ = 0x5095;

struct st_pinfo {
  int pid;         // 进程id
  int timeout;     // 超过时间
  char pname[51];  // 进程名称
  time_t atime;    // 最后一次心跳时间
};

class PActive {
 private:
  CSEM m_sem;
  int m_shmid;
  int m_pos;
  st_pinfo *m_shm;

 public:
  PActive();
  bool AddPInfo(const int timeout, const char *pname);
  bool UpAtime();
  ~PActive();
};

PActive::PActive() : m_shmid(-1), m_pos(-1), m_shm(0) {}
bool PActive::AddPInfo(const int timeout, const char *pname) {
  if (m_pos != -1) {
    return true;
  }
  if ((m_shmid = shmget(SHMKEYP_, MAXNUNP_ * sizeof(st_pinfo),
                        0640 | IPC_CREAT)) == -1) {
    printf("shmget(%x) failed\n", SHMKEYP_);
    return false;
  }
  if (m_sem.init(SEMKEYP_) == false) {
    printf("sem.init(%x) failed\n", SEMKEYP_);
    return false;
  }
  m_shm = (st_pinfo *)shmat(m_shmid, 0, 0);
  st_pinfo stpinfo;
  memset(&stpinfo, 0, sizeof(st_pinfo));
  stpinfo.pid = getpid();
  STRNCPY(stpinfo.pname, sizeof(stpinfo.pname), pname, 50);
  stpinfo.timeout = timeout;
  stpinfo.atime = time(0);
  for (int i = 0; i < MAXNUNP_; i++) {
    if ((m_shm + i)->pid == stpinfo.pid) {
      m_pos = i;
      break;
    }
  }
  m_sem.P();
  if (m_pos == -1) {
    for (int i = 0; i < MAXNUNP_; i++) {
      if ((m_shm + i)->pid == 0) {
        m_pos = i;
        break;
      }
    }
  }
  if (m_pos == -1) {
    m_sem.V();
    printf("共享内存空间已用完\n");
    return false;
  }
  memcpy(m_shm + m_pos, &stpinfo, sizeof(st_pinfo));
  m_sem.V();

  return true;
}
bool PActive::UpAtime() {
  if (m_pos == -1) {
    return false;
  }
  (m_shm + m_pos)->atime = time(0);
  return true;
}
PActive::~PActive() {
  if (m_pos != -1) {
    memset(m_shm + m_pos, 0, sizeof(st_pinfo));
  }
  if (m_shm != 0) {
    shmdt(m_shm);
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("using:./HBMechanism\n");
    return 0;
  }
  PActive Active;
  Active.AddPInfo(30, argv[1]);
  while (true) {
    Active.UpAtime();
    sleep(10);
  }
  return 0;
}
