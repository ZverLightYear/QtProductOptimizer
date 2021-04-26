#ifndef PO_RECTSLICEMANAGER_H
#define PO_RECTSLICEMANAGER_H

#include "ISliceManager.h"

/**
 * @brief Класс управления упаковщиками
 */
class RectSliceManager : public ISliceManager {
public:
    /**
     * @brief Конструктор класса
     */
    RectSliceManager();

    /**
     * @brief Задать базовый материал (базовую заготовку)
     * @param {IMaterial*} - Экземпляр заготовки
     */
    void SetBlank(IMaterial*) override;
    /**
     * @brief Задать базовый материал (базовую заготовку) исходя из размеров
     * @param {float} - Высота материала
     * @param {float} - Ширина материала
     */
    void SetBlank(float, float) override;

    /**
     * @brief Задать упаковщика изделий
     * @param {ISlicer*} - Экземпляр упаковщика
     */
    void SetSlicer(ISlicer*) override;

    /**
     * @brief Добавить изделие в контейнер
     * @param {IMaterial*} - Экземпляр изделия
     */
    void AddMaterial(IMaterial*) override;
    /**
     * @brief Добавить изделие в контейнер исходя из размеров
     * @param {float} - Высота изделия
     * @param {float} - Ширина изделия
     */
    void AddMaterial(float, float) override;
    /**
     * @brief Удалить изделие из контейнера
     * @param {int} - Индекс изделия в контейнере
     */
    void RemoveMaterial(int) override;
    /**
     * @brief Изменить размеры изделия в контейнере
     * @param {int} - Индекс изделия в контейнере
     * @param {float} - Новая высота изделия
     * @param {float} - Новая ширина изделия
     */
    void EditMaterial(int, float, float) override;
    /**
     * @return Количество изделий в контейнере
     */
    int MaterialCount() override;

    /**
     * @brief SLASH IT NOW !!!!!!!
     * @return {SliceResult} Результат упаковки ("нарезки") изделий на заготовке
     */
    SliceResult Slice() override;

    /**
     * Деструктор
     */
    ~RectSliceManager();
private:
    /// @brief Приватный экземпляр базового материала (заготовки)
    IMaterial* _blank = nullptr;
    /// @brief Приватный контейнер изделий
    Container<IMaterial*>* _materials = new Container<IMaterial*>();
    /// @brief Приватный экземпляр упаковщика изделий
    ISlicer* _slicer = nullptr;
};


#endif //PO_RECTSLICEMANAGER_H
