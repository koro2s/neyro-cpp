#include "emotion_processor.h"
#include "playlist_manager.h"
#include "emotion_detector.h"
#include "logger.h"
#include "utils.h"
#include <iostream>
#include <string>

void process(EmotionProcessor& processor, const ProgramOptions& options)
{
    if (options.infiniteMode) {
        while (true) {
            std::string imagePath;
            std::cout << "\nEnter image path (or 'q' to quit): ";
            std::getline(std::cin, imagePath);

            if (imagePath == "q" || imagePath == "quit") {
                break;
            }
            processor.processImage(imagePath);
        }
    }
    else if (!options.imageFile.empty()) {
        processor.processImage(options.imageFile);
    }
    else if (!options.directory.empty()) {
        const auto files = getFilenamesInDirectory(options.directory);
        for (const std::string& fileName : files) {
            std::cout << "Попытка обработки " << options.directory + "/" + fileName << "\n";
            processor.processImage(options.directory + "/" + fileName);
            std::cout << "\n";
        }
    }
}

int main(int argc, char* argv[])
{
    try {
        ProgramOptions options = parseArguments(argc, argv);

        if (options.helpRequested) {
            showHelp();
            return 0;
        }

        std::cout << "Запуск Emotion Player с параметрами:\n";
        std::cout << "Модель: " << options.modelFile << "\n";
        std::cout << "Плейлисты: " << options.playlistsFile << "\n";

        if (!options.imageFile.empty()) {
            std::cout << "Обработка изображения: " << options.imageFile << "\n";
        }
        else if (!options.directory.empty()) {
            std::cout << "Обработка директории: " << options.directory << "\n";
        }

        if (options.infiniteMode) {
            std::cout << "Бесконечный режим работы\n";
        }

        if (!options.loggerFile.empty()) {
            std::cout << "Логирование в файл: " << options.loggerFile << "\n";
        }

        PlaylistManager playlistManager;
        if (!playlistManager.loadMappings(options.playlistsFile)) {
            throw std::runtime_error("Не удалось загрузить плейлисты");
        }

        EmotionDetector emotionDetector;
        emotionDetector.loadModel(options.modelFile);

        if (options.loggerFile.empty()) {
            EmotionProcessor processor(playlistManager, emotionDetector, nullptr);
            process(processor, options);
        }
        else {
            EmotionLogger logger(options.loggerFile);
            EmotionProcessor processor(playlistManager, emotionDetector, &logger);
            process(processor, options);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n\n";
        showHelp();
        return 1;
    }

    std::cout << "Program finished.\n";
    return 0;
}