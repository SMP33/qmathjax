#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWebEngineView>

#include "MathJaxSVG.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void addSvg(QString latex,QByteArray svg);
    void onMathJaxLoaded(bool);
    void onReturnPressed();

private:
    QLineEdit* m_edit;
    QTableWidget* m_tab;
    MathJaxSVG* m_tex;
    QWebEngineView* m_view;
};
#endif // MAINWINDOW_H
