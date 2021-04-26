#ifndef PO_RECTMATERIAL_H
#define PO_RECTMATERIAL_H

#include "IMaterial.h"

/**
 * @brief Класс материала прямоугольной формы
 */
class RectMaterial : public IMaterial {
public:
    /**
     * @brief Конструктор
      * @param height - Высота материала
      * @param width - Ширина материала
     */
    RectMaterial(float height, float width);

    /**
     * @return Площадь материала
     */
    float Area() const override;

    /**
     * @return Высота материала
     */
    float getHeight() const override;
    /**
     * @return Ширина материала
     */
    float getWidth() const override;

    /**
     * @brief Осуществялет переворачивание материала
     * @return Ссылка на новый экземпляр изделия (перевернутого)
     */
    virtual RectMaterial* Rotate() override;

    /**
     * @brief Деструктор
     */
    ~RectMaterial();
private:
    /// @brief Приватный параметр высоты материала
    float _height;
    /// @brief Приватный параметр ширины материала
    float _width;
};

#endif //PO_RECTMATERIAL_H
