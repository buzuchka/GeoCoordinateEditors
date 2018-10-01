#ifndef GEOCOORDINATEEDITORS_DEGREECOODINATEEDIT_HPP
#define GEOCOORDINATEEDITORS_DEGREECOODINATEEDIT_HPP

#include <GEOCOORDINATEEDITORS_EXPORT.h>

#include <Geo/Format.hpp>

#include <QLineEdit>

namespace Geo {

class AbstractFormat;

// Виджет для редактирования географических координат
class GEOCOORDINATEEDITORS_EXPORT DegreeCoordinateEdit : public QLineEdit
{
  Q_OBJECT
public:
  DegreeCoordinateEdit(QWidget * parent = 0,
                       Format format = Geo::DDMMSS);
  ~DegreeCoordinateEdit();

  // Установить значение в виде десятичных градусов
  void setDecimalDegreesValue(double decimalDegrees);
  // Возвращает значение, установленное в виджете
  double getDecimalDegreesValue() const;

  void setMaxDegrees(const int maxDegreesValue);

  void setFormat(Format format,
                 int precision = 0,
                 Separator separator = Geo::Period);

  // Установка обозначений положительной и отрицательной полусфер.
  void setDesignationHemisphereType(const QString & plusChr,
                                    const QString & minusChr,
                                    HemisphereCharPosition position);

signals:
  // Для перемещения курсора на соседние виджеты DegreeCoordinateEdit
  void up();
  void down();
  void right();
  void left();

protected:
  void focusInEvent(QFocusEvent * e);
  void focusOutEvent(QFocusEvent * e);

  void mousePressEvent(QMouseEvent * e);
  void mouseMoveEvent(QMouseEvent * e);

  void keyPressEvent(QKeyEvent * e);
  void wheelEvent(QWheelEvent * event);

private:
  void updateSize();
  void updateText();
  void updateSelection();

private:
  double m_decimalDegrees;

  AbstractFormat * m_format;
};

}

#endif
