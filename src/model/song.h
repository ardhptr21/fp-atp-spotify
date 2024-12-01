#include <iostream>
#include <string>
#include "../lib/linkedlist.h"
#include "../lib/util.h"
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

  void addSongHandle(linkedlist::Node<Song> *node)
  {
    util::ignoreLine();

    Song song;
    song.id = util::generateRandomString(10);
    std::string test;
    std::cout << "Enter singer: ";
    std::getline(std::cin, song.singer);
    std::cout << "Enter title: ";
    std::getline(std::cin, song.title);

    linkedlist::append<Song>(node, song);
    std::cout << "Song added successfully." << std::endl;
  }

  void deleteSongHandle(linkedlist::Node<Song> *node)
  {
    util::ignoreLine();
    int index;
    std::cout << "Enter index : ";
    std::cin >> index;
    linkedlist::removeAt<Song>(node, index);
  }

}