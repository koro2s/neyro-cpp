#include "playlist_manager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

bool PlaylistManager::loadMappings(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t delimiter = line.find(':');
        if (delimiter != std::string::npos) {
            std::string emotion = line.substr(0, delimiter);
            std::string playlist = line.substr(delimiter + 1);
            emotionToPlaylist[emotion] = playlist;
        }
        else {
            return false;
        }
    }

    printMappings();
    return true;
}

void PlaylistManager::printMappings() const
{
    int maxEmotionLength = 0;
    for (const auto& [emotion, playlist] : emotionToPlaylist) {
        if (emotion.length() > maxEmotionLength) {
            maxEmotionLength = emotion.length();
        }
    }

    std::cout << "\nLoaded playlists:\n\n";
    for (const auto& [emotion, playlist] : emotionToPlaylist) {
        std::cout << " - " << std::left << std::setw(maxEmotionLength + 2)
                  << (emotion + ":") << playlist << "\n";
    }
    std::cout << std::endl;
}

std::string PlaylistManager::getPlaylist(const std::string& emotion) const
{
    auto it = emotionToPlaylist.find(emotion);
    if (it != emotionToPlaylist.end()) {
        return it->second;
    }
    return "Default Playlist";
}