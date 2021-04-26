#ifndef PO_IMATERIALSORTER_H
#define PO_IMATERIALSORTER_H

#include "../Container.h"
#include "../IMaterial.h"

/**
 * @brief Сортировщик контейнера материалов
 */
class IMaterialSorter {
public:
    /**
     * @brief Метод сортировки контейнера материалов
     * @param {Container<IMaterial*>*} Контейнер для сортировки
     */
    virtual void Sort(Container<IMaterial*>*) = 0;
};

#endif //PO_IMATERIALSORTER_H
