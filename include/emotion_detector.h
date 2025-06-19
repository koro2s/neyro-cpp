/**
 * @file emotion_detector.h
 * @brief Детектор эмоций на изображениях лиц с использованием нейронных сетей
 * @author Зянг
 * @date 2025
 * @version 1.0
 */

#pragma once

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>


/**
 * @class EmotionDetector
 * @brief Класс для определения эмоций по изображению лица
 *
 * Использует предобученную модель нейронной сети (FER+) для классификации эмоций.
 * Поддерживает стандартный набор из 7 базовых эмоций.
 */
class EmotionDetector
{
public:

    /**
     * @brief Загружает модель нейронной сети из файла
     * @param modelFileName Путь к файлу модели (.pb или .onnx)
     *
     * Пример:
     * @code
     * detector.loadModel("emotion_ferplus.onnx");
     * @endcode
     */
    void loadModel(const std::string& modelFileName);

    /**
     * @brief Определяет эмоцию на изображении
     * @param imagePath Путь к файлу изображения
     * @return Пара: название эмоции и вероятность (0-1)
     * @throw std::runtime_error Если изображение не может быть загружено
     *
     * Поддерживаемые форматы изображений: JPEG, PNG, BMP.
     * Возвращаемые эмоции: "Neutral", "Happiness", "Surprise", "Sadness", "Anger", "Disgust", "Fear", "Contempt"
     *
     * Пример:
     * @code
     * auto result = detector.detectFromImage("face.jpg");
     * std::cout << "Emotion: " << result.first << ", confidence: " << result.second;
     * @endcode
     */
    std::pair<std::string, float> detectFromImage(const std::string& imagePath);

private:
    /// Метки эмоций (соответствуют выходам модели FER+)
    static const std::vector<std::string> emotionLabels;

    /// Объект нейронной сети OpenCV
    cv::dnn::Net net;

    /**
     * @brief Предобработка изображения перед подачей в нейросеть
     * @param image Исходное изображение
     * @return Нормализованный тензор для нейросети
     *
     * Выполняет:
     * - Изменение размера до 64x64 пикселей
     * - Нормализацию значений пикселей
     * - Преобразование в формат float32
     */
    static cv::Mat preprocessImage(const cv::Mat& image);
};