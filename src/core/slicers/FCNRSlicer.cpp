#include "FCNRSlicer.h"

/*
 * Floor Сeiling No Rotation
 *
 * Прямоугольники сортируются по не-возрастанию высоты и применяется алгоритм BFDH с некоторыми модификациями.
 * У каждого уровня есть «пол» (floor) и «потолок» (ceiling).
 * Пока есть возможность, прямоугольники пакуются на «пол» слева направо.
 * Когда место заканчивается, предпринимается попытка упаковать на «потолок» справа налево;
 * если нет места на потолке, то только тогда начинается новый уровень.
 * В лучших традициях BFDH, на каждом шагу просматриваются все уровни — сначала «пол», затем «потолок» — на наличие наиболее подходящего места.
 * Метод удачно упаковывает по «потолкам» самые мелкие прямоугольники.
 *
 * https://habr.com/ru/post/136225/
 */
SliceResult FCNRSlicer::Slice(IMaterial * blank, Container<IMaterial *> * productContainer) {
    SliceResult* result = new SliceResult{};
    result->blank = blank;

    /// ToDo

    return *result;
}

void FCNRSlicer::pushProduct(SliceResult& result, IMaterial* product, Level* level) {
    result.good.push(GoodResult{ level->coord, product });
    level->coord.X += product->getWidth();
}

FCNRSlicer::~FCNRSlicer() = default;
