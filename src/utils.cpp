#include "utils.h"
#include <sys/stat.h>
#include <filesystem>

cv::Mat softmax(const cv::Mat& logits)
{
    cv::Mat maxVals;
    cv::reduce(logits, maxVals, 1, cv::REDUCE_MAX, -1);

    cv::Mat stabilized = logits - cv::repeat(maxVals, 1, logits.cols);

    cv::Mat exp_scores;
    cv::exp(stabilized, exp_scores);

    cv::Mat sum_exp;
    cv::reduce(exp_scores, sum_exp, 1, cv::REDUCE_SUM, -1);

    return exp_scores / cv::repeat(sum_exp, 1, logits.cols);
}

bool fileExists(const std::string& path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

void showHelp()
{
    std::cout << "Emotion Player\n"
              << "Использование:\n"
              << "  -h, --help          Показывает это сообщение\n"
              << "  -m <model_file>     [обязательный параметр] Путь к файлу с моделью\n"
              << "  -p <playlists_file> [обязательный параметр] Путь к файлу с плейлистами\n"
              << "  -i <image_file>     Обрабатывает изображение и выводит рекомендованный плейлист\n"
              << "  -d <directory>      Обрабатывает каждое изображение из папки и выводит рекомендованный плейлист для каждой\n"
              << "  -q                  Бесконечный режим работы\n"
              << "  -l <logger_file>    Дополнительная запись результатов в лог-файл\n"
              << "Примеры:\n"
              << "  emotion_player -m model.onnx -p playlists.txt -i image.png\n"
              << "  emotion_player -m model.onnx -p playlists.txt -d directory\n"
              << "  emotion_player -m model.onnx -p playlists.txt -l log.txt -q\n";
}

ProgramOptions parseArguments(int argc, char* argv[])
{
    ProgramOptions options;
    std::unordered_map<std::string, bool> requiredParams = {
        {"-m", false}, {"-p", false}
    };

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            options.helpRequested = true;
            return options;
        }
        else if (arg == "-m") {
            if (i + 1 >= argc) throw std::runtime_error("Не указан файл модели после -m");
            options.modelFile = argv[++i];
            requiredParams["-m"] = true;
        }
        else if (arg == "-p") {
            if (i + 1 >= argc) throw std::runtime_error("Не указан файл плейлистов после -p");
            options.playlistsFile = argv[++i];
            requiredParams["-p"] = true;
        }
        else if (arg == "-i") {
            if (i + 1 >= argc) throw std::runtime_error("Не указан файл изображения после -i");
            options.imageFile = argv[++i];
        }
        else if (arg == "-d") {
            if (i + 1 >= argc) throw std::runtime_error("Не указана директория после -d");
            options.directory = argv[++i];
        }
        else if (arg == "-q") {
            options.infiniteMode = true;
        }
        else if (arg == "-l") {
            if (i + 1 >= argc) throw std::runtime_error("Не указан лог-файл после -l");
            options.loggerFile = argv[++i];
        }
        else {
            throw std::runtime_error("Неизвестный параметр: " + arg);
        }
    }

    for (const auto& [param, provided] : requiredParams) {
        if (!provided) {
            throw std::runtime_error("Обязательный параметр " + param + " не указан");
        }
    }

    int count = 0;
    if (!options.imageFile.empty()) ++count;
    if (!options.directory.empty()) ++count;
    if (options.infiniteMode) ++count;

    if (count == 0) {
        throw std::runtime_error("Нужно выбрать 1 режим работы: -i -d -q");
    }

    if (count > 1) {
        throw std::runtime_error("Нужно выбрать ровно 1 режим работы: -i -d -q");
    }

    return options;
}

std::vector<std::string> getFilenamesInDirectory(const std::string& directoryPath)
{
    std::vector<std::string> files;

    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }

    return files;
}