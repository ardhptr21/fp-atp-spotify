#include <iostream>
#include <string>
#include <fstream>
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

    std::string getValue(std::string key)
    {
      if (key == "id")
        return id;
      else if (key == "singer")
        return singer;
      else if (key == "title")
        return title;
      return "";
    }
  };

  // Function prototypes
  using SongNode = linkedlist::Node<Song>;
  SongNode *newSong();
  void addSongHandle(SongNode *&);
  void deleteSongHandle(SongNode *&);
  void printSongList(SongNode *&);
  Song searchSong(SongNode *, std::string);
  void serialize(SongNode *&, std::string);
  void deserialize(SongNode *&, std::string);
  void sortSongHandle(SongNode *);

  SongNode *newSong()
  {
    SongNode *songs = new SongNode();
    deserialize(songs, util::pwd("/database/songs.txt", false));
    return songs;
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
    SongNode *curr = node;
    util::printBorder('-', width * 3 + 10);
    printf("| %-*s | %-*s | %-*s |\n", width, "ID", width, "Singer", width, "Title");
    util::printBorder('-', width * 3 + 10);

    while (curr != nullptr)
    {
      if (curr->isEmpty())
      {
        curr = curr->next;
        continue;
      }
      printf("| %-*s | %-*s | %-*s |\n", width, curr->data.id.c_str(), width, curr->data.singer.c_str(), width, curr->data.title.c_str());
      curr = curr->next;
    }
    util::printBorder('-', width * 3 + 10);
  }

  void serialize(SongNode *&node, std::string filename)
  {
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (!file.is_open())
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }

    SongNode *curr = node;
    while (curr != nullptr)
    {
      file << curr->data.id << "," << curr->data.singer << "," << curr->data.title << std::endl;
      curr = curr->next;
    }
    file.close();
  }

  void deserialize(SongNode *&node, std::string filename)
  {
    std::ifstream file;
    file.open(filename, std::ios::in);

    if (!file.is_open())
    {
      std::cerr << "Error: Unable to open file." << std::endl;
      return;
    }

    std::string line;
    while (getline(file, line))
    {
      std::string id, singer, title;
      std::istringstream ss(line);
      getline(ss, id, ',');
      getline(ss, singer, ',');
      getline(ss, title, ',');
      Song song;
      song.id = id;
      song.singer = singer;
      song.title = title;
      linkedlist::append<Song>(node, song);
    }
    file.close();
  }

  template <typename T>
  void sortedInsert(SongNode *&node, T data)
  {
    std::string sortBy = "title";
    SongNode *newNode = new SongNode();
    newNode->data = data;
  }

  void sortSongHandle(SongNode *node)
  {
    std::string sortBy;
    std::cout << "Sort by (singer/title): ";
    std::cin >> sortBy;
    node = linkedlist::sort<Song>(node, sortBy);

    printSongList(node);
  }

  void exportSongHandle(SongNode *&node)
  {
    util::ignoreLine();

    std::string filename;

    std::cout << "Enter filename to export: ";
    std::getline(std::cin, filename);

    std::string filepath = util::pwd("/exports/" + filename + " Songs.txt", false);
    serialize(node, filepath);
    std::cout << "Export song successfully." << std::endl;
  }

  void importSongHandle(SongNode *&node)
  {
    util::ignoreLine();

    std::string filepath;

    std::cout << "Enter filepath to import: ";
    std::getline(std::cin, filepath);

    deserialize(node, filepath);
    std::cout << "Import song successfully." << std::endl;
  }
}
