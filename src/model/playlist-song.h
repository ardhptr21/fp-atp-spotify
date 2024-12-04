#include <string>
#include "../lib/linkedlist.h"
#include "../lib/util.h"

namespace playlistsong
{
  struct PlaylistSong
  {
    std::string id;
    std::string playlistId;
    std::string songId;

    PlaylistSong() : id(""), playlistId(""), songId("") {}

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

  PlaylistSongNode *newPlaylistSong()
  {
    PlaylistSongNode *playlistsongs = new PlaylistSongNode();
    serialize(playlistsongs, util::pwd("/database/playlistsongs.txt", false));
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
}