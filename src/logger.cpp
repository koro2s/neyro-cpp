#include "logger.h"
#include <iomanip>
#include <chrono>

EmotionLogger::EmotionLogger(const std::string& logFilePath)
    : logFile(logFilePath, std::ios::app)
{
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file: " + logFilePath);
    }
}

EmotionLogger::~EmotionLogger()
{
    if (logFile.is_open()) {
        logFile.close();
    }
}

void EmotionLogger::logEmotion(const std::string& emotion, float confidence)
{
    if (!logFile.is_open()) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);

    logFile << "Emotion: " << emotion << "\n"
            << "Confidence: " << std::fixed << std::setprecision(4) << confidence << "\n"
            << "Processed at: " << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
            << "\n\n";

    logFile.flush();
}