/// @brief 程序名:crtsurfdata1.cpp 本程序用于生成全国气象站点观测的分钟数据
/// @brief 作者:alina

#include "_public.h"

CLogFile logfile;

int main(int argc, char *argv[]) {
  // inifile outpath logfile
  if (argc != 4) {
    printf("using:./crtsurfdata1 inifile outpath logfile\n");
    printf(
        "example:/project/idc1/bin/crtsurfdata1 /project/idc1/ini/stcode.in "
        "/tmp/surfdata /log/idc/fdata1.log\n");
    printf("inifile 全国气象站点参数文件名。\n");
    printf("outpath 全国气象站点数据文件存放目录。\n");
    printf("logfile 本程序运行的日志文件名。\n");
    return -1;
  }
  if (logfile.Open(argv[3]) == false) {
    printf("logfile.Open(%s) failed.\n", argv[3]);
    return -1;
  }
  logfile.Write("crtsufdata1 开始运行。\n");

  logfile.Write("crtsufdata1 结束运行。\n");

  return 0;
}