#include "Geo/PointEdit.hpp"

#include "LatitudeEdit.hpp"
#include "LongitudeEdit.hpp"

#include <QHBoxLayout>

namespace Geo {

PointEdit::PointEdit(bool bordersOn, QWidget * parent)
  : QWidget()
  , mLatitudeEdit(new LatitudeEdit(this))
  , mLongitudeEdit(new LongitudeEdit(this))
{
  if(!bordersOn)
    setStyleSheet(QString::fromUtf8(
                      "QLineEdit { border: 0px; }"));

  connect(mLatitudeEdit, SIGNAL(textChanged(QString)),
          this, SLOT(changeValue()));
  connect(mLongitudeEdit, SIGNAL(textChanged(QString)),
          this, SLOT(changeValue()));

  QHBoxLayout * const mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(mLatitudeEdit);
  mainLayout->addWidget(mLongitudeEdit);

  mainLayout->setSpacing(0);
  mainLayout->setContentsMargins(0, 0, 0, 0);

  // Навигация между координатами точки
  connect(mLatitudeEdit, SIGNAL(right()), this, SLOT(focusLonEditAtStart()));
  connect(mLongitudeEdit, SIGNAL(left()), this, SLOT(focusLatEditAtStart()));

  // Навигация между точками
  connect(mLatitudeEdit, SIGNAL(left()),this, SIGNAL(prevLon()));
  connect(mLatitudeEdit, SIGNAL(up()),this, SIGNAL(prevLat()));
  connect(mLatitudeEdit, SIGNAL(down()), this,SIGNAL(nextLat()));
  connect(mLongitudeEdit, SIGNAL(right()), this,SIGNAL(nextLat()));
  connect(mLongitudeEdit, SIGNAL(up()),this, SIGNAL(prevLon()));
  connect(mLongitudeEdit, SIGNAL(down()), this, SIGNAL(nextLon()));

  setMinimumSize(sizeHint());
}

void PointEdit::clear()
{
  mLatitudeEdit->setDecimalDegreesValue(0);
  mLongitudeEdit->setDecimalDegreesValue(0);
}

void PointEdit::setFormat(Format format, int precision)
{
  mLatitudeEdit->setFormat(format, precision);
  mLongitudeEdit->setFormat(format, precision);
}

void PointEdit::setDesignationsHemisphereType(
    const QString &plusChrLat, const QString &minusChrLat,
    const QString &plusChrLon, const QString &minusChrLon,
    HemisphereCharPosition position)
{
  mLatitudeEdit->setDesignationHemisphereType(
        plusChrLat, minusChrLat, position);
  mLongitudeEdit->setDesignationHemisphereType(
        plusChrLon, minusChrLon, position);
}

double PointEdit::getDecimalDegreesLatitude() const
{
  return mLatitudeEdit->getDecimalDegreesValue();
}

void PointEdit::setDecimalDegreesLatitude(double decDegLat)
{
  mLatitudeEdit->setDecimalDegreesValue(decDegLat);
}

double PointEdit::getDecimalDegreesLongitude() const
{
  return mLongitudeEdit->getDecimalDegreesValue();
}

void PointEdit::setDecimalDegreesLongitude(double decDegLon)
{
  mLongitudeEdit->setDecimalDegreesValue(decDegLon);
}

void PointEdit::changeValue()
{
  double lat = mLatitudeEdit->getDecimalDegreesValue();
  double lon = mLongitudeEdit->getDecimalDegreesValue();
  emit changed(lat, lon);
}

void PointEdit::setReadOnly(bool flag)
{
  mLongitudeEdit->setReadOnly(flag);
  mLatitudeEdit->setReadOnly(flag);
}

void PointEdit::focusLonEditAtStart()
{
  mLongitudeEdit->setFocus();
}

void PointEdit::focusLatEditAtStart()
{
  mLatitudeEdit->setFocus();
}

}
