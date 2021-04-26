#ifndef PO_SLICERESULT_H
#define PO_SLICERESULT_H

#include "../Point.h"
#include "../IMaterial.h"
#include "../Container.h"
#include "Level.h"

/**
 * @brief Структура для сохранения успешно упакованных (успешно "нарезанных") изделий
 */
struct GoodResult {
    /// @brief Точка на плоскости базового материала заготовки, где располазается изделие
    Point point;
    /// @brief Изделие
    IMaterial* material;
};

/**
 * @brief Структура для сохранения результатов упаковки ("нарезки") изделий
 */
struct SliceResult {
    /// @brief Базовый материал (заготовка), для которой осуществлялась нарезка
    IMaterial* blank = nullptr;
    /// @brief Успешно упакованные ("нарезанные") изделия
    Container<GoodResult> good;
    /// @brief Изделия, которые не удалось упаковать ("нарезать") для заготовки
    Container<IMaterial*> bad;

    /// @brief Хранит информацию об уровнях упаковки изделий
    Container<Level*> levels;
    
    /**
     * @return Эффективность упаковки, вычисляемая исходя из площади упакованных изделий относительно общей площади изделий
     */
    float Efficiency() {
        // считаем площадь упакованных изделий
        float slicedArea = 0;
        for (GoodResult goodResult : good)
            slicedArea += goodResult.material->Area();

        // считаем площадь НЕ упакованных изделий
        float badArea = 0;
        for (IMaterial* badProduct : bad)
            badArea += badProduct->Area();

        // результат
        return slicedArea / (badArea + slicedArea);
    }
};

#endif //PO_SLICERESULT_H
