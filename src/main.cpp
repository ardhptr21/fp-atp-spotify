#include <iostream>
#include <fstream>
#include <locale>
#include "lib/util.h"
#include "lib/linkedlist.h"
#include "model/song.h"
#include "model/playlist.h"
#include "model/playlist-song.h"
#include <csignal>
#include <cstdlib>

enum State
{
  MAIN = 1,
  SONG,
  PLAYLIST,
  DETAIL_PLAYLIST,
};

enum MainMenu
{
  MENU_SONG = 1,
  MENU_PLAYLIST,
  MENU_EXIT,
};

enum SongMenu
{
  SONG_BACK = 0,
  SONG_LIST,
  SONG_LIST_SORT,
  SONG_ADD,
  SONG_DELETE,
};

enum PlaylistMenu
{
  PLAYLIST_BACK = 0,
  PLAYLIST_LIST,
  PLAYLIST_ADD,
  PLAYLIST_SELECT,
  PLAYLIST_DELETE,
};

enum PlaylistDetailMenu
{
  PLAYLIST_DETAIL_BACK = 0,
  PLAYLIST_DETAIL_LIST,
  PLAYLIST_DETAIL_ADD,
  PLAYLIST_DETAIL_DELETE,
};

void banner();
void mainMenu(State &);
void songMenu(State &);
void playlistMenu(State &);
void playlistDetailMenu(State &);
void signalHandler(int signum);

song::SongNode *songs;
playlist::PlaylistNode *playlists;
playlistsong::PlaylistSongNode *playlistsongs;
playlist::Playlist *selectedPlaylist;

int main()
{
  std::signal(SIGINT, signalHandler);

  util::clearScreen();
  banner();

  State state = State::MAIN;

  songs = song::newSong();
  playlists = playlist::newPlaylist();
  playlistsongs = playlistsong::newPlaylistSong();
  selectedPlaylist = new playlist::Playlist();

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
    case DETAIL_PLAYLIST:
      playlistDetailMenu(state);
      break;
    }

    std::cout << std::endl;

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

  util::printBorder('-', width);
  printf("| %-*s |\n", width - 4, "Main Menu");
  util::printBorder('-', width);

  printf("| %-*s |\n", width - 4, "1. Song");
  printf("| %-*s |\n", width - 4, "2. Playlist");
  printf("| %-*s |\n", width - 4, "3. Exit");

  util::printBorder('-', width);

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
    std::cout << "Exiting..." << std::endl;
    song::serialize(songs, util::pwd("/database/songs.txt", false));
    playlist::serialize(playlists, util::pwd("/database/playlists.txt", false));
    playlistsong::serialize(playlistsongs, util::pwd("/database/playlistsongs.txt", false));
    std::cout << "Goodbye!" << std::endl;
    exit(0);
  }
}

void songMenu(State &state)
{
  int choice;

  util::printBorder('-', width);
  printf("| %-*s |\n", width - 4, "Song Menu");
  util::printBorder('-', width);

  printf("| %-*s |\n", width - 4, "1. List Song");
  printf("| %-*s |\n", width - 4, "2. List Sort Song");
  printf("| %-*s |\n", width - 4, "3. Add Song");
  printf("| %-*s |\n", width - 4, "4. Delete Song");
  printf("| %-*s |\n", width - 4, "0. Back");

  util::printBorder('-', width);

  std::cout << "Enter your choice: ";
  std::cin >> choice;
  switch (choice)
  {
  case SONG_LIST:
    song::printSongList(songs);
    break;
  case SONG_LIST_SORT:
    song::sortSongHandle(songs);
    break;
  case SONG_ADD:
    song::addSongHandle(songs);
    break;
  case SONG_DELETE:
    song::deleteSongHandle(songs);
    break;
  case SONG_BACK:
  {
    song::serialize(songs, util::pwd("/database/songs.txt", false));
    state = MAIN;
    break;
  }
  }
}

void playlistMenu(State &state)
{
  int choice;

  util::printBorder('-', width);
  printf("| %-*s |\n", width - 4, "Playlist Menu");
  util::printBorder('-', width);

  printf("| %-*s |\n", width - 4, "1. List Playlist");
  printf("| %-*s |\n", width - 4, "2. Add Playlist");
  printf("| %-*s |\n", width - 4, "3. Select Playlist");
  printf("| %-*s |\n", width - 4, "4. Delete Playlist");
  printf("| %-*s |\n", width - 4, "0. Back");

  util::printBorder('-', width);

  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case PLAYLIST_LIST:
    playlist::printPlaylistList(playlists);
    break;
  case PLAYLIST_ADD:
    playlist::addPlaylistHandle(playlists);
    break;
  case PLAYLIST_DELETE:
    playlist::deletePlaylistHandle(playlists);
    break;
  case PLAYLIST_SELECT:
  {
    bool success = playlist::selectPlaylistHandle(playlists, selectedPlaylist);
    if (!success)
    {
      std::cout << "Playlist not found." << std::endl;
      break;
    }
    state = DETAIL_PLAYLIST;
    break;
  }
  case PLAYLIST_BACK:
  {
    playlist::serialize(playlists, util::pwd("/database/playlists.txt", false));
    state = MAIN;
    break;
  }
  }
}

void playlistDetailMenu(State &state)
{
  int choice;

  util::printBorder('-', width);
  printf("| %-*s |\n", width - 4, ("Playlist Name: " + selectedPlaylist->name).c_str());
  util::printBorder('-', width);

  printf("| %-*s |\n", width - 4, "1. List Song");
  printf("| %-*s |\n", width - 4, "2. Add Song");
  printf("| %-*s |\n", width - 4, "3. Delete Song");
  printf("| %-*s |\n", width - 4, "0. Back");

  util::printBorder('-', width);

  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case PLAYLIST_DETAIL_LIST:
    playlistsong::printPlaylistSongList(playlistsongs, songs, selectedPlaylist->id);
    break;
  case PLAYLIST_DETAIL_ADD:
    playlistsong::addPlaylistSongHandle(playlistsongs, selectedPlaylist->id);
    break;
  case PLAYLIST_DETAIL_DELETE:
    playlistsong::deletePlaylistSongHandle(playlistsongs);
    break;
  case PLAYLIST_DETAIL_BACK:
  {
    playlistsong::serialize(playlistsongs, util::pwd("/database/playlistsongs.txt", false));
    state = PLAYLIST;
    break;
  }
  }
}

void signalHandler(int signum)
{
  std::cout << "\nInterrupt signal (" << signum << ") received. Exiting gracefully...\n";
  song::serialize(songs, util::pwd("/database/songs.txt", false));
  playlist::serialize(playlists, util::pwd("/database/playlists.txt", false));
  playlistsong::serialize(playlistsongs, util::pwd("/database/playlistsongs.txt", false));
  exit(signum);
}