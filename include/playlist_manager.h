/**
 * @file playlist_mapper.h
 * @brief Класс для сопоставления эмоций с музыкальными плейлистами
 * @author Дима
 * @date 2025
 * @version 1.0
 */

#pragma once

#include <string>
#include <map>

/**
 * @class PlaylistManager
 * @brief Менеджер для загрузки и управления соответствиями эмоций и плейлистов
 *
 * Класс предоставляет функциональность для:
 * - Загрузки соответствий из файла
 * - Быстрого поиска плейлиста по эмоции
 * - Внутреннего хранения и управления маппингом
 */
class PlaylistManager
{
public:

    /**
     * @brief Загружает соответствия эмоций и плейлистов из файла
     * @param filename Путь к файлу с маппингом
     * @return true если загрузка прошла успешно, false в случае ошибки
     *
     * Формат файла:
     * Каждая строка должна содержать пару "эмоция:название_плейлиста"
     * Пример содержимого файла:
     * @code
     * happy:happy_music_playlist
     * sad:Sad Music Playlist
     * @endcode
     */
    bool loadMappings(const std::string& filename);

    /**
     * @brief Получает плейлист для указанной эмоции
     * @param emotion Название эмоции (регистрозависимое)
     * @return Название плейлиста или "Default Playlist", если эмоция не найдена
     *
     * Пример использования:
     * @code
     * PlaylistManager manager;
     * manager.loadMappings("mappings.txt");
     * std::string playlist = manager.getPlaylist("happy");
     * @endcode
     */
    std::string getPlaylist(const std::string& emotion) const;

private:
    /// Хранилище соответствий эмоций и плейлистов
    std::map<std::string, std::string> emotionToPlaylist;

    /**
     * @brief Выводит все загруженные соответствия в консоль (для отладки)
     *
     * Формат вывода:
     * @code
     * Loaded mappings:
     * - happy: happy_music_playlist
     * - sad:   Sad Music Playlist
     * @endcode
     */
    void printMappings() const;
};