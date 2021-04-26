#ifndef PO_ISLICEMANAGER_H
#define PO_ISLICEMANAGER_H

#include "IMaterial.h"
#include "slicers/ISlicer.h"

/**
 * Интерфейс менеджера упаковки. Осуществляет упаковку ("нарезку") изделий для заготовки
 */
class ISliceManager {
public:
    /**
     * @brief Задать базовый материал (базовую заготовку)
     * @param {IMaterial*} - Экземпляр заготовки
     */
    virtual void SetBlank(IMaterial*) = 0;
    /**
     * @brief Задать базовый материал (базовую заготовку) исходя из размеров
     * @param {float} - Высота материала
     * @param {float} - Ширина материала
     */
    virtual void SetBlank(float, float) = 0;

    /**
     * @brief Задать упаковщика изделий
     * @param {ISlicer*} - Экземпляр упаковщика
     */
    virtual void SetSlicer(ISlicer*) = 0;

    /**
     * @brief Добавить изделие в контейнер
     * @param {IMaterial*} - Экземпляр изделия
     */
    virtual void AddMaterial(IMaterial*) = 0;
    /**
     * @brief Добавить изделие в контейнер исходя из размеров
     * @param {float} - Высота изделия
     * @param {float} - Ширина изделия
     */
    virtual void AddMaterial(float, float) = 0;
    /**
     * @brief Удалить изделие из контейнера
     * @param {int} - Индекс изделия в контейнере
     */
    virtual void RemoveMaterial(int) = 0;
    /**
     * @brief Изменить размеры изделия в контейнере
     * @param {int} - Индекс изделия в контейнере
     * @param {float} - Новая высота изделия
     * @param {float} - Новая ширина изделия
     */
    virtual void EditMaterial(int, float, float) = 0;
    /**
     * @return Количество изделий в контейнере
     */
    virtual int MaterialCount() = 0;

    /**
     * @brief SLASH IT NOW !!!!!!!
     * @return {SliceResult} Результат упаковки ("нарезки") изделий на заготовке
     */
    virtual SliceResult Slice() = 0;
};

#endif //PO_ISLICEMANAGER_H
