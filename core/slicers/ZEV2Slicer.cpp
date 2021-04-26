#include "ZEV2Slicer.h"
#include "../sorters/DecreasingAreaSorter.h"
#include <algorithm>

/*
 * Zver Edition Version 2
 *
 * Улучшение алгоритма ZE, позволяющее укладывать изделия плотнее.
 * Основная идея - отвязаться от высоты уровней при упаковке, так как, по моим наблюдениям, пустоты в цпаковке возникают именно из-за проверок по высоте
 * 
 * При упаковке изделий не будем проверять, что оно по высоте залезает на уровень.
 * При упаковке изделия проверяем, что оно не пересекается с уже упакованными изделиями.
 * При упаковке очередного изделия передвигаем текущий уровень вперед.
 * После упаковки изделия создаем новый уровень - либо на "крыше" только что упакованного изделия, либо у левой стенки заготовки (зависит от высоты уровня). 
 *
 * Таким образом достигнем необходимого количества уровней для наиболее плотной упаковки.
 *
 */
SliceResult ZEV2Slicer::Slice(IMaterial* blank, Container<IMaterial*>* productContainer) {
    result->blank = blank;

    // создаем начальный уровень, если необходимо
    if (result->levels.size() == 0)
        result->levels.push(new Level{ Point{0,0}, result->blank->getHeight(), result->blank->getWidth() });

    // сортируем перед началом упаковки по невозрастанию высоты
    IMaterialSorter* sorter = new DecreasingHeightSorter();

    // сортируем перед началом упаковки по невозрастанию площади
    // IMaterialSorter* sorter = new DecreasingAreaSorter();

    sorter->Sort(productContainer);

    // для каждого уровня пытаемся запаковать по очереди каждое изделие
    for (IMaterial* product : *productContainer) {
        // пытаемся упаковать изделие
        if (pushProduct(product))
            continue;
        // упаковать изделие не удалось
        // пытаемся упаковать изделие, перевернув его
        if (pushProduct(product->Rotate()))
            continue;

        // все-равно изделие упаковать не получилось
        // вносим его в список неудачников
        result->bad.push(product);
    }

    // конец алгоритма
    return *result;
}

bool ZEV2Slicer::pushProduct(IMaterial *product) {
    // подбираем уровень (начиная с самого нижнего) для упаковки изделия
    for (Level* level : result->levels) {
        // проверяем влезает ли изделие в заготовку
        // проверка высоты изделия производится не по высоте уровня, а по верхней границе заготовки
        if ((product->getWidth() > level->Width) || (level->coord.Y + product->getHeight() > result->blank->getHeight()))
            // не пролезли по габаритам
            continue;

        // создаем экземпляр потенциально успешного результата
        auto mayBeGoodResult = GoodResult{ level->coord, product };

        // проверяем, чтобы добавляемое изделие не пересекалось с уже упакованными изделиями
        if (isIntersectWithResult(mayBeGoodResult))
            // с чем-то пересекается - потенциально успешный результат не подошел
            continue;

        // потенциально успешный результат оказался подходящим
        // добавляем его в список результатов
        auto gr = GoodResult{ level->coord, product };
        result->good.push(gr);

        // вычисляем параметры нового уровня
        auto newLevelX = level->coord.X;
        auto newLevelY = level->coord.Y + product->getHeight();
        auto newLevelHeight = level->Height - product->getHeight();
        auto newLevelWidth = level->Width;

        // если высота изделия превысила высоту уровня, 
        // то уровень создаем не на "крыше" изделия, а у левой стенки (X = 0)
        if (level->Height < product->getHeight()) {
            newLevelX = 0.f;
            newLevelWidth = result->blank->getWidth();
        }

        // если изделие целиком "вписалось" на текущий уровень по высоте, то новый уровень создавать не нужно
        if (level->Height != product->getHeight())
            // если же не "вписалось", то уровень создать надо
            pushNewLevel(new Level{ Point{ newLevelX, newLevelY },
                                           newLevelHeight,
                                           newLevelWidth});

        // при упаковке изделия оно могло "лечь" на уже существующие уровни
        // поэтому нужно эти уровни подвинуть вправо
        for (Level* checkedLevel : result->levels)
            // двигаем уровень вправо (offset может быть равен 0)
            moveLevelRightByOffset(checkedLevel, pointLeftOffsetInMaterial(checkedLevel->coord, gr));

        // У текущего уровня меняем только высоту
        // так как вправо мы уже продвинули его в цикле выше
        level->Height = product->getHeight();
        
        // после упаковки изделия мы передвинули текущий уровень
        // текущий уровень мог упереться в одно из изделий, размещенных ранее
        // поэтому нужно его подвинуть вправо до свободного пространства
        moveLevelRight(level);

        // результат упаковки изделия - успех
        return true;
    }
    
    // результат упаковки изделия - провал
    return false;
}

void ZEV2Slicer::pushNewLevel(Level* newLevel) {
    if (newLevel->coord.X == 0)
        // при добавлении нового уровня он может попасть на упакованное изделие (когда X == 0)
        // надо продвинуть уровень
        moveLevelRight(newLevel);

    // добавляем уровень
    result->levels.push(newLevel);

    // необходимо отсортировать уровни по координате Y (по высоте внутри заготовки)
    sortLevels();
}

bool ZEV2Slicer::isIntersectWithResult(GoodResult checkedResult) {
    // ищем пересечение по всем результатам
    for (GoodResult goodResult : result->good) {
        if (isIntersect(goodResult, checkedResult))
            return true;
    }
    return false;
}

bool ZEV2Slicer::isIntersect(GoodResult res1, GoodResult res2) {
    // вычисляем параметры вычисления результата
    float left = std::max(res1.point.X, res2.point.X);
    float top = std::min(res1.point.Y + res1.material->getHeight(), res2.point.Y + res2.material->getHeight());
    float right = std::min(res1.point.X + res1.material->getWidth(), res2.point.X + res2.material->getWidth());
    float bottom = std::max(res1.point.Y, res2.point.Y);

    // возвращаем результат пересечения
    return !(right - left <= 0 || top - bottom <= 0);
}

float ZEV2Slicer::pointLeftOffsetInMaterial(Point point, GoodResult res) {
    // вычисляем параметры вычисления результата
    bool left = res.point.X <= point.X;
    bool right = point.X < res.point.X + res.material->getWidth();
    bool top = point.Y < res.point.Y + res.material->getHeight();
    bool bottom = res.point.Y <= point.Y;

    // возвращаем смещение точки от левой стенки изделия внутри прямоугольника
    if (right && left && top && bottom)
        return res.point.X + res.material->getWidth() - point.X;
    else
        return 0;
}

void ZEV2Slicer::sortLevels() {
    std::sort(result->levels.begin(), 
              result->levels.end(), 
              [](Level* a, Level* b) {return a->coord.Y < b->coord.Y; });
}

void ZEV2Slicer::moveLevelRight(Level* level) {
    // здесь учитывается упорядоченность изделий по времени их добавления, поэтому ошибок не возникнет 
    // т.е. если изделие_1 стоит на уровне раньше, чем изделие_2 на этом же уровне, то в списке успешных изделие_1 располагается раньше, чем изделие_2
    for (GoodResult gr : result->good)
        // двигаем уровень вправо (offset может быть равен 0)
        moveLevelRightByOffset(level, pointLeftOffsetInMaterial(level->coord, gr));
}

void ZEV2Slicer::moveLevelRightByOffset(Level* level, float offset) {
    level->coord.X += offset;
    level->Width -= offset;
}

ZEV2Slicer::~ZEV2Slicer() = default;


