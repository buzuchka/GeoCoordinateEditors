#include "degreecoordinateeditor.h"
#include "format.h"

#include <cassert>

DegreeCoordinateEditor::DegreeCoordinateEditor(QWidget *parent, Format format)
    : QLineEdit(parent),
      m_decimalDegrees(0.),
      m_precision(2),
      m_format(0)
{
    setFormat(format);
}

DegreeCoordinateEditor::~DegreeCoordinateEditor()
{
    delete m_format;
}

void DegreeCoordinateEditor::setDecimalDegreesValue(double decimalDegrees)
{
    m_decimalDegrees = decimalDegrees;
    m_format->setValue(decimalDegrees);
    setText(m_format->getDisplayValue());
}

double DegreeCoordinateEditor::getDecimalDegreesValue() const
{
    return m_decimalDegrees;
}

void DegreeCoordinateEditor::setPrecision(int precision)
{
    m_precision = precision;
}

int DegreeCoordinateEditor::getPresicion() const
{
    return m_precision;
}

void DegreeCoordinateEditor::setMaxDegrees(const int maxDegreesValue)
{
    m_format->setMaxDegrees(maxDegreesValue);
    updateSize();
}

void DegreeCoordinateEditor::setFormat(DegreeCoordinateEditor::Format format)
{
    if(m_format)
        delete m_format;

    switch(format)
    {
    case DDMMSS:
    {
        m_format = new Format_DDMMSS(this);
        break;
    }
    default:
    {
        assert("DegreeCoordinateEdtor::setFormat - Unknown format!");
        break;
    }
    }
    updateSize();

    m_format->setValue(m_decimalDegrees);
    setText(m_format->getDisplayValue());
}

void DegreeCoordinateEditor::updateSize()
{
    int width =
            fontMetrics().width('9') * m_format->getDisplayValue().length() * 0.92;
    setFixedWidth(width);
}
