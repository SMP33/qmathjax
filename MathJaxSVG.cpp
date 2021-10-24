#include "MathJaxSVG.h"
#include "latextjs.h"

MathJaxSVG::MathJaxSVG(QObject* parent)
    : QObject(parent)
{
    mb_isLoaded = false;
    m_latexJS = new LatextJs(this);

    connect(m_latexJS, &LatextJs::loadFinished,
        this, &MathJaxSVG::setIsLoaded);
    connect(m_latexJS, &LatextJs::loadFinished,
        this, &MathJaxSVG::loadFinished);
    connect(m_latexJS, &LatextJs::rendered,
        this, &MathJaxSVG::rendered);
}

bool MathJaxSVG::isLoaded() const
{
    return mb_isLoaded;
}

void MathJaxSVG::render(const QString& latex)
{
    m_latexJS->render(latex);
}

void MathJaxSVG::load()
{
    m_latexJS->load();
}

void MathJaxSVG::setIsLoaded(bool new_isLoaded)
{
    mb_isLoaded = new_isLoaded;
}
