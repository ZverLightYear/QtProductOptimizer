#ifndef PO_IMATERIAL_H
#define PO_IMATERIAL_H

/**
 * Интерфейс, задающий новый материал (изделие / заготовку)
 */
class IMaterial {
public:
    /**
     * @return Площадь материала
     */
    virtual float Area() const = 0;

    /**
     * @return Ширина материала
     */
    virtual float getWidth() const = 0;
    /**
     * @return Высота материала
     */
    virtual float getHeight() const = 0;

    /**
     * @brief Осуществялет переворачивание материала
     * @return Новый экземпляр изделия, который будет уже перевернутым
     */
    virtual IMaterial* Rotate() = 0;
};

#endif //PO_IMATERIAL_H
