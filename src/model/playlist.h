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

  // Function prototypes
  using PlaylistNode = linkedlist::Node<Playlist>;
  PlaylistNode *newPlaylist();
  void addPlaylistHandle(PlaylistNode *&);
  void deletePlaylistHandle(PlaylistNode *&);
  bool selectPlaylistHandle(PlaylistNode *&, Playlist *);
  Playlist searchPlaylist(PlaylistNode *, std::string);
  void printPlaylistList(PlaylistNode *&);

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
    std::string id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    linkedlist::removeByID<Playlist>(node, id);
  }

  bool selectPlaylistHandle(PlaylistNode *&node, Playlist *selectedPlaylist)
  {
    util::ignoreLine();
    std::string id;
    std::cout << "Enter ID: ";
    std::cin >> id;
    Playlist playlist = searchPlaylist(node, id);

    if (playlist.isEmpty())
      return false;

    *selectedPlaylist = playlist;
    return true;
  }

  Playlist searchPlaylist(PlaylistNode *node, std::string id)
  {
    PlaylistNode *curr = node;
    while (curr != nullptr)
    {
      if (curr->data.id == id)
      {
        return curr->data;
      }
      curr = curr->next;
    }
    return Playlist();
  }

  void printPlaylistList(PlaylistNode *&node)
  {
    if (node->isEmpty())
    {
      std::cout << "No playlists available." << std::endl;
      return;
    }

    PlaylistNode *curr = node;
    util::printBorder('-', width * 2 + 6);
    printf("| %-*s | %-*s |\n", width, "ID", width, "Name");
    util::printBorder('-', width * 2 + 6);

    while (curr != nullptr)
    {
      printf("| %-*s | %-*s |\n", width, curr->data.id.c_str(), width, curr->data.name.c_str());
      curr = curr->next;
    }
    util::printBorder('-', width * 2 + 6);
  }

}