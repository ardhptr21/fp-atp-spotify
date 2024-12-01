#include <string>
#include "../lib/linkedlist.h"

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

  linkedlist::Node<PlaylistSong> *newPlaylistSong()
  {
    return new linkedlist::Node<PlaylistSong>{};
  }

  void addPlaylistSongHandle(linkedlist::Node<PlaylistSong> *node, PlaylistSong playlistsong)
  {
    linkedlist::append<PlaylistSong>(node, playlistsong);
  }

  void deletePlaylistSongHandle(linkedlist::Node<PlaylistSong> *node, int index)
  {
    linkedlist::removeAt<PlaylistSong>(node, index);
  }
}