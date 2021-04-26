#ifndef PO_DECREASINGAREASORTER_H
#define PO_DECREASINGAREASORTER_H

#include "IMaterialSorter.h"

/**
 * @brief Класс сортировщика контейнера материалов по невозрастанию площади материала
 */
class DecreasingAreaSorter : public IMaterialSorter {
public:
    /**
     * @brief Конструктор класса
     */
    DecreasingAreaSorter();

    /**
     * @brief Метод сортировки контейнера материалов по невозрастанию площаади материала
     * @param {Container<IMaterial*>*} - Контейнер для сортировки
     */
    void Sort(Container<IMaterial*>* container) override;

    /**
     * @brief Деструктор класса
     */
    ~DecreasingAreaSorter();
};


#endif //PO_DECREASINGAREASORTER_H
