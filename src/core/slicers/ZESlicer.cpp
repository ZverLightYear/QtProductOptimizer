#include <algorithm>
#include "ZESlicer.h"

/*
 * Zver Edition
 * 
 * Суть алгоритма в упаковке изделий на уровни (собственно, как и все остальное).
 * При упаковке очередного изделия передвигаем текущий уровень вперед .
 * В случае необходимости создаем новый уровень на "крыше" только что упакованного изделия. 
 * Необходимость определяется неравенством высоты изделия и текущего уровня, 
 * так как в противном случае получится, что мы добавляем уровень на "этаж", где есть уровень пошире.
 * 
 */
SliceResult ZESlicer::Slice(IMaterial* blank, Container<IMaterial*>* productContainer) {
    result->blank = blank;

    // создаем начальный уровень, если необходимо
    if (result->levels.size() == 0)
        result->levels.push(new Level{ Point{0,0}, result->blank->getHeight(), result->blank->getWidth() });

    // сортируем перед началом упаковки по невозрастанию высоты
    IMaterialSorter *sorter = new DecreasingHeightSorter();
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

bool ZESlicer::pushProduct(IMaterial *product) {
    // подбираем уровень (начиная с самого нижнего) для упаковки изделия
    for (auto i = 0; i < result->levels.size(); i++) {
        auto level = result->levels.at(i);

        if ((product->getWidth() > level->Width) || (product->getHeight() > level->Height))
            // не пролезли по габаритам
            continue;

        // по габаритам пролезли
        // вносим изделие в список успешных
        result->good.push(GoodResult{ level->coord, product });

        // если изделие целиком перекрывает уровень по высоте, то новый уровень создавать не нужно
        if (product->getHeight() < level->Height) {
            // если же нет, то ...
            // вычисляем параметры для нового уровня
            // новый уровень кладется на "крышу" только что добавленного изделия
            auto newLevelY = level->coord.Y + product->getHeight();
            auto newLevelX = level->coord.X;
            auto newLevelHeight = level->Height - product->getHeight();
            auto newLevelWidth = level->Width;
            
            // создаем уровень
            auto newLevel = new Level{ Point{ newLevelX, newLevelY },
                                newLevelHeight,
                                newLevelWidth };

            // вставляем уровень после того уровня, с которым работали
            // это обеспечит последовательность (отсортированность) уровней по координате Y внутри списка
            result->levels.insert(result->levels.begin() + i + 1, newLevel);
        }

        // модифицируем текущий уровень
        // двигаем его ввправо
        level->coord.X += product->getWidth();
        // урезаем по ширине
        level->Width -= product->getWidth();
        // задаем новую высоту уровня
        level->Height = product->getHeight();

        // результат упаковки - успех
        return true;
    }
    // результат упаковки - неудача
    return false;
}

ZESlicer::~ZESlicer() = default;


