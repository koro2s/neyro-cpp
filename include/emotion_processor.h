/**
 * @file emotion_processor.h
 * @brief Обработчик эмоций и подбор плейлистов
 * @author Дима
 * @date 2025
 * @version 1.0
 */

#pragma once

#include "emotion_detector.h"
#include "playlist_manager.h"
#include "logger.h"
#include <string>

/**
 * @class EmotionProcessor
 * @brief Класс-координатор между детекцией эмоций и подбором плейлистов
 *
 * Связывает функциональность EmotionDetector и PlaylistManager, предоставляя
 * единый интерфейс для обработки изображений и получения соответствующих
 * музыкальных рекомендаций.
 */
class EmotionProcessor
{
public:
    /**
     * @brief Конструктор процессора эмоций
     * @param mapper Менеджер плейлистов (PlaylistManager)
     * @param emotionDetector Детектор эмоций (EmotionDetector)
     * @param logger Логгер (EmotionLogger)
     *
     * @note Оба параметра передаются по ссылке и должны существовать
     * в течение всего времени жизни EmotionProcessor.
     */
    EmotionProcessor(PlaylistManager& mapper, EmotionDetector& emotionDetector, EmotionLogger* logger);

    /**
     * @brief Обрабатывает изображение и выводит результат
     * @param imagePath Путь к файлу изображения
     * @throw std::runtime_error При ошибках обработки изображения
     *
     * Полный процесс обработки:
     * 1. Детекция эмоции на изображении
     * 2. Поиск соответствующего плейлиста
     * 3. Вывод результатов в консоль
     *
     * Пример использования:
     * @code
     * EmotionDetector detector;
     * detector.loadModel("model.onnx");
     * PlaylistManager manager;
     * manager.loadMappings("playlists.txt");
     *
     * EmotionProcessor processor(manager, detector);
     * processor.processImage("person.jpg");
     * @endcode
     */
    void processImage(const std::string& imagePath);

private:
    /// Ссылка на менеджер плейлистов
    PlaylistManager& playlistManager;

    /// Ссылка на детектор эмоций
    EmotionDetector& emotionDetector;

    /// Указатель на логгер
    EmotionLogger* logger;
};