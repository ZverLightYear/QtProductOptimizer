#include "BFDHSlicer.h"

/*
 * Best Fit Decreasing High
 *
 * Модификация алгоритма FFDH (FFDHSlicer.h).
 * Суть ее в том, что из уровней, подходящих для упаковки очередного прямоугольника, выбирается не первый, а лучший.
 * Лучший уровень — это такой, на котором останется минимум места после упаковки текущего прямоугольника.
 * Проще говоря, выбирается минимальное подходящее пространство, что способствует лучшему заполнению уровней.
 *
 * https://habr.com/ru/post/136225/
 */
SliceResult BFDHSlicer::Slice(IMaterial* blank, Container<IMaterial*>* productContainer) {
    SliceResult* result = new SliceResult{};
    result->blank = blank;

    /// ToDo

    return *result;
}

void BFDHSlicer::pushProduct(SliceResult &result, IMaterial *product, Level *level) {
    result.good.push(GoodResult {level->coord, product});
    level->coord.X += product->getWidth();
}

BFDHSlicer::~BFDHSlicer()
