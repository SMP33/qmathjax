#include "mainwindow.h"

#include <QClipboard>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QSvgRenderer>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{

    QWidget* w1 = new QWidget;
    QWidget* w2 = new QWidget;
    m_tab = new QTableWidget;
    m_tab->setEnabled(false);

    m_edit = new QLineEdit;
    m_edit->setEnabled(false);
    m_view = new QWebEngineView;
    m_tex = new MathJaxSVG;

    QVBoxLayout* l = new QVBoxLayout(w1);
    QSizePolicy sp;
    sp.setHorizontalPolicy(QSizePolicy::Expanding);
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    w2->setSizePolicy(sp);

    l->addWidget(m_edit);
    l->addWidget(m_tab);

    setCentralWidget(w1);

    connect(m_tex, &MathJaxSVG::rendered,
        this, &MainWindow::addSvg);
    connect(m_tex, &MathJaxSVG::loadFinished,
        this, &MainWindow::onMathJaxLoaded);
    connect(m_edit, &QLineEdit::returnPressed,
        this, &MainWindow::onReturnPressed);

    m_tex->load();
}

MainWindow::~MainWindow()
{
}

void MainWindow::addSvg(QString latex, QByteArray svg)
{
    QLabel* lab = new QLabel;
    QSvgRenderer r;
    r.load(svg);

    QImage img(r.defaultSize(), QImage::Format_ARGB32);
    QPainter p(&img);
    p.fillRect(img.rect(), Qt::white);
    r.render(&p);

    QPixmap pm = QPixmap::fromImage(img);
    pm = pm.scaled(500, 150, Qt::KeepAspectRatio);

    lab->setPixmap(pm);
    m_tab->insertRow(0);
    m_tab->setCellWidget(0, 0, new QLabel(latex));
    m_tab->setCellWidget(0, 1, lab);
    m_tab->resizeColumnsToContents();
    m_tab->resizeRowsToContents();
}

void MainWindow::onMathJaxLoaded(bool)
{
    m_edit->setEnabled(true);
    m_tab->setEnabled(true);
    m_tab->setColumnCount(2);

    m_tex->render(R"(\frac{Простой^{Пример}}{С\;russian\;текстом})");
}

void MainWindow::onReturnPressed()
{
    m_tex->render(m_edit->text());
    m_edit->clear();
}
