#include <iostream>
#include <fstream>
#include <locale>
#include "lib/util.h"
#include "lib/linkedlist.h"
#include "model/song.h"
#include "model/playlist.h"
#include "model/playlist-song.h"

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
void mainMenu(State &state);
void songMenu(State &state, song::SongNode *&songs);
void playlistMenu(State &state, playlist::PlaylistNode *&playlists, playlist::Playlist *selectedPlaylist);
void playlistDetailMenu(State &state, playlist::Playlist *selectedPlaylist);

int main()
{

  util::clearScreen();
  banner();

  State state = State::MAIN;

  song::SongNode *songs = song::newSong();
  playlist::PlaylistNode *playlists = playlist::newPlaylist();

  playlist::Playlist *selectedPlaylist = new playlist::Playlist();

  bool shouldEnd = false;
  while (true)
  {
    switch (state)
    {
    case MAIN:
      mainMenu(state);
      break;
    case SONG:
      songMenu(state, songs);
      break;
    case PLAYLIST:
      playlistMenu(state, playlists, selectedPlaylist);
      break;
    case DETAIL_PLAYLIST:
      playlistDetailMenu(state, selectedPlaylist);
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

void songMenu(State &state, song::SongNode *&songs)
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
    song::printSongList(songs);
    break;
  case SONG_ADD:
    song::addSongHandle(songs);
    break;
  case SONG_DELETE:
    song::deleteSongHandle(songs);
    break;
  case SONG_BACK:
    state = MAIN;
    break;
  }
}

void playlistMenu(State &state, playlist::PlaylistNode *&playlists, playlist::Playlist *selectedPlaylist)
{
  int choice;

  std::cout << "1. List Playlist" << std::endl;
  std::cout << "2. Add Playlist" << std::endl;
  std::cout << "3. Select Playlist" << std::endl;
  std::cout << "4. Delete Playlist" << std::endl;
  std::cout << "0. Back" << std::endl;
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
    state = MAIN;
    break;
  }
}

void playlistDetailMenu(State &state, playlist::Playlist *selectedPlaylist)
{
  int choice;

  std::cout << "Playlist Name: " << selectedPlaylist->name << std::endl;
  std::cout << "1. List Song" << std::endl;
  std::cout << "2. Add Song" << std::endl;
  std::cout << "3. Delete Song" << std::endl;
  std::cout << "0. Back" << std::endl;
  std::cout << "Enter your choice: ";
  std::cin >> choice;

  switch (choice)
  {
  case PLAYLIST_DETAIL_LIST:
    std::cout << "TODO: List song from playlist" << std::endl;
    break;
  case PLAYLIST_DETAIL_ADD:
    std::cout << "TODO: Add song to playlist" << std::endl;
    break;
  case PLAYLIST_DETAIL_DELETE:
    std::cout << "TODO: Delete song from playlist" << std::endl;
    break;
  case PLAYLIST_DETAIL_BACK:
    state = PLAYLIST;
    break;
  }
}