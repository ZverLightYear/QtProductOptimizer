#include "ParametersWindow.h"
#include "ui_ParametersWindow.h"
#include "ProductEditWindow.h"
#include "GraphicWindow.h"

#define SEPARATOR " x "

ParametersWindow::ParametersWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::ParametersWindow) {
    ui->setupUi(this);

    // задаем границы значений для размеров заготовки
    ui->tbBlankHeight->setValidator(new QDoubleValidator(10, 1000000, 2));
    ui->tbBlankWidth->setValidator(new QDoubleValidator(10, 1000000, 2));

/*
    /// Для тестов
    ui->tbBlankHeight->setText("100");
    ui->tbBlankWidth->setText("100");

    /// Для тестов
    addProduct(80, 10);
    addProduct(20, 100);
    addProduct(30, 90);
    addProduct(20, 20);
    addProduct(30, 20);
    addProduct(50, 15);
    addProduct(10, 55);
    addProduct(40, 55);
*/
    /// Для тестов
    ui->tbBlankHeight->setText("123");
    ui->tbBlankWidth->setText("123");

    /// Для тестов
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(12, 12);
    addProduct(23, 23);
    addProduct(34, 34);
    addProduct(45, 45);
    addProduct(78, 78);
    addProduct(1, 1);
    addProduct(2, 2);
    addProduct(3, 3);
    addProduct(4, 4);
    addProduct(11, 111);

    // привязываем обработчики к сигналам
    connect(ui->btAddProduct, SIGNAL(clicked()), this, SLOT(add_clicked()));
    connect(ui->btEditProduct, SIGNAL(clicked()), this, SLOT(edit_clicked()));
    connect(ui->btRemoveProduct, SIGNAL(clicked()), this, SLOT(delete_clicked()));
    connect(ui->btZE, SIGNAL(clicked()), this, SLOT(ZE_clicked()));
    connect(ui->btZEV2, SIGNAL(clicked()), this, SLOT(ZEV2_clicked()));
    connect(ui->btNFDH, SIGNAL(clicked()), this, SLOT(NFDH_clicked()));
    connect(ui->btFFDH, SIGNAL(clicked()), this, SLOT(FFDH_clicked()));
    connect(ui->btBFDH, SIGNAL(clicked()), this, SLOT(BFDH_clicked()));
    connect(ui->btSF, SIGNAL(clicked()), this, SLOT(SF_clicked()));
    connect(ui->btFCNR, SIGNAL(clicked()), this, SLOT(FCNR_clicked()));

    // отключаем возможность пользоваться нереализованным функционалом
    /// ToDo: почему это в релизе?
    ui->btBFDH->setDisabled(true);
    ui->btFCNR->setDisabled(true);
}

ParametersWindow::~ParametersWindow() {
    delete ui;
}

void ParametersWindow::addProduct(float height, float width) {
    // когда добавляем изделие - добавляем его в список формы + в список менеджера упаковки
    ui->lstProducts->addItem(QString::number(height) + SEPARATOR + QString::number(width));
    this->sliceManager->AddMaterial(height, width);
}

void ParametersWindow::add_clicked() {
    QString height = "";
    QString width = "";

    auto wAddProduct = new ProductEditWindow();
    wAddProduct->setEditHeight(height);
    wAddProduct->setEditWidth(width);

    if(wAddProduct->exec() == QDialog::Accepted) {
        height = wAddProduct->lineEditHeght();
        width = wAddProduct->lineEditWidth();
        addProduct(height.toFloat(), width.toFloat());
    }
}

void ParametersWindow::edit_clicked() {
    // получаем индекс строки и саму строку
    auto row = ui->lstProducts->currentItem();
    auto rowIndex = ui->lstProducts->currentRow();

    if (!row) return;

    // крошим текст
    // так себе решение, но работает
    // ToDo: забирать значения у менеджера упаковки
    auto rowTextList = row->text().split(SEPARATOR);
    QString height = rowTextList[0];
    QString width = rowTextList[1];

    auto wAddProduct = new ProductEditWindow();
    wAddProduct->setEditHeight(height);
    wAddProduct->setEditWidth(width);

    if(wAddProduct->exec() == QDialog::Accepted) {
        height = wAddProduct->lineEditHeght();
        width = wAddProduct->lineEditWidth();
        row->setText(height + SEPARATOR + width);
        sliceManager->EditMaterial(rowIndex, height.toFloat(), width.toFloat());
    }
}

void ParametersWindow::delete_clicked() {
    // удаляем из двух мест - из списка формы + из списка менеджера упаковки
    auto index = ui->lstProducts->currentRow();
    ui->lstProducts->takeItem(index);
    sliceManager->RemoveMaterial(index);
}

void ParametersWindow::showGraphicWindow(QString caption)
{
    // пытаемся создать экземпляр заготовки
    if (sliceManager->MaterialCount() == 0) return;

    auto blankHeight = ui->tbBlankHeight->text().toFloat();
    auto blankWidth = ui->tbBlankWidth->text().toFloat();

    if ((blankHeight == 0) || (blankWidth == 0)) return;

    sliceManager->SetBlank(blankHeight, blankWidth);

    // выводим
    GraphicWindow* gw = new GraphicWindow();
    gw->setWindowTitle(caption);
    gw->SetSliceResult(sliceManager->Slice());
    gw->show();
}

void ParametersWindow::ZE_clicked() {
    sliceManager->SetSlicer(new ZESlicer());
    showGraphicWindow("ZE");
}

void ParametersWindow::ZEV2_clicked() {
    sliceManager->SetSlicer(new ZEV2Slicer());
    showGraphicWindow("ZEV2");
}

void ParametersWindow::NFDH_clicked() {
    sliceManager->SetSlicer(new NFDHSlicer());
    showGraphicWindow("NFDH");
}

void ParametersWindow::FFDH_clicked() {
    sliceManager->SetSlicer(new FFDHSlicer());
    showGraphicWindow("FFDH");
}

void ParametersWindow::BFDH_clicked() {
    sliceManager->SetSlicer(new BFDHSlicer());
    // showGraphicWindow("BFDH");
}

void ParametersWindow::SF_clicked() {
    sliceManager->SetSlicer(new SFSlicer());
    showGraphicWindow("SF");
}

void ParametersWindow::FCNR_clicked() {
    sliceManager->SetSlicer(new FCNRSlicer());
    // showGraphicWindow("FCNR");
}