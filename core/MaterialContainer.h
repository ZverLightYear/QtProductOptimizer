#ifndef PO_MATERIALCONTAINER_H
#define PO_MATERIALCONTAINER_H

#include "Container.h"
#include "IMaterial.h"

/**
 * @brief Класс контейнера материалов.
 */
class MaterialContainer : public Container<IMaterial *> {
public:
    /**
     * @brief Базовый конструктор
     */
    MaterialContainer();
    /**
     * @brief Базовый деструктор
     */
    ~MaterialContainer();
};

#endif //PO_MATERIALCONTAINER_H
