cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)

add_executable(test_playlist_manager test_playlist_manager.cpp)
target_link_libraries(test_playlist_manager
    GTest::GTest
    GTest::Main
    emotion_detector)

add_test(NAME PlayListManagerTests COMMAND test_playlist_manager)


add_executable(test_utils test_utils.cpp)
target_link_libraries(test_utils
    GTest::GTest
    GTest::Main
    emotion_detector)

add_test(NAME UtilsTest COMMAND test_utils)