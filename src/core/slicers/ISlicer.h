#ifndef PO_ISLICER_H
#define PO_ISLICER_H

#include "../Container.h"
#include "../IMaterial.h"
#include "SliceResult.h"

/**
 * @brief Интерфейс упаковщика ("нарезателя") изделий из базового материала (заготовки)
 */
class ISlicer {
public:
    /**
     * @brief Метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    virtual SliceResult Slice(IMaterial*, Container<IMaterial*>*) = 0;
};

#endif //PO_ISLICER_H
