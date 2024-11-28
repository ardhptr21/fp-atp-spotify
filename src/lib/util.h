#include <string>
#include <chrono>

namespace util
{
  std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

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
}
