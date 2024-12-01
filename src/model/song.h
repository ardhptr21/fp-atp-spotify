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

  void printBorder(char c)
  {
    for (int i = 0; i < width * 3 + 1; i++)
      std::cout << c;
    std::cout << std::endl;
  }

  void printSongList(linkedlist::Node<Song> *node)
  {
    linkedlist::Node<Song> *curr = node;
    printBorder('-');
    printf("| %-*s | %-*s | %-*s | %-*s |\n", 10, "Index", width, "ID", width, "SINGER", 10, "TITLE");
    printBorder('-');
    int i = 0;
    while (curr != nullptr)
    {
      printf("| %-*d | %-*s | %-*s | %-*s |\n", 10, i, width, curr->data.id.c_str(), width, curr->data.singer.c_str(), 10, curr->data.title.c_str());
      curr = curr->next;
      i++;
    }
    printBorder('-');
  }
}