#include "GraphicWindow.h"
#include "ui_GraphicWindow.h"
#include <qpainter.h>

#define OFFSET 20
#define WINDOW_SIZE 700
#define SEPARATOR QString(" x ")

GraphicWindow::GraphicWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::GraphicWindow) {
    ui->setupUi(this);
}

GraphicWindow::~GraphicWindow() {
    delete ui;
}

void GraphicWindow::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    QPainter qp(this);
    Paint(&qp);
}
void GraphicWindow::drawLevel(QPainter *painter, Level *level) const {
    // определяем параметры отрисовки учитывая масштаб
    auto x = OFFSET + level->coord.X * this->scale;
    auto y = OFFSET + level->coord.Y * this->scale;
    auto h = OFFSET;
    auto w = OFFSET;

    painter->drawLine(x, y, x + w, y);
    painter->drawLine(x, y, x, y + h);
}

void GraphicWindow::drawRect(QPainter* painter, GoodResult* rect, bool print_size ) const {
    // определяем параметры отрисовки учитывая масштаб
    auto x = OFFSET + rect->point.X * this->scale;
    auto y = OFFSET + rect->point.Y * this->scale;
    auto h = rect->material->getHeight() * this->scale;
    auto w = rect->material->getWidth() * this->scale;

    // painter->drawRect(x, y, w, h);
    painter->drawLine(x, y, x + w, y);
    painter->drawLine(x + w, y, x + w, y + h);
    painter->drawLine(x + w, y + h, x, y + h);
    painter->drawLine(x, y + h, x, y);

    // если надо, то выводим размеры нарисованного
    QString h_w;
    if (print_size)
        h_w = QString::number(rect->material->getHeight()) + SEPARATOR + QString::number(rect->material->getWidth());
    painter->drawText(x + 1, y + h, h_w);
}

void GraphicWindow::Paint(QPainter* painter) {
    // определяем масштаб отрисовки
    // задаем размеры окна исходя из вычисленного значения масштаба
    this->scale = WINDOW_SIZE / std::max(this->sr.blank->getWidth(), this->sr.blank->getHeight());

    int newWidth = this->sr.blank->getWidth() * this->scale + 2*OFFSET;
    int newHeight = this->sr.blank->getHeight() * this->scale + 2*OFFSET;
    newHeight += ui->lbEfficiency->height();
    this->setFixedSize(newWidth, newHeight);

    // Draw Blank
    QPen pen(Qt::red, 2, Qt::SolidLine);    // красным, толщина:2
    painter->setPen(pen);
    drawRect(painter, new GoodResult{ Point{0, 0}, this->sr.blank }, false);

    // Draw Products
    pen = QPen{ Qt::black, 1, Qt::SolidLine };  // черным, толщина:1
    painter->setPen(pen);
    for (GoodResult product : this->sr.good)
        drawRect(painter, &product);

    // Draw Levels
    pen = QPen{ Qt::green, 1, Qt::SolidLine };  // зеленым, толщина:1
    painter->setPen(pen);
    for (Level* level : this->sr.levels)
        drawLevel(painter, level);
}

void GraphicWindow::SetSliceResult(SliceResult sliceResult) {
    this->sr = sliceResult;
    // перемещаем лэйбл эффективности над графикой
    ui->lbEfficiency->move(OFFSET, 0);
    // устанавливаем отображаемый текст
    ui->lbEfficiency->setText("Efficiency : " + QString::number(this->sr.Efficiency() * 100, 'f', 2) + "%");
}