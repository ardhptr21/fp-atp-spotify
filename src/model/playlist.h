#include <string>
#include "../lib/linkedlist.h"

namespace song
{
  struct Playlist
  {
    std::string id;
    std::string name;
  };

  struct PlaylistSong
  {
    std::string id;
    std::string playlistId;
    std::string songId;
  };

  linkedlist::Node<Playlist> *newPlaylist()
  {
    return new linkedlist::Node<Playlist>{};
  }

  linkedlist::Node<PlaylistSong> *newPlaylistSong()
  {
    return new linkedlist::Node<PlaylistSong>{};
  }
  void addPlaylistSongHandle(linkedlist::Node<Song> *node, Song song)
  {
    linkedlist::append<Song>(node, song);
  }

}