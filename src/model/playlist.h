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

    Playlist(std::string id, std::string name) : id(id), name(name) {}

    bool isEmpty() const
    {
      return id.empty() && name.empty();
    }

    std::string getValue(std::string key)
    {
      if (key == "id")
        return id;
      else if (key == "name")
        return name;
      return "";
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
  void serialize(PlaylistNode *&, std::string);
  void deserialize(PlaylistNode *&, std::string);

#define PLAYLIST_FAVORITE_ID "fav"

  PlaylistNode *newPlaylist()
  {
    PlaylistNode *playlists = new PlaylistNode();
    deserialize(playlists, util::pwd("/database/playlists.txt", false));
    return playlists;
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
    PlaylistNode *curr = node;
    util::printBorder('-', width * 2 + 6);
    printf("| %-*s | %-*s |\n", width, "ID", width, "Name");
    util::printBorder('-', width * 2 + 6);

    while (curr != nullptr)
    {
      if (curr->isEmpty())
      {
        curr = curr->next;
        continue;
      }

      printf("| %-*s | %-*s |\n", width, curr->data.id.c_str(), width, curr->data.name.c_str());
      curr = curr->next;
    }
    util::printBorder('-', width * 2 + 6);
  }

  void serialize(PlaylistNode *&node, std::string filename)
  {
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (!file.is_open())
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }

    PlaylistNode *curr = node;
    while (curr != nullptr)
    {
      if (curr->isEmpty())
      {
        continue;
      }
      file << curr->data.id << "," << curr->data.name << std::endl;
      curr = curr->next;
    }
    file.close();
  }

  void deserialize(PlaylistNode *&node, std::string filename)
  {
    std::ifstream file;
    file.open(filename, std::ios::in);

    if (!file.is_open())
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }

    std::string line;
    bool hasFavorite = false;
    while (getline(file, line))
    {
      std::string id, name;
      std::istringstream ss(line);
      getline(ss, id, ',');
      getline(ss, name, ',');
      Playlist playlist;
      playlist.id = id;
      playlist.name = name;
      if (playlist.id == PLAYLIST_FAVORITE_ID)
      {
        hasFavorite = true;
      }
      linkedlist::append<Playlist>(node, playlist);
    }

    if (!hasFavorite)
    {
      Playlist favPlaylist = Playlist(PLAYLIST_FAVORITE_ID, "Favorite <3");
      linkedlist::appendAtFirst<Playlist>(node, favPlaylist);
    }
    file.close();
  }

  void exportPlaylistHandle(PlaylistNode *&node)
  {
    util::ignoreLine();

    std::string filename;

    std::cout << "Enter filename to export: ";
    std::getline(std::cin, filename);

    std::string filepath = util::pwd("/exports/" + filename + "Playlist.txt", false);
    serialize(node, filepath);
    std::cout << "Export Playlist successfully." << std::endl;
  }

  void importPlaylistSongHandle(PlaylistNode *&node)
  {
    util::ignoreLine();

    std::string filepath;

    std::cout << "Enter filepath to import: ";
    std::getline(std::cin, filepath);

    deserialize(node, filepath);
    std::cout << "Import song successfully." << std::endl;
  }
}