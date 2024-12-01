#pragma once

#include <string>
#include <regex>
#include <chrono>
#include <direct.h>

namespace util
{
  std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  // function prototypes
  std::string generateRandomString(int length);
  std::string pwd(std::string extendm, bool relativeSrc);
  bool isWindows();
  void clearScreen();
  void ignoreLine();

  // function definitions
  std::string generateRandomString(int length)
  {
    auto now = std::chrono::high_resolution_clock::now();
    std::srand(now.time_since_epoch().count());
    std::string randomString;

    for (int i = 0; i < length; i++)
    {
      randomString += letters[std::rand() % letters.length()];
    }

    return randomString;
  }

  std::string pwd(std::string extend = "", bool relativeSrc = true)
  {
    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);
    std::string path = std::string(buffer) + (relativeSrc ? "/src" : "") + extend;
    bool is = isWindows();
    return std::regex_replace(path, std::regex(is ? "/" : "\\\\"), is ? "\\" : "/");
  }

  bool isWindows()
  {
#ifdef _WIN32
    return true;
#else
    return false;
#endif
  }

  void clearScreen()
  {
    if (isWindows())
    {
      system("cls");
    }
    else
    {
      system("clear");
    }
  }

  void ignoreLine()
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
