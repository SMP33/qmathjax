#ifndef LATEXTJS_H
#define LATEXTJS_H

#include <QObject>
#include <QWebEnginePage>
#include <QWebEngineView>

#include <QScopedPointer>

class LatextJs : public QObject {
    Q_OBJECT
public:
    explicit LatextJs(QObject* parent = nullptr);

    Q_INVOKABLE void MathJaxDone(QString latex,QString svg1, QString svg2);
    Q_INVOKABLE void MathJaxError(QString errorMessage);
    Q_INVOKABLE void MathJaxLoaded();

public slots:
    void render(const QString& latex);
    void load();

signals:
    void rendered(QString latex,QByteArray svg);
    void loadFinished(bool result);

private slots:
    void onPageLoaded(bool);

private:
    QScopedPointer<QWebEngineView> m_view;
    QScopedPointer<QWebEnginePage> m_page;
};

#endif // LATEXTJS_H
