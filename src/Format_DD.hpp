#ifndef GEOCOORDINATEEDITORS_FORMAT_DD_HPP
#define GEOCOORDINATEEDITORS_FORMAT_DD_HPP

#include <AbstractFormat.hpp>

namespace Geo {

/*!
 * \brief Преобразование координаты в формат DD (только градусы).
 */
class GEOCOORDINATEEDITORS_EXPORT Format_DD : public AbstractFormat
{
public:
  Format_DD(double decDegValue,
            int precision = 0,
            Separator separator = Period);

  ~Format_DD();

  void setValue(double decimalDegrees);
  double getValue() const;

  void setMaxDegrees(int maxDegreesValue);

protected:
  QList<Selection> generateSelections() const;
  const QString generateString() const;

  void pressed(int field, int num);
  void increase(int field);
  void decrease(int field);

private:
  double mDegrees;
  int mMaxDegrees;
};

}

#endif
