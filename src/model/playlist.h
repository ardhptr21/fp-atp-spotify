#include <iostream>
#include <string>
#include "../lib/linkedlist.h"
#include "../lib/util.h"

#define width 32
namespace playlist
{
  struct Playlist
  {
    std::string id;
    std::string name;

    Playlist() : id(""), name("") {}

    bool isEmpty() const
    {
      return id.empty() && name.empty();
    }
  };

  using PlaylistNode = linkedlist::Node<Playlist>;

  PlaylistNode *newPlaylist()
  {
    return new PlaylistNode();
  }

  void addPlaylistHandle(PlaylistNode *&node)
  {

    util::ignoreLine();

    Playlist playlist;
    playlist.id = util::generateRandomString(10);
    std::cout << "Enter playlist name: ";
    std::getline(std::cin, playlist.name);

    linkedlist::append<Playlist>(node, playlist);
    std::cout << "Playlist added successfully." << std::endl;
  }

  void deletePlaylistHandle(PlaylistNode *&node)
  {
    util::ignoreLine();
    int index;
    std::cout << "Enter index : ";
    std::cin >> index;
    linkedlist::removeAt<Playlist>(node, index);
  }

  Playlist searchPlaylist(PlaylistNode *&node, int index)
  {
    PlaylistNode *curr = node;
    int currIndex = 0;
    while (curr != nullptr)
    {
      if (currIndex == index)
      {
        return node->data;
      }
      currIndex++;
    }
    return Playlist();
  }

  void printPlaylistList(PlaylistNode *&node)
  {
    if (node->isEmpty())
    {
      std::cout << "No songs available." << std::endl;
      return;
    }

    PlaylistNode *curr = node;
    util::printBorder('-', width * 2 + 20);
    printf("| %-*s | %-*s | %-*s |\n", 10, "Index", width, "ID", width, "Name");
    util::printBorder('-', width * 2 + 20);
    int i = 0;
    while (curr != nullptr)
    {
      printf("| %-*d | %-*s | %-*s |\n", 10, i, width, curr->data.id.c_str(), width, curr->data.name.c_str());
      curr = curr->next;
      i++;
    }
    util::printBorder('-', width * 2 + 20);
  }

}