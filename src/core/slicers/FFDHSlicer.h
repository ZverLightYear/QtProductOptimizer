#ifndef PO_FFDHSLICER_H
#define PO_FFDHSLICER_H

#include "ISlicer.h"
#include "../sorters/IMaterialSorter.h"
#include "../sorters/DecreasingHeightSorter.h"
#include "Level.h"

/**
 * @brief Метод FFDH (First Fit Decreasing High) упаковки ("нарезки") изделий
 * Усовершенствование алгоритма NFDH (NFDHSlicer.h).
 *
 * https://habr.com/ru/post/136225/
 */
class FFDHSlicer : public ISlicer {
public:
    /**
     * @brief FFDH метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~FFDHSlicer();
private:
    /// @brief Результат упаковки ("нарезки") изделий
    SliceResult* result = new SliceResult{};

    /**
     * @brief Приватный метод занесения информации об упаковке ("нарезке") изделия в общий результат упаковки ("нарезки")
     * @param {IMaterial*} Упаковываемое изделие
     * @param {Level*} Уровень упаковки
     * @return {bool} Флаг успеха операции
     */
    bool pushProduct(IMaterial*);
    /**
     * @brief Приватный метод создания уровня упаковки ("нарезки") изделий в общий результат упаковки ("нарезки")
     */
    void createNewLevel();
};

#endif //PO_FFDHSLICER_H
