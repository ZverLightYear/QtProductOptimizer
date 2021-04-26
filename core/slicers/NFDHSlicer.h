#ifndef PO_NFDHSLICER_H
#define PO_NFDHSLICER_H

#include "ISlicer.h"
#include "Level.h"
#include "../sorters/IMaterialSorter.h"
#include "../sorters/DecreasingHeightSorter.h"

/**
 * @brief Метод NFDH (Next Fit Decreasing High) упаковки ("нарезки") изделий
 * Алгоритм, что называется, «в лоб».
 *
 * https://habr.com/ru/post/136225/
 */
class NFDHSlicer : public ISlicer {
public:
    /**
     * @brief NFDH метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~NFDHSlicer();

private:
    /// @brief Результат упаковки ("нарезки") изделий
    SliceResult* result = new SliceResult{};

    /**
     * @brief Приватный метод занесения информации об упаковке ("нарезке") изделия в общий результат упаковки ("нарезки")
     * @param {IMaterial*} Упаковываемое изделие
     * @param {Level*} Уровень упаковки
     * @return {bool} Флаг успеха операции
     */
    bool pushProduct(IMaterial*, Level*);

    /**
     * @brief Приватный метод занесения информации об уровне упаковки ("нарезки") изделия в общий результат упаковки ("нарезки")
     */
    void createNewLevel();
};

#endif //PO_NFDHSLICER_H
