#include "inputrenderer.h"

QString InputRenderer::render(QString input)
{
    QString output = input.replace("[pi]", "\u03c0");
    output = output.remove("[").remove("]").remove("&");
    return output;
}
