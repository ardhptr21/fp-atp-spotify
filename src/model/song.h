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

  void deleteSongHandle(linkedlist::Node<Song> *node, int index)
  {
    linkedlist::removeAt<Song>(node, index);
  }
  
  void addSongHandle(linkedlist::Node<Song> *node, Song song)
  {
    linkedlist::append<Song>(node, song);
  }
}