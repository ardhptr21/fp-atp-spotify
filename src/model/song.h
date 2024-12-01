#include <string>
#include "../lib/linkedlist.h"
namespace song
{
  struct Song
  {
    std::string id;
    std::string singer;
    std::string title;
  };

  linkedlist::Node<Song> *newSong()
  {
    return new linkedlist::Node<Song>{};
  }

  void addSongHandle(linkedlist::Node<Song> *node, Song song)
  {
    linkedlist::append<Song>(node, song);
  }
}