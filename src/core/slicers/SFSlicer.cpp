#include "SFSlicer.h"
#include "FFDHSlicer.h"

/*
 * Split Fit
 *
 * Алгоритм, призванный улучшить FFDH (FFDHSlicer.h) по принципу «разделяй и властвуй».
 * Для начала отбираются прямоугольники, которые шире чем половина полосы.
 * Из них выбираются еще более широкие — шире, чем 2/3 полосы.
 * Они упаковываются алгоритмом FFDH.
 * Над ними, начиная со следующего уровня, упаковываются оставшиеся, те, что все еще шире 1/2, но уже 2/3.
 * Они тоже упаковываются с помощью FFDH.
 * Это разделение создает свободный регион шириной 1/3 справа от только что упакованных, начинающийся на уровне R
 * и заканчивающийся текущей верхней границей упаковки
 * (то есть он не простирается выше прямоугольников 1/2 < width <= 2/3).
 * Все оставшиеся прямоугольники, которые уже, чем 1/2 полосы, упаковываются с помощью того же FFDH в первую очередь
 * в образовавшийся регион, а если не помещаются — то сверху.
 *
 * https://habr.com/ru/post/136225/
 */
SliceResult SFSlicer::Slice(IMaterial* blank, Container<IMaterial*>* productContainer) {
    result->blank = blank;

    // разбиваем контейнер на 3 контейнера, удовлетворяющих алгоритму
    Container<IMaterial*>* notWidedProductContainer = new Container<IMaterial*>();        // уже,  чем 1/2 полосы
    Container<IMaterial*>* widedProductContainer = new Container<IMaterial*>();           // шире, чем 1/2 полосы
    Container<IMaterial*>* veryWidedProductContainer = new Container<IMaterial*>();       // шире, чем 2/3 полосы

    for (IMaterial* product : *productContainer) {
        if (product->getWidth() > blank->getWidth() * 2 / 3)
            veryWidedProductContainer->push(product);
        else if (product->getWidth() > blank->getWidth() / 2)
            widedProductContainer->push(product);
        else
            notWidedProductContainer->push(product);
    }

    // пакуем полученные контейнеры в порядке, указанном в алгоритме
    auto ffdhSlicer = new FFDHSlicer();
    ffdhSlicer->Slice(blank, veryWidedProductContainer);
    ffdhSlicer->Slice(blank, widedProductContainer);
    *result = ffdhSlicer->Slice(blank, notWidedProductContainer);

    return *result;
}

SFSlicer::~SFSlicer() = default;
