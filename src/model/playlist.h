#include <string>

namespace song
{
  struct Playlist
  {
    std::string id;
    std::string name;
  };

  struct PlaylistSong
  {
    std::string id;
    std::string playlistId;
    std::string songId;
  };
}