#ifndef GEOCOORDINATEEDITORS_POINTEDIT_HPP
#define GEOCOORDINATEEDITORS_POINTEDIT_HPP

#include <geocoordinateeditors_export.h>

#include <Geo/Format.hpp>

#include <QWidget>

namespace Geo {

class LatitudeEdit;
class LongitudeEdit;

/*!
 * \brief Виджет для ввода и редактирования точки.
 */
class GEOCOORDINATEEDITORS_EXPORT PointEdit: public QWidget
{
  Q_OBJECT
public:
  explicit PointEdit(bool bordersOn = true, QWidget * parent = 0);

  double getDecimalDegreesLatitude() const;
  void setDecimalDegreesLatitude(double decDegLat);

  double getDecimalDegreesLongitude() const;
  void setDecimalDegreesLongitude(double decDegLon);

  // Установка формата отображения координат
  void setFormat(Format format, int precision = 0);

  // Установка обозначений положительной и отрицательной полусфер широты и долготы.
  void setDesignationsHemisphereType(const QString & plusChrLat,
                                     const QString & minusChrLat,
                                     const QString & plusChrLon,
                                     const QString & minusChrLon,
                                     HemisphereCharPosition position);
  void setReadOnly(bool flag);
  void clear();

signals:
  void changed(double decDegLat, double decDegLon);

  // Для навигации между координатами группы точек
  void prevLat();
  void prevLon();
  void nextLat();
  void nextLon();

private slots:
  void focusLonEditAtStart();
  void focusLatEditAtStart();

  void changeValue();

private:
  LatitudeEdit * const mLatitudeEdit;
  LongitudeEdit * const mLongitudeEdit;
};

}

#endif
