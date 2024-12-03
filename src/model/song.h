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

  // Function prototypes
  using SongNode = linkedlist::Node<Song>;
  SongNode *newSong();
  void addSongHandle(SongNode *&);
  void deleteSongHandle(SongNode *&);
  void printSongList(SongNode *&);
  Song searchSong(SongNode *, std::string id);

  SongNode *newSong()
  {
    return new SongNode();
  }

  void addSongHandle(SongNode *&node)
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

  void deleteSongHandle(SongNode *&node)
  {
    util::ignoreLine();
    std::string id;
    std::cout << "Enter ID : ";
    std::cin >> id;
    linkedlist::removeByID<Song>(node, id);
  }

  Song searchSong(SongNode *node, std::string id)
  {
    linkedlist::Node<Song> *curr = node;
    while (curr != nullptr)
    {
      if (curr->data.id == id)
      {
        return curr->data;
      }
      curr = curr->next;
    }
    return Song();
  }

  void printSongList(SongNode *&node)
  {
    if (node->isEmpty())
    {
      std::cout << "No songs available." << std::endl;
      return;
    }

    SongNode *curr = node;
    util::printBorder('-', width * 3 + 10);
    printf("| %-*s | %-*s | %-*s |\n", width, "ID", width, "Singer", width, "Title");
    util::printBorder('-', width * 3 + 10);

    while (curr != nullptr)
    {
      printf("| %-*s | %-*s | %-*s |\n", width, curr->data.id.c_str(), width, curr->data.singer.c_str(), width, curr->data.title.c_str());
      curr = curr->next;
    }
    util::printBorder('-', width * 3 + 10);
  }
}