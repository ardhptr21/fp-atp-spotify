#include <iostream>
#include <fstream>
#include <locale>
#include "lib/util.h"

enum State
{
  MAIN = 1,
  SONG,
  PLAYLIST
};

enum MainMenu
{
  MENU_PLAYLIST = 1,
  MENU_SONG,
  EXIT,
};

void banner();
void mainMenu(State &state);

int main()
{
  State state = State::MAIN;

  util::clearScreen();
  banner();

  bool shouldEnd = false;
  while (true)
  {
    switch (state)
    {
    case MAIN:
      mainMenu(state);
      break;
    case SONG:
      shouldEnd = true;
      break;
    case PLAYLIST:
      shouldEnd = true;
      break;
    }

    if (shouldEnd)
      break;
  }
}

void banner()
{
  std::ifstream banner;

  banner.open(util::pwd("/assets/ascii.txt", true));

  if (banner.is_open())
  {

    std::string line;
    while (getline(banner, line))
    {
      std::cout << line << std::endl;
    }

    banner.close();
  }
  else
  {
    std::cout << "Banner not found." << std::endl;
    exit(1);
  }
}
void mainMenu(State &state)
{
  int choice;

  std::cout << "1. Playlist" << std::endl;
  std::cout << "2. Song" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case MENU_SONG:
    std::cout << "TODO: Song Handle" << std::endl;
    state = SONG;
    break;
  case MENU_PLAYLIST:
    std::cout << "TODO: Playlist Handle" << std::endl;
    state = PLAYLIST;
    break;
  case EXIT:
    exit(0);
  }
}