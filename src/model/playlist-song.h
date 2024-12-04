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
  };

  // Function prototypes
  using PlaylistSongNode = linkedlist::Node<PlaylistSong>;
  PlaylistSongNode *newPlaylistSong();
  void addPlaylistSongHandle(PlaylistSongNode *&, std::string);
  void deletePlaylistSongHandle(PlaylistSongNode *&);
  void printPlaylistSongList(PlaylistSongNode *&, song::SongNode *, std::string);

  PlaylistSongNode *newPlaylistSong()
  {
    return new PlaylistSongNode();
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
    if (node->isEmpty())
    {
      std::cout << "No songs available." << std::endl;
      return;
    }

    PlaylistSongNode *curr = node;
    util::printBorder('-', width * 3 + 10);
    printf("| %-*s | %-*s | %-*s |\n", width, "ID", width, "Singer", width, "Title");
    util::printBorder('-', width * 3 + 10);

    song::Song song;
    while (curr != nullptr)
    {
      if (curr->data.playlistId != currentPlaylistID)
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
}