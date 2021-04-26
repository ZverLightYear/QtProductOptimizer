#ifndef PO_PARAMETERSWINDOW_H
#define PO_PARAMETERSWINDOW_H

#include <QWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QStringListModel>
#include <QGridLayout>

#include "../core/MaterialContainer.h"
#include "../core/RectMaterial.h"
#include "../core/RectMaterial.h"

#include "../core/slicers/ISlicer.h"
#include "../core/slicers/ZESlicer.h"
#include "../core/slicers/ZEV2Slicer.h"
#include "../core/slicers/NFDHSlicer.h"
#include "../core/slicers/FFDHSlicer.h"
#include "../core/slicers/BFDHSlicer.h"
#include "../core/slicers/SFSlicer.h"
#include "../core/slicers/FCNRSlicer.h"
#include "../core/ISliceManager.h"
#include "../core/RectSliceManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ParametersWindow; }
QT_END_NAMESPACE

/**
 * @brief Класс, описывающий функционал главного окна
 */
class ParametersWindow : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param parent - родитель
     */
    explicit ParametersWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор
     */
    ~ParametersWindow() override;
private:
    Ui::ParametersWindow *ui;

    /// @brief Менеджер упаковки
    ISliceManager* sliceManager = new RectSliceManager();

    /**
     * @brief Вывод в отдельном окне результатов упаковки в графическом виде
     * @param {QString} Заголовок выбрасываемого окна
     */
    void showGraphicWindow(QString);
    /**
     * @brief Добавление изделия в список для упаковки
     * @param {float} - Высота изделия
     * @param {float} - Ширина изделия
     */
    void addProduct(float, float);
public slots:
    /// @brief Обработка нажатия на кнопку добавление изделия в список
    void add_clicked();
    /// @brief Обработка нажатия на кнопку редактирования изделия
    void edit_clicked();
    /// @brief Обработка нажатия на кнопку удаления изделия
    void delete_clicked();

    /// @brief Обработка нажатия на кнопку упаковщика ZE
    void ZE_clicked();
    /// @brief Обработка нажатия на кнопку упаковщика ZEV2
    void ZEV2_clicked();
    /// @brief Обработка нажатия на кнопку упаковщика NFDH
    void NFDH_clicked();
    /// @brief Обработка нажатия на кнопку упаковщика FFDH
    void FFDH_clicked();
    /// @brief Обработка нажатия на кнопку упаковщика BFDH
    void BFDH_clicked();
    /// @brief Обработка нажатия на кнопку упаковщика SF
    void SF_clicked();
    /// @brief Обработка нажатия на кнопку упаковщика FCNR
    void FCNR_clicked();
};

#endif //PO_PARAMETERSWINDOW_H
