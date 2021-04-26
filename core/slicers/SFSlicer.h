#ifndef PO_SFSLICER_H
#define PO_SFSLICER_H

#include "ISlicer.h"

/**
 * @brief Метод SF (Split Fit) упаковки ("нарезки") изделий
 * Алгоритм, призванный улучшить FFDH (FFDHSlicer.h) по принципу «разделяй и властвуй».
 *
 * https://habr.com/ru/post/136225/
 */
class SFSlicer : public ISlicer {
public:
    /**
     * @brief SF метод упаковки ("нарезки") изделий из базового материала (заготовки)
     * @param {IMaterial*} Базовый материал (заготовка)
     * @param {Container<IMaterial*>*} Контейнер изделий для упаковки в базовый материал ("нарезки")
     * @return {SliceResult} Результат упаковки ("нарезки")
     */
    SliceResult Slice(IMaterial*, Container<IMaterial*>*) override;

    /**
     * @brief Деструктор
     */
    ~SFSlicer();
private:
    /// @brief Результат упаковки ("нарезки") изделий
    SliceResult* result = new SliceResult{};
};

#endif //PO_SFSLICER_H
