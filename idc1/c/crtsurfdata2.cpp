/// @brief 程序名:crtsurfdata2.cpp 本程序用于生成全国气象站点观测的分钟数据
/// @brief 作者:alina

#include "_public.h"

// 全国气象站点数据结构
struct st_stcode {
  char provname[31];  // 省
  char obtid[11];     // 站号
  char obtname[31];   // 站名
  double lat;         // 经度
  double lon;         // 纬度
  double height;      // 海拔高度
};

// 存放气象站点数据的容器
vector<struct st_stcode> vstcode;

// 把数据加载到容器vstcode中
bool LoadSTCode(const char* inifile);

CLogFile logfile;

int main(int argc, char* argv[]) {
  // inifile outpath logfile
  if (argc != 4) {
    printf("using:./crtsurfdata2 inifile outpath logfile\n");
    printf(
        "example:/project/idc1/bin/crtsurfdata2 /project/idc1/ini/stcode.ini "
        "/tmp/surfdata /log/idc/fdata2.log\n");
    printf("inifile 全国气象站点参数文件名。\n");
    printf("outpath 全国气象站点数据文件存放目录。\n");
    printf("logfile 本程序运行的日志文件名。\n");
    return -1;
  }
  if (logfile.Open(argv[3]) == false) {
    printf("logfile.Open(%s) failed.\n", argv[3]);
    return -1;
  }
  logfile.Write("crtsufdata2 开始运行。\n");

  // 把数据加载到容器vstcode中
  if (LoadSTCode(argv[1]) == false) {
    return -1;
  }

  logfile.Write("crtsufdata2 结束运行。\n");

  return 0;
}

// 把数据加载到容器vstcode中
bool LoadSTCode(const char* inifile) {
  CFile File;
  // 打开站点参数文件
  if (File.Open(inifile, "r") == false) {
    logfile.Write("File.Open(%s) failed.\n", inifile);
    return false;
  }
  char strBuffer[301];
  CCmdStr CmdStr;
  st_stcode stcode;
  while (true) {
    // 从站点参数文件读取一行，如果已经读完，跳出循环。
    bool Fgets(char* buffer, const int readsize, bool bdelcrt = false);
    if (File.Fgets(strBuffer, 300, true) == false) {
      break;
    }
    logfile.Write("=%s=\n", strBuffer);
    // 把读取到的一行进行拆分
    CmdStr.SplitToCmd(strBuffer, ",", true);
    if (CmdStr.CmdCount() != 6) {
      continue;
    }

    // 把站点参数的每个数据保存到站带你参数结构体中
    CmdStr.GetValue(0, stcode.provname, 30);  // 省
    CmdStr.GetValue(1, stcode.obtid, 10);     // 站号
    CmdStr.GetValue(2, stcode.obtname, 30);   // 站名
    CmdStr.GetValue(3, &stcode.lat);          // 经度
    CmdStr.GetValue(4, &stcode.lon);          // 纬度
    CmdStr.GetValue(5, &stcode.height);       // 海拔高度
    // 把站点参数结构体存入站点参数容器中
    vstcode.push_back(stcode);
  }

  // 测试代码
  for (auto it = vstcode.begin(); it != vstcode.end(); it++) {
    logfile.Write(
        "provname=%s,obtid=%s,obtname=%s,lat=%0.2f,lon=%0.2f,height=%0.2f\n",
        it->provname, it->obtid, it->obtname, it->lat, it->lon, it->height);
  }

  return true;
}