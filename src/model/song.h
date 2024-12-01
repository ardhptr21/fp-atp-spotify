#include <iostream>
#include <string>
#include "../lib/linkedlist.h"
#include "../lib/util.h"

#define width 32
namespace song
{
  struct Song
  {
    std::string id;
    std::string singer;
    std::string title;

    Song() : id(""), singer(""), title("") {}

    bool isEmpty() const
    {
      return id.empty() && singer.empty() && title.empty();
    }
  };

  using SongNode = linkedlist::Node<Song>;

  SongNode *newSong()
  {
    return new SongNode();
  }

  void addSongHandle(linkedlist::Node<Song> *&node)
  {
    util::ignoreLine();

    Song song;
    song.id = util::generateRandomString(10);
    std::cout << "Enter singer: ";
    std::getline(std::cin, song.singer);
    std::cout << "Enter title: ";
    std::getline(std::cin, song.title);

    linkedlist::append<Song>(node, song);
    std::cout << "Song added successfully." << std::endl;
  }

  void deleteSongHandle(linkedlist::Node<Song> *&node)
  {
    util::ignoreLine();
    int index;
    std::cout << "Enter index : ";
    std::cin >> index;
    linkedlist::removeAt<Song>(node, index);
  }

  void printSongList(linkedlist::Node<Song> *&node)
  {
    if (node->isEmpty())
    {
      std::cout << "No songs available." << std::endl;
      return;
    }

    linkedlist::Node<Song> *curr = node;
    util::printBorder('-', width * 3 + 23);
    printf("| %-*s | %-*s | %-*s | %-*s |\n", 10, "Index", width, "ID", width, "Singer", width, "Title");
    util::printBorder('-', width * 3 + 23);
    int i = 0;
    while (curr != nullptr)
    {
      printf("| %-*d | %-*s | %-*s | %-*s |\n", 10, i, width, curr->data.id.c_str(), width, curr->data.singer.c_str(), width, curr->data.singer.c_str());
      curr = curr->next;
      i++;
    }
    util::printBorder('-', width * 3 + 23);
  }
}