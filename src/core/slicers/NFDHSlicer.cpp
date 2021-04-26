#include "NFDHSlicer.h"

/*
 * Next Fit Decreasing High
 *
 * Алгоритм, что называется, «в лоб».
 * Прямоугольники сортируются по не-возрастанию высоты (DecreasingHeightSorter).
 * Самый высокий располагается в левом нижнем углу, тем самым инициализируя первый уровень, по высоте равный ему.
 * Остальные прямоугольники располагаются слева направо, пока есть место на текущем уровне.
 * Прямоугольник, который не поместился на уровне, помещается сверху, образуя следующий уровень, и так далее.
 *
 * https://habr.com/ru/post/136225/
 */
SliceResult NFDHSlicer::Slice(IMaterial* blank, Container<IMaterial*>* productContainer) {
    result->blank = blank;

    // создаем начальный уровень, если необходимо
    if (result->levels.size() == 0)
        result->levels.push(new Level{ Point{0,0}, result->blank->getHeight(), result->blank->getWidth() });
    // в качестве текущего уровня берем последний
    auto currentLevel = result->levels.back();

    // сортируем перед началом упаковки по невозрастанию высоты
    IMaterialSorter *sorter = new DecreasingHeightSorter();
    sorter->Sort(productContainer);

    for (IMaterial* product : *productContainer) {
        // пытаемся упаковать изделие
        if (pushProduct(product, currentLevel))
            continue;
        // упаковать изделие не удалось
        // пытаемся упаковать изделие, перевернув его
        if (pushProduct(product->Rotate(), currentLevel))
            continue;

        // изделие упаковать не получилось
        // создать уровень для изделия, если необходимо
        createNewLevel();

        // в качестве текущего уровня берем только что созданный
        currentLevel = result->levels.back();

        // пытаемся упаковать изделие уже на новый уровень
        if (pushProduct(product, currentLevel))
            continue;
        // упаковать изделие не удалось
        // пытаемся упаковать изделие, перевернув его
        if (pushProduct(product->Rotate(), currentLevel))
            continue;

        // провал
        // вносим изделие в список неудачников
        result->bad.push(product);
    }
    return *result;
}

bool NFDHSlicer::pushProduct(IMaterial *product, Level *level) {
    if ((product->getWidth() <= level->Width) && (product->getHeight() <= level->Height)) {
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

    // не пролезли по габаритам
    return false;
}

void NFDHSlicer::createNewLevel() {
    // создаем новый уровень, опираясь на предыдущий уровень
    auto lastLevel = result->levels.back();
    
    // если текущий уровень пустой, то создавать новый уровень нет смысла
    if (lastLevel->coord.X == 0)
        return;

    // создание нового уровня
    auto newLevelY = lastLevel->coord.Y + lastLevel->Height;
    result->levels.push(new Level{ Point{0, newLevelY}, result->blank->getHeight() - newLevelY, result->blank->getWidth() });
}

NFDHSlicer::~NFDHSlicer() = default;


