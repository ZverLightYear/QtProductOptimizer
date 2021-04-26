#ifndef PO_PRODUCTEDITWINDOW_H
#define PO_PRODUCTEDITWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ProductEditWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс, описывающий функционал окна редактора параметров изделия
 */
class ProductEditWindow : public QDialog {
Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent - родитель
     */
    explicit ProductEditWindow(QWidget *parent = nullptr);

    /**
     * @brief Задать значение высоты изделия
     * @param _text высота изделия
     */
    void setEditHeight(const QString &_text);
    /**
     * @brief Задать значение ширины изделия
     * @param _text Ширина изделия
     */
    void setEditWidth(const QString &_text);

    /**
     * @return Значение высоты изделия
     */
    QString lineEditHeght() const;
    /**
     * @return Значение ширины изделия
     */
    QString lineEditWidth() const;

    /**
     * @brief Деструктор
     */
    ~ProductEditWindow() override;
private:
    Ui::ProductEditWindow *ui;

public slots:
    /// @brief обработка нажатия на OK
    void dlgAccept();
    /// @brief обработка нажатия на Cancel
    void dlgReject();
};

#endif //PO_PRODUCTEDITWINDOW_H
