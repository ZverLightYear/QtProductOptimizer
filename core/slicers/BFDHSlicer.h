#ifndef PO_BFDHSLICER_H
#define PO_BFDHSLICER_H

#include "SliceResult.h"
#include "ISlicer.h"
#include "Level.h"

/**
 * @brief Метод BFDH (Best Fit Decreasing High) упаковки ("нарезки") изделий
 * Модификация алгоритма FFDH (FFDHSlicer.h).
 *
 * https://habr.com/ru/post/136225/
 *
 * TODO !!! На данный момент не реализован (@STUB) !!!
 */
class BFDHSlicer : public ISlicer  {
public:
    /**
     * @brief BFDH метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~BFDHSlicer();
private:
    /**
     * @brief Приватный метод занесения информации об упаковке ("нарезке") изделия в общий результат упаковки ("нарезки")
     * @param {SliceResult&} Ссылка не общий результат нарезки
     * @param {IMaterial*} Упаковываемое изделие
     * @param {Level*} Уровень упаковки
     */
    static void pushProduct(SliceResult&, IMaterial*, Level*);
};

#endif //PO_BFDHSLICER_H
