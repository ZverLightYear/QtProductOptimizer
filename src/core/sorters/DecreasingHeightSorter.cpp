#include "DecreasingHeightSorter.h"
#include <algorithm>

DecreasingHeightSorter::DecreasingHeightSorter() = default;

void DecreasingHeightSorter::Sort(Container<IMaterial*>* container) {
    std::sort(container->begin(),
              container->end(),
              // задаем правило сортировки lambda-функцией (сортируем по невозрвстанию высоты)
              [](IMaterial* a, IMaterial* b) { return a->getHeight() > b->getHeight(); }
            );
}

DecreasingHeightSorter::~DecreasingHeightSorter() = default;

