#include <iostream>
#include <string>
#include "../lib/linkedlist.h"
#include "../lib/util.h"

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
}