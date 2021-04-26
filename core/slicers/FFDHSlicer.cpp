#include "FFDHSlicer.h"

/*
 * First Fit Decreasing High
 *
 * Похожий на алгоритм NFDH (NFDHSlicer), но с той разницей, что для каждого следующего прямоугольника
 * ищется место не только на последнем уровне, а начиная с самого нижнего.
 *
 * https://habr.com/ru/post/136225/
 */
SliceResult FFDHSlicer::Slice(IMaterial* blank, Container<IMaterial*>* productContainer) {
    result->blank = blank;

    // создаем начальный уровень, если необходимо
    if (result->levels.size() == 0)
        result->levels.push(new Level{ Point{0,0}, result->blank->getHeight(), result->blank->getWidth() });

    // сортируем перед началом упаковки по невозрастанию высоты
    IMaterialSorter *sorter = new DecreasingHeightSorter();
    sorter->Sort(productContainer);

    for (IMaterial* product : *productContainer) {
        // пытаемся упаковать изделие
        if (pushProduct(product))
            continue;
        // упаковать изделие не удалось
        // пытаемся упаковать изделие, перевернув его
        if (pushProduct(product->Rotate()))
            continue;

        // изделие упаковать не получилось
        // создать уровень для изделия, если необходимо
        createNewLevel();
        // пытаемся упаковать изделие уже на новый уровень
        if (pushProduct(product))
            continue;
        // упаковать изделие не удалось
        // пытаемся упаковать изделие, перевернув его
        if (pushProduct(product->Rotate()))
            continue;

        // провал
        // вносим изделие в список неудачников
        result->bad.push(product);

    }

    return *result;
}

bool FFDHSlicer::pushProduct(IMaterial* product)
{
    for (Level* level : result->levels) {
        if ((product->getWidth() > level->Width) || (product->getHeight() > level->Height))
            // не пролезли по габаритам
            continue;
        
        // пролезли по габаритам
        // добавляем изделие в список упакованных
        result->good.push(GoodResult{ level->coord, product });
        if (level->coord.X == 0)
            // если это первое изделие на уровне, то задаем изделию высоту
            level->Height = product->getHeight();

        // передвигаем текущий уровень
        level->coord.X += product->getWidth();
        level->Width -= product->getWidth();
        
        return true;
    }
    return false;
}

void FFDHSlicer::createNewLevel() {
    // создаем новый уровень, опираясь на предыдущий уровень
    auto lastLevel = result->levels.back();
    // создание нового уровня
    auto newLevelY = lastLevel->coord.Y + lastLevel->Height;
    result->levels.push(new Level{ Point{0, newLevelY}, result->blank->getHeight() - newLevelY, result->blank->getWidth() });
}

FFDHSlicer::~FFDHSlicer() = default;

