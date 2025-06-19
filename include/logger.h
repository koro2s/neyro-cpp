/**
 * @file EmotionLogger.h
 * @brief Заголовочный файл класса для логирования эмоций
 * @author Зянг
 * @date 2025
 * @version 1.0
 */

#pragma once

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

/**
 * @class EmotionLogger
 * @brief Класс для записи логов эмоций с временными метками
 *
 * Класс предоставляет функциональность для логирования распознанных эмоций
 * в файл с указанием времени и уровня уверенности.
 */
class EmotionLogger
{
public:

    /*
     * @brief Конструктор, открывающий файл лога
     * @param logFilePath Путь к файлу для записи логов
     * @throw std::runtime_error Если не удалось открыть файл
     *
     * Создает или открывает существующий файл лога для добавления записей.
     * Если файл не может быть открыт, генерируется исключение.
     */
    EmotionLogger(const std::string& logFilePath);

    /**
     * @brief Деструктор, закрывающий файл лога
     *
     * Гарантирует корректное закрытие файла при уничтожении объекта.
     */
    ~EmotionLogger();

    /**
     * @brief Записывает информацию об эмоции в лог
     * @param emotion Строка с названием эмоции (например, "Neutral")
     * @param confidence Уровень уверенности (0.0-1.0)
     */
    void logEmotion(const std::string& emotion, float confidence);

private:
    std::ofstream logFile;
};