#ifndef GEOCOORDINATEEDITORS_CIRCLEEDIT_HPP
#define GEOCOORDINATEEDITORS_CIRCLEEDIT_HPP

#include <geocoordinateeditors_export.h>

#include <QWidget>

class QDoubleSpinBox;

namespace Geo {

class Coordinate;
class PointEdit;

/*!
 * \brief Виджет для ввода и редактирования круга.
 */
class GEOCOORDINATEEDITORS_EXPORT CircleEdit : public QWidget
{
  Q_OBJECT
public:
  explicit CircleEdit(QWidget * parent = 0, Qt::WindowFlags flags = 0);

  void setData(Coordinate const& coordinate, qreal radius);

  Coordinate getCenter() const;
  qreal getRadius() const;

private:
  PointEdit *const mPointEdit;
  QDoubleSpinBox *const mRadiusEdit;
};

}

#endif
