#ifndef GEOCOORDINATEEDITORS_FORMAT_DDMM_HPP
#define GEOCOORDINATEEDITORS_FORMAT_DDMM_HPP

#include <AbstractFormat.hpp>

namespace Geo {

/*!
 * \brief Преобразование координаты в формат DDMM (градусы и минуты).
 */
class Format_DDMM : public AbstractFormat
{
public:
  Format_DDMM(double decDegValue,
              int precision = 0,
              Separator separator = Period);

  ~Format_DDMM();

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
  enum Element
  {
    D = 0,
    M = 1
  };

private:
  double mDegrees;
  double mMinutes;

  int mMaxDegrees;

  const int mMaxMinutes;
};

}

#endif
