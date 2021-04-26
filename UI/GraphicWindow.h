#ifndef PO_GRAPHICWINDOW_H
#define PO_GRAPHICWINDOW_H

#include <QWidget>
#include "../core/slicers/SliceResult.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GraphicWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс, описывающий функционал окна вывода в графическом виде информации об упаковке изделий
 */
class GraphicWindow : public QWidget {
Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent - родитель
     */
    explicit GraphicWindow(QWidget *parent = nullptr);

    /**
     * @brief Метод отрисовки окна
     * @param painter - Художник, который будет рисовать результат упаковки =)
     */
    void Paint(QPainter* painter);
    /**
     * @brief Установить результат упаковки для отображения
     * @param sliceResult - Результат упаковки
     */
    void SetSliceResult(SliceResult sliceResult);

    /**
     * @brief Деструктор
     */
    ~GraphicWindow() override;

protected:
    /**
     * @brief Обработчик события отрисовки окна
     * @param event - событие
     */
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::GraphicWindow *ui;

    /// @brief Результат упаковки для отображения
    SliceResult sr;

    /// @brief Масштаб отображения результатов
    float scale = 1;

    /**
     * @brief Нарисовать прямоугольник
     * @param painter - Художник, который нарисует
     * @param rect - непосредственно, прямоугольник, который надо нарисовать
     * @param print_size - флаг, указывающий на необходимость напечатать размер рисуемого прямоугольника
     */
    void drawRect(QPainter* painter, GoodResult* rect, bool print_size = true) const;

    /**
     * @brief Нарисовать уровень упаковки
     * @param painter - Художник, который нарисует
     * @param level - уровень, который надо нарисовать
     */
    void drawLevel(QPainter* painter, Level* level) const;
};

#endif //PO_GRAPHICWINDOW_H
