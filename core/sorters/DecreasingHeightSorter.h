#ifndef PO_DECREASINGHEIGHTSORTER_H
#define PO_DECREASINGHEIGHTSORTER_H

#include "IMaterialSorter.h"

/**
 * @brief Класс сортировщика контейнера материалов по невозрастанию высоты материала
 */
class DecreasingHeightSorter : public IMaterialSorter {
public:
    /**
     * @brief Конструктор класса
     */
    DecreasingHeightSorter();

    /**
     * @brief Метод сортировки контейнера материалов по невозрастанию высоты материала
     * @param {Container<IMaterial*>*} - Контейнер для сортировки
     */
    void Sort(Container<IMaterial*>*) override;

    /**
     * @brief Деструктор класса
     */
    ~DecreasingHeightSorter();
};

#endif //PO_DECREASINGHEIGHTSORTER_H
