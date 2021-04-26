#ifndef PO_LEVEL_H
#define PO_LEVEL_H

/**
 * @brief Структура уровня заполнения маленькими блоками базового блока
 */
struct Level {
    /// @brief расположение уровня
    Point coord;
    
    /// @brief Высота уровня
    float Height;
    
    /// @brief Ширина уровня
    float Width;
};

#endif // PO_LEVEL_H
