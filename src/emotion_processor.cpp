#include "emotion_processor.h"
#include <iostream>

EmotionProcessor::EmotionProcessor(PlaylistManager& mapper,
                                  EmotionDetector& emotionDetector,
                                  EmotionLogger* logger)
    : playlistManager(mapper),
      emotionDetector(emotionDetector),
      logger(logger)
{}

void EmotionProcessor::processImage(const std::string& imagePath)
{
    try {
        auto result = emotionDetector.detectFromImage(imagePath);
        std::string emotion = result.first;
        float prob = result.second;
        float perc = prob * 100;

        std::cout << "Detected emotion: " << emotion
                  << " (" << perc << " %)" << std::endl;
        std::cout << "Recommended playlist: "
                  << playlistManager.getPlaylist(emotion) << std::endl;

        if (logger != nullptr) {
            logger->logEmotion(emotion, perc);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}