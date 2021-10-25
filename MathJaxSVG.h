#pragma once

#include <QtCore/QObject>
#include <QQueue>

class LatextJs;

class MathJaxSVG : public QObject {
    Q_OBJECT
public:
    explicit MathJaxSVG(QObject* parent = nullptr);

    bool isLoaded() const;

public slots:
    void render(const QString& latex);
    void load();
signals:
    void rendered(QString latex, QByteArray svg);
    void loadFinished(bool result);

private slots:
    void setIsLoaded(bool new_isLoaded);

private:
    QQueue<QString> m_queue;
    bool mb_isLoaded;
    LatextJs* m_latexJS;
};
