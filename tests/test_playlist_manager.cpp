#include <gtest/gtest.h>
#include "playlist_manager.h"
#include <filesystem>
#include <fstream>

class PlaylistManagerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        std::ofstream testFile("test_playlists.txt");
        testFile << "happy:Pop Hits\n";
        testFile << "sad:Chill Vibes\n";
        testFile.close();
    }

    void TearDown() override
    {
        std::remove("test_playlists.txt");
    }
};

TEST_F(PlaylistManagerTest, LoadValidMappings)
{
    PlaylistManager mapper;
    EXPECT_TRUE(mapper.loadMappings("test_playlists.txt"));
}

TEST_F(PlaylistManagerTest, GetExistingPlaylist)
{
    PlaylistManager mapper;
    mapper.loadMappings("test_playlists.txt");
    EXPECT_EQ(mapper.getPlaylist("happy"), "Pop Hits");
}

TEST_F(PlaylistManagerTest, GetNonExistingPlaylist)
{
    PlaylistManager mapper;
    mapper.loadMappings("test_playlists.txt");
    EXPECT_EQ(mapper.getPlaylist("unknown"), "Default Playlist");
}

TEST(PlaylistManagerNegativeTest, LoadNonExistingFile)
{
    PlaylistManager mapper;
    EXPECT_FALSE(mapper.loadMappings("nonexistent_file.txt"));
}