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
    if (mb_isLoaded) {
        m_latexJS->render(latex);
    } else {
        m_queue.push_back(latex);
    }
}

void MathJaxSVG::load()
{
    m_latexJS->load();
}

void MathJaxSVG::setIsLoaded(bool new_isLoaded)
{
    mb_isLoaded = new_isLoaded;

    while (!m_queue.empty()) {
        render(m_queue.front());
        m_queue.pop_front();
    }
}
