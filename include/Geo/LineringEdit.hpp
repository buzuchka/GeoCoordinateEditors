#ifndef GEOCOORDINATEEDITORS_LINERINGEDIT_HPP
#define GEOCOORDINATEEDITORS_LINERINGEDIT_HPP

#include <geocoordinateeditors_export.h>

#include <Geo/Coordinate.hpp>

#include <QWidget>

class QSpinBox;

namespace Geo {

class CoordinateVectorEdit;

/*!
 * \brief Виджет для ввода и редактирования полигона.
 */
class GEOCOORDINATEEDITORS_EXPORT LineRingEdit : public QWidget
{
  Q_OBJECT
public:
  explicit LineRingEdit(QWidget * parent = 0, Qt::WindowFlags flags = 0);

  void setData(CoordinateVector const& vector);
  CoordinateVector getData();

  void clear();

  void setReadOnly(bool flag);

  void setMaximum(unsigned int value);

signals:
  void dataChanged(CoordinateVector const& data);

private slots:
  void onVertexCountChanged();

private:
  CoordinateVectorEdit *const mCoordinateVectorEdit;
  QSpinBox* mVertexCountSpinBox;
};

}

#endif
