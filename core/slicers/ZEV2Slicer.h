#ifndef PO_ZEV2SLICER_H
#define PO_ZEV2SLICER_H

#include "SliceResult.h"
#include "ISlicer.h"
#include "Level.h"
#include "../sorters/IMaterialSorter.h"
#include "../sorters/DecreasingHeightSorter.h"

/**
 * @brief Метод ZEV2 (Zver Edition Version 2) упаковки ("нарезки") изделий
 */
class ZEV2Slicer : public ISlicer  {
public:
    /**
     * @brief ZEV2 метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~ZEV2Slicer();
private:
    /// @brief Результат упаковки ("нарезки") изделий
    SliceResult* result = new SliceResult{};

    /**
     * @brief Приватный метод занесения информации об упаковке ("нарезке") изделия в общий результат упаковки ("нарезки")
     * @param {IMaterial*} Упаковываемое изделие
     * @return {bool} Флаг успеха упаковки
     */
    bool pushProduct(IMaterial*);

    /**
     * @brief Приватный метод добавления нового уровня упаковки
     * @param {Level*} Упаковываемое изделие
     */
    void pushNewLevel(Level*);

    /**
     * @brief Приватный метод проверки пересечения изделия с уже упакованными изделиями
     * @param {GoodResult} Упаковываемое изделие (с координатами размещения)
     * @return {bool} Флаг пересечения
     */
    bool isIntersectWithResult(GoodResult);
    /**
     * @brief Приватный метод проверки пересечения двух изделий
     * @param {GoodResult} Упаковываемое изделие 1 (с координатами размещения)
     * @param {GoodResult} Упаковываемое изделие 2 (с координатами размещения)
     * @return {bool} Флаг пересечения
     */
    bool isIntersect(GoodResult, GoodResult);

    /**
     * @brief Приватный метод вычисления смещения точки внутри изделия. Вычисляется расстояние от точки до левой стенки изделия
     * @param {Point} Точка для проверки
     * @param {GoodResult} Упаковываемое изделие (с координатами размещения)
     * @return {float} Смещение точки от левой стенки изделия
     */
    float pointLeftOffsetInMaterial(Point, GoodResult);

    /**
     * @brief Приватный метод сортировки уровней по высоте внутри заготовки
     */
    void sortLevels();

    /**
     * @brief Приватный метод продвижения уровня направо исходя из его пересечения с упакованными изделиями
     * @param {Level*} Уровень для продвижения
     */
    void moveLevelRight(Level*);

    /**
     * @brief Приватный метод продвижения уровня направо с указанным смещением
     * @param {Level*} Уровень для продвижения
     * @param {float} Смещение, на которое передвигается уровень
     */
    void moveLevelRightByOffset(Level*, float);
};

#endif //PO_ZEV2SLICER_H
