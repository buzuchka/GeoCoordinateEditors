#include "Geo/CircleEdit.hpp"
#include "Geo/PointEdit.hpp"
#include "Geo/Coordinate.hpp"

#include <QFormLayout>
#include <QDoubleSpinBox>

namespace Geo {

CircleEdit::CircleEdit(QWidget * parent, Qt::WindowFlags flags)
  : QWidget(parent, flags)
  , mPointEdit(new PointEdit(true, this))
  , mRadiusEdit(new QDoubleSpinBox(this))
{
  mRadiusEdit->setRange(0.0, 10000.0);
  mRadiusEdit->setDecimals(3);
  mRadiusEdit->setSuffix(tr(" км"));

  QFormLayout *const mainLayout = new QFormLayout(this);
  mainLayout->setLabelAlignment(Qt::AlignRight);
  mainLayout->addRow(tr("Координаты центра:"), mPointEdit);
  mainLayout->addRow(tr("Радиус:"), mRadiusEdit);

  mainLayout->setContentsMargins(0, 0, 0, 0);
}

void CircleEdit::setData(const Coordinate &coordinate, qreal radius)
{
  mPointEdit->setDecimalDegreesLatitude(coordinate.latitude());
  mPointEdit->setDecimalDegreesLongitude(coordinate.longitude());
  mRadiusEdit->setValue(radius / 1000.0);
}

Coordinate CircleEdit::getCenter() const
{
  return Coordinate(
        mPointEdit->getDecimalDegreesLatitude(),
        mPointEdit->getDecimalDegreesLongitude());
}

qreal CircleEdit::getRadius() const
{
  int radius = static_cast<int>(mRadiusEdit->value() * 1000.0);
  if (radius == 0)
    radius = -1; // Окружность с радиусом -1 считается невалидной.

  return radius;
}

}
