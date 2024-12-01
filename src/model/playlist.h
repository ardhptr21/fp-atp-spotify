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
  };

  linkedlist::Node<Playlist> *newPlaylist()
  {
    return new linkedlist::Node<Playlist>{};
  }

  void addPlaylistHandle(linkedlist::Node<Playlist> *node)
  {

    util::ignoreLine();

    Playlist playlist;
    playlist.id = util::generateRandomString(10);
    std::cout << "Enter playlist name: ";
    std::getline(std::cin, playlist.name);

    linkedlist::append<Playlist>(node, playlist);
    std::cout << "Playlist added successfully." << std::endl;
  }

  void deletePlaylistHandle(linkedlist::Node<Playlist> *node, int index)
  {
    linkedlist::removeAt<Playlist>(node, index);
  }
  void printBorder(char c)
  {
    for (int i = 0; i < width * 3 + 1; i++)
      std::cout << c;
    std::cout << std::endl;
  }

  void printPlaylistList(linkedlist::Node<Playlist> *node)
  {
    linkedlist::Node<Playlist> *curr = node;
    printBorder('-');
    printf("| %-*s | %-*s | %-*s |\n", 10, "ID", width, "PLAYLISTNAME");
    printBorder('-');
    int i = 0;
    while (curr != nullptr)
    {
      printf("| %-*d | %-*s | %-*s |\n", 10, i, width, curr->data.id.c_str(), width, curr->data.name.c_str());
      curr = curr->next;
      i++;
    }
    printBorder('-');
  }

}