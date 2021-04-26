#include "ProductEditWindow.h"
#include "ui_ProductEditWindow.h"

ProductEditWindow::ProductEditWindow(QWidget *parent) :
        QDialog(parent), ui(new Ui::ProductEditWindow) {
    ui->setupUi(this);

    ui->tbProductHeight->setValidator(new QDoubleValidator(1, 1000000, 2));
    ui->tbProductWidth->setValidator(new QDoubleValidator(1, 1000000, 2));

    // set signal and slot for "Buttons"
    connect(ui->btbResult, SIGNAL(accepted()), this, SLOT(dlgAccept()));
    connect(ui->btbResult, SIGNAL(rejected()), this, SLOT(dlgReject()));
}

ProductEditWindow::~ProductEditWindow() {
    delete ui;
}

void ProductEditWindow::dlgAccept() {
    auto textHeight = ui->tbProductHeight->text();
    auto textWidth = ui->tbProductWidth->text();

    if ((textHeight.toFloat() == 0) || (textWidth.toFloat() == 0)) return;

    accept();
}

void ProductEditWindow::dlgReject() {
    reject();
}

void ProductEditWindow::setEditHeight(const QString &_text) {
    ui->tbProductHeight->setText(_text);
}

void ProductEditWindow::setEditWidth(const QString &_text) {
    ui->tbProductWidth->setText(_text);
}

QString ProductEditWindow::lineEditHeght() const {
    return ui->tbProductHeight->text();
}

QString ProductEditWindow::lineEditWidth() const {
    return ui->tbProductWidth->text();
}
