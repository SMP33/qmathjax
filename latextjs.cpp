#include "latextjs.h"

#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QRegularExpression>
#include <QTimer>
#include <QWebChannel>

LatextJs::LatextJs(QObject* parent)
    : QObject(parent)
{
    m_view.reset(new QWebEngineView());

    connect(m_view.get(), &QWebEngineView::loadFinished,
        this, &LatextJs::onPageLoaded);
}

void LatextJs::MathJaxDone(QString latex, QString svg1, QString svg2)
{

    QRegularExpression s1("<.?svg>");
    QRegularExpression s2("(<svg .+?>)");

    svg1 = svg1.replace(s1, " ");
    emit rendered(latex, svg2.replace(s2, "\\1" + svg1).toUtf8());
}

void LatextJs::MathJaxError(QString errorMessage)
{
    qDebug() << "ERROR:" << errorMessage;
}

void LatextJs::MathJaxLoaded()
{
    emit loadFinished(true);
}

void LatextJs::render(const QString& latex)
{
    QString tex = latex;
    tex = tex.replace("\\", "\\\\")
              .replace("'", "\\'")
              .replace("\n", "\\\n");

    QString toRun = QString("var TeX2SVG_result = null;"
                            "try {"
                            "    TeX2SVG_result = UpdateOutput( '%1' );"
                            "} catch ( e ) {"
                            "    cpp.MathJaxError(e);"
                            "}"
                            "TeX2SVG_result")
                        .arg(tex);

    m_page->runJavaScript(toRun);
}

void LatextJs::load()
{
    QString toLoad
        = "qrc:/main.html";
    m_view->load(QUrl(toLoad));
}

void LatextJs::onPageLoaded(bool result)
{
    if (result) {
        m_page.reset(m_view->page());
        QFile apiFile(":/qtwebchannel/qwebchannel.js"); //load the API from the resources
        if (!apiFile.open(QIODevice::ReadOnly))
            qDebug() << "Couldn't load Qt QWebChannel API!";
        QString apiScript = QString::fromLatin1(apiFile.readAll());
        apiFile.close();

        m_page->runJavaScript(apiScript);
        QWebChannel* ch = new QWebChannel(m_page.get());
        m_page->setWebChannel(ch);
        QString code = QStringLiteral(
            R"DELIM(
        window.webChannel = new QWebChannel(qt.webChannelTransport, function( channel)
        {
            cpp = channel.objects.cpp;
            if(MathJaxIsLoaded){
            cpp.MathJaxLoaded();
            }
        });

        )DELIM");

        ch->registerObject(QStringLiteral("cpp"), this);
        m_page->runJavaScript(code);
    } else {
        emit loadFinished(false);
    }
}
