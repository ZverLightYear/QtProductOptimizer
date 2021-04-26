#ifndef PO_ZESLICER_H
#define PO_ZESLICER_H

#include "SliceResult.h"
#include "ISlicer.h"
#include "Level.h"
#include "../sorters/IMaterialSorter.h"
#include "../sorters/DecreasingHeightSorter.h"


/**
 * @brief Метод ZE (Zver Edition) упаковки ("нарезки") изделий
 */
class ZESlicer : public ISlicer  {
public:
    /**
     * @brief ZE метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~ZESlicer();
private:
    /// @brief Результат упаковки ("нарезки") изделий
    SliceResult* result = new SliceResult{};

    /**
     * @brief Приватный метод занесения информации об упаковке ("нарезке") изделия в общий результат упаковки ("нарезки")
     * @param {IMaterial*} Упаковываемое изделие
     * @return {bool} Флаг успеха операции
     */
    bool pushProduct(IMaterial*);
};

#endif //PO_ZESLICER_H
