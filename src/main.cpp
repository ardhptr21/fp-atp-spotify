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
  MENU_EXIT,
};

enum SongMenu
{
  SONG_BACK = 0,
  SONG_LIST,
  SONG_ADD,
  SONG_DELETE,
};

enum PlaylistMenu
{
  PLAYLIST_BACK = 0,
  PLAYLIST_LIST,
  PLAYLIST_ADD,
  PLAYLIST_DELETE,
  PLAYLIST_SELECT,
};

void banner();
void mainMenu(State &state);
void songMenu(State &state);
void playlistMenu(State &state);

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
      songMenu(state);
      break;
    case PLAYLIST:
      playlistMenu(state);
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

  std::cout << "1. Song" << std::endl;
  std::cout << "2. Playlist" << std::endl;
  std::cout << "3. Exit" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case MENU_SONG:
    state = SONG;
    break;
  case MENU_PLAYLIST:
    state = PLAYLIST;
    break;
  case MENU_EXIT:
    exit(0);
  }
}

void songMenu(State &state)
{
  int choice;

  std::cout << "1. List Song" << std::endl;
  std::cout << "2. Add Song" << std::endl;
  std::cout << "3. Delete Song" << std::endl;
  std::cout << "0. Back" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case SONG_LIST:
    std::cout << "TODO: List Song Handle" << std::endl;
    break;
  case SONG_ADD:
    std::cout << "TODO: Add Song Handle" << std::endl;
    break;
  case SONG_DELETE:
    std::cout << "TODO: Delete Song Handle" << std::endl;
    break;
  case SONG_BACK:
    state = MAIN;
    break;
  }
}

void playlistMenu(State &state)
{
  int choice;

  std::cout << "1. List Playlist" << std::endl;
  std::cout << "2. Add Playlist" << std::endl;
  std::cout << "3. Delete Playlist" << std::endl;
  std::cout << "4. Select Playlist" << std::endl;
  std::cout << "0. Back" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case PLAYLIST_LIST:
    std::cout << "TODO: List Playlist Handle" << std::endl;
    break;
  case PLAYLIST_ADD:
    std::cout << "TODO: Add Playlist Handle" << std::endl;
    break;
  case PLAYLIST_DELETE:
    std::cout << "TODO: Delete Playlist Handle" << std::endl;
    break;
  case PLAYLIST_SELECT:
    std::cout << "TODO: Select Playlist Handle" << std::endl;
    break;
  case PLAYLIST_BACK:
    state = MAIN;
    break;
  }
}