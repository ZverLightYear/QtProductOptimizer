#ifndef PO_FCNRSLICER_H
#define PO_FCNRSLICER_H

#include "SliceResult.h"
#include "ISlicer.h"
#include "Level.h"

/**
 * @brief Метод FCNR (Floor Сeiling No Rotation) упаковки ("нарезки") изделий
 * На базе алгоритма BFDH (BFDHSlicer.h), используемого с некоторыми модификациями.
 *
 * https://habr.com/ru/post/136225/
 *
 * TODO !!! На данный момент не реализован (@STUB) !!!
 */
class FCNRSlicer : public ISlicer {
public:
    /**
     * @brief FCNR метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~FCNRSlicer();
private:
    /**
     * @brief Приватный метод занесения информации об упаковке ("нарезке") изделия в общий результат упаковки ("нарезки")
     * @param {SliceResult&} Ссылка не общий результат нарезки
     * @param {IMaterial*} Упаковываемое изделие
     * @param {Level*} Уровень упаковки
     */
    static void pushProduct(SliceResult&, IMaterial*, Level*);
};

#endif //PO_FCNRSLICER_H
