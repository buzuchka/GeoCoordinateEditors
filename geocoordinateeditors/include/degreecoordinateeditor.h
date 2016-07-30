#ifndef DEGREECOODINATEEDITOR_H
#define DEGREECOODINATEEDITOR_H

#include <QLineEdit>

class AbstractFormat;

// Виджет для редактирования географических координат
class DegreeCoordinateEditor : public QLineEdit
{
    Q_OBJECT
public:
    enum Format
    {
        DDMMSS
    };

    DegreeCoordinateEditor(QWidget * parent = 0, Format format = DDMMSS);
    ~DegreeCoordinateEditor();

    // Установить значение в виде десятичных градусов
    void setDecimalDegreesValue(double decimalDegrees);
    // Возвращает значение, установленное в виджете
    double getDecimalDegreesValue() const;

    void setPrecision(int precision);
    int getPresicion() const;

    void setMaxDegrees(const int maxDegreesValue);

private:
    void setFormat(Format format);
    void updateSize();

private:
    double m_decimalDegrees;
    int m_precision;

    AbstractFormat * m_format;
};

#endif
