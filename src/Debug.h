#ifndef DEBUG_H
#define DEBUG_H

#include <string>

class Debug {
	public: 
	  static void Info(char* str);
	  static void Info(const char* str);
	  static void Info(std::string str) { Info(str.c_str()); }

	  static void Error(char* str);
	  static void Error(const char* str);
	  static void Error(std::string str) { Info(str.c_str()); }
};

#endif