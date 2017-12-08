#include <iostream>
#include <functional>
#include <chrono>
#include <ctime>
#include <ratio>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;



string DatetimeToString(time_t time)
  {
      tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
      int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
      year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
      month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
      day = tm_->tm_mday;                        // 临时变量，日。
      hour = tm_->tm_hour;                       // 临时变量，时。
      minute = tm_->tm_min;                      // 临时变量，分。
     second = tm_->tm_sec;                      // 临时变量，秒。
     char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
     sprintf(yearStr, "%d", year);              // 年。
     sprintf(monthStr, "%d", month);            // 月。
     sprintf(dayStr, "%d", day);                // 日。
     sprintf(hourStr, "%d", hour);              // 时。
     sprintf(minuteStr, "%d", minute);          // 分。
     if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
     {
         minuteStr[2] = '\0';
         minuteStr[1] = minuteStr[0];
         minuteStr[0] = '0';
    }
     sprintf(secondStr, "%d", second);          // 秒。
     if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
     {
         secondStr[2] = '\0';
         secondStr[1] = secondStr[0];
         secondStr[0] = '0';
     }
     char s[20];                                // 定义总日期时间char*变量。
     sprintf(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
     string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
     return str;                                // 返回转换日期时间后的string变量。
 }


int main()
{
	 high_resolution_clock::time_point now = high_resolution_clock::now();


	  //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	  std::string str1 = DatetimeToString(now_c);


	  //time_t t = time(0);
	  char ch[64];
	  strftime(ch, sizeof(ch), "%Y%m%d%H%M%S", localtime(&now_c)); //年-月-日 时-分-秒

	  std::cout<<str1<<std::endl;
	  
      auto key1 = hash<string>{}(str1);
      std::stringstream ss1;
      ss1  << key1;
      std::string OrderId1 = ss1.str();
      std::string cusip = "912828F62";
      

      std::cout<<OrderId1<<std::endl;
      std::string buyparentOrderId =cusip + OrderId1 +"00";

      std::cout<<buyparentOrderId<<std::endl;



	high_resolution_clock::time_point now2 = high_resolution_clock::now();


	  //std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	  std::time_t now_c2 = std::chrono::system_clock::to_time_t(now2);
	  std::string str2 = DatetimeToString(now_c2);

	  std::cout<<str2<<std::endl;
	  
      auto key2 = hash<string>{}(str2);
      std::stringstream ss2;
      ss2  << key2;
      std::string OrderId2 = ss2.str();
      std::string cusip2 = "912828F62";
      

      std::cout<<OrderId2<<std::endl;
      std::string buyparentOrderId2 =cusip2 + OrderId2+ "01";

      std::cout<<buyparentOrderId2<<std::endl;


/*
      std::chrono::system_clock::time_point now2 = std::chrono::system_clock::now();
	  std::time_t now_c2 = std::chrono::system_clock::to_time_t(now2);
	  std::string str2 = DatetimeToString(now_c2);




      auto key2 = hash<string>(str2);
      std::stringstream ss2;
      ss1  << key2;
      std::string OrderId2 = ss2.str();
    
      string sellparentOrderId = "912828F62"+OrderId2;


      std::cout<< buyparentOrderId<<std::endl;
      std::cout<< sellparentOrderId<<std::endl;
      */
      return 0;

}
	