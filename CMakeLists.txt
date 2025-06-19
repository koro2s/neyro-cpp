cmake_minimum_required(VERSION 3.10)
project(EmotionPlayer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" ON)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_DOCS)
    find_package(Doxygen REQUIRED dot)
    configure_file(docs/Doxyfile.in docs/Doxyfile @ONLY)
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

find_package(OpenCV REQUIRED)
find_package(dlib REQUIRED)

add_library(emotion_detector src/emotion_detector.cpp include/emotion_detector.h
                             src/playlist_manager.cpp include/playlist_manager.h
                             src/emotion_processor.cpp include/emotion_processor.h
                             src/utils.cpp include/utils.h
                             src/logger.cpp include/logger.h)

target_link_libraries(emotion_detector
    PUBLIC
        ${OpenCV_LIBS}
        dlib::dlib
)

target_include_directories(emotion_detector
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(emotion_player src/main.cpp)
target_link_libraries(emotion_player emotion_detector)

target_include_directories(emotion_player
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

install(TARGETS emotion_player DESTINATION bin)
install(FILES include/emotion_detector.h include/playlist_mapper.h DESTINATION include)