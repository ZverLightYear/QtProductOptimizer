#include <algorithm>
#include "DecreasingAreaSorter.h"

DecreasingAreaSorter::DecreasingAreaSorter() = default;

void DecreasingAreaSorter::Sort(Container<IMaterial*>* container) {
    std::sort(container->begin(),
              container->end(),
              // задаем правило сортировки lambda-функцией (сортируем по невозрвстанию площади)
              [](IMaterial* a, IMaterial* b) { return a->Area() > b->Area(); }
    );
}

DecreasingAreaSorter::~DecreasingAreaSorter() = default;
