#include <iostream>
#include <string>
#include <fstream>
#include "../lib/linkedlist.h"
#include "../lib/util.h"
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

namespace playlistsong
{
  struct PlaylistSong
  {
    std::string id;
    std::string playlistId;
    std::string songId;
    std::string path;

    PlaylistSong() : id(""), playlistId(""), songId(""), path() {}

    PlaylistSong(std::string id, std::string playlistId, std::string songId) : id(id), playlistId(playlistId), songId(songId) {}

    bool isEmpty() const
    {
      return id.empty() && playlistId.empty() && songId.empty();
    }

    std::string getValue(std::string key)
    {
      if (key == "id")
        return id;
      else if (key == "playlistId")
        return playlistId;
      else if (key == "songId")
        return songId;
      return "";
    }
  };

  // Function prototypes
  using PlaylistSongNode = linkedlist::Node<PlaylistSong>;
  PlaylistSongNode *newPlaylistSong();
  void addPlaylistSongHandle(PlaylistSongNode *&, std::string);
  void deletePlaylistSongHandle(PlaylistSongNode *&);
  void printPlaylistSongList(PlaylistSongNode *&, song::SongNode *, std::string);
  void serialize(PlaylistSongNode *&, std::string);
  void deserialize(PlaylistSongNode *&, std::string);
  void playPlaySong(PlaylistSongNode *&, std::string);

  PlaylistSongNode *newPlaylistSong()
  {
    PlaylistSongNode *playlistsongs = new PlaylistSongNode();
    deserialize(playlistsongs, util::pwd("/database/playlistsongs.txt", false));
    return playlistsongs;
  }

  void addPlaylistSongHandle(PlaylistSongNode *&node, std::string currentPlaylistID)
  {
    util::ignoreLine();

    PlaylistSong playlistSong;
    playlistSong.id = util::generateRandomString(10);
    playlistSong.playlistId = currentPlaylistID;
    std::cout << "Enter song ID: ";
    std::getline(std::cin, playlistSong.songId);

    linkedlist::append<PlaylistSong>(node, playlistSong);
    std::cout << "Added new playlist song successfully." << std::endl;
  }

  void deletePlaylistSongHandle(PlaylistSongNode *&node)
  {
    util::ignoreLine();
    std::string id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    linkedlist::removeByID<PlaylistSong>(node, id);
  };

  void printPlaylistSongList(PlaylistSongNode *&node, song::SongNode *songNode, std::string currentPlaylistID)
  {
    PlaylistSongNode *curr = node;
    util::printBorder('-', width * 3 + 10);
    printf("| %-*s | %-*s | %-*s |\n", width, "ID", width, "Singer", width, "Title");
    util::printBorder('-', width * 3 + 10);

    song::Song song;
    while (curr != nullptr)
    {
      if (curr->data.playlistId != currentPlaylistID || curr->isEmpty())
      {
        curr = curr->next;
        continue;
      }
      song = song::searchSong(songNode, curr->data.songId);
      printf("| %-*s | %-*s | %-*s |\n", width, curr->data.id.c_str(), width, song.singer.c_str(), width, song.title.c_str());
      curr = curr->next;
    }
    util::printBorder('-', width * 3 + 10);
  }

  void serialize(PlaylistSongNode *&node, std::string filename)
  {
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (!file.is_open())
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }

    PlaylistSongNode *curr = node;
    while (curr != nullptr)
    {
      file << curr->data.id << "," << curr->data.playlistId << "," << curr->data.songId << std::endl;
      curr = curr->next;
    }
    file.close();
  }

  void deserialize(PlaylistSongNode *&node, std::string filename)
  {
    std::ifstream file;
    file.open(filename, std::ios::in);

    if (!file.is_open())
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }

    std::string line;
    while (getline(file, line))
    {
      std::string id, playlistId, songId;
      std::istringstream ss(line);
      getline(ss, id, ',');
      getline(ss, playlistId, ',');
      getline(ss, songId, ',');
      PlaylistSong playlistSong;
      playlistSong.id = id;
      playlistSong.playlistId = playlistId;
      playlistSong.songId = songId;
      linkedlist::append<PlaylistSong>(node, playlistSong);
    }
    file.close();
  }

  void playPlaylistSongHandle(PlaylistSongNode *playlistSongs, song::SongNode *songs, playlist::Playlist *currentPlaylist)
  {
    util::ignoreLine();
    std::string id;
    std::cout << "Enter ID : ";
    std::cin >> id;

    PlaylistSongNode *curr = playlistSongs;
    while (curr != nullptr)
    {
      if (currentPlaylist->id != curr->data.playlistId)
      {
        curr = curr->next;
        continue;
      }

      song::Song song = searchSong(songs, curr->data.songId);
      if (song.isEmpty())
      {
        std::cout << "Song not found." << std::endl;
        return;
      }

      std::cout << song.path << std::endl;
      if (!util::fileExists(song.path))
      {
        std::cout << "Cannot find the song file." << std::endl;
        return;
      }

      std::cout << "Playing " << song.title << " by " << song.singer << std::endl;
      std::cout << "Press enter to stop playing." << std::endl;
      PlaySound(TEXT(song.path.c_str()), NULL, SND_FILENAME | SND_ASYNC);

      std::cin.ignore();
      std::cin.get();
      PlaySound(NULL, 0, 0);
      return;
    }
    std::cout << "Playlist not found." << std::endl;
  }
}