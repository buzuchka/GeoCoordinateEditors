#ifndef GEOCOORDINATEEDITORS_COORDINATEVECTOREDIT_HPP
#define GEOCOORDINATEEDITORS_COORDINATEVECTOREDIT_HPP

#include <geocoordinateeditors_export.h>

#include <Geo/Coordinate.hpp>

#include <QTableWidget>

namespace Geo {

class PointEdit;

class GEOCOORDINATEEDITORS_EXPORT CoordinateVectorEdit : public QTableWidget
{
  Q_OBJECT
public:
  CoordinateVectorEdit(int vertexCount, QWidget * parent = 0);

  CoordinateVector getData();
  void setData(CoordinateVector const& data);
  void setReadOnly(bool flag);

signals:
  void dataChanged(CoordinateVector const& data);
  void vertexCountChanged(int count);

public slots:
  void setVertexCount(int count);

private slots:
  void onPointChanged();

private:
  PointEdit* getGeoPoint(int index);

private:
  bool m_readonlyFlag;
};

}

#endif
