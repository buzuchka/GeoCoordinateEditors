#include "format.h"
#include "degreecoordinateeditor.h"

#include <QtCore/qmath.h>

#include <QFontMetrics>

int HowManyChars(int x);

//=========================== AbstractFormat ==================================
AbstractFormat::AbstractFormat(DegreeCoordinateEditor *edit)
    : m_edit(edit)
{}

AbstractFormat::~AbstractFormat()
{}

//=========================== Format_DDMMSS ===================================
Format_DDMMSS::Format_DDMMSS(DegreeCoordinateEditor *edit)
    : AbstractFormat(edit),
      m_degrees(0.),
      m_minutes(0.),
      m_seconds(0.),
      m_maxDegrees(360.0),
      m_maxMinutes(59.0),
      m_maxSeconds(59.0),
      m_degreesFieldLength(3),
      m_minutesFieldLength(2),
      m_secondsFieldLength(2)
{
    setValue(edit->getDecimalDegreesValue());
}

Format_DDMMSS::~Format_DDMMSS()
{}

QString Format_DDMMSS::getDisplayValue() const
{
    return QString::fromUtf8("%1° %2' %3\"").
            arg(m_degrees, m_degreesFieldLength, 'f', 0, QLatin1Char('0')).
            arg(m_minutes, m_minutesFieldLength, 'f', 0, QLatin1Char('0')).
            arg(m_seconds, qMax(2, m_secondsFieldLength), 'f',
                qMax(0, m_edit->getPresicion()), QLatin1Char('0'));;
}

void Format_DDMMSS::setMaxDegrees(int maxDegreesValue)
{
    m_maxDegrees = maxDegreesValue;
    m_degreesFieldLength = HowManyChars(maxDegreesValue);
}

void Format_DDMMSS::setValue(double decimalDegreesValue)
{
    double decimalDegrees(decimalDegreesValue);

    if (decimalDegrees < -m_maxDegrees || m_maxDegrees < decimalDegrees)
    {
        m_degrees = 0.0;
        m_minutes = 0.0;
        m_seconds = 0.0;
        return;
    }

    if(decimalDegrees < 0.0)
        decimalDegrees *= -1;

    m_degrees = qFloor(decimalDegrees);

    decimalDegrees -= m_degrees;
    decimalDegrees *= 60.0;

    m_minutes = qFloor(decimalDegrees);

    decimalDegrees -= m_minutes;
    decimalDegrees *= 60.0;

    m_seconds = decimalDegrees;
    if (m_seconds - m_maxSeconds > 0.5*pow(10.0, m_edit->getPresicion()))
    {
        m_seconds = 0.0;
        m_minutes += 1;
        if (m_minutes > m_maxMinutes)
        {
            m_minutes = 0.0;
            m_degrees += 1;
        }
    }
}

int HowManyChars(int x)
{
    int k = 1;
    int n = 0;
    while (x / k != 0) {
        ++n;
        k *= 10;
    }
    return n;
}
