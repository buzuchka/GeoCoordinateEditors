#ifndef GEOCOORDINATEEDITORS_FORMAT_DDMMSS_HPP
#define GEOCOORDINATEEDITORS_FORMAT_DDMMSS_HPP

#include <AbstractFormat.hpp>

namespace Geo {

/*!
 * \brief Преобразование координаты в формат DDMMSS (градусы, минуты, секунды).
 */
class GEOCOORDINATEEDITORS_EXPORT Format_DDMMSS : public AbstractFormat
{
public:
  Format_DDMMSS(double decDegValue,
                int precision = 0,
                Separator separator = Period);

  ~Format_DDMMSS();

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
    M = 1,
    S = 2
  };

private:
  double mDegrees;
  double mMinutes;
  double mSeconds;

  int mMaxDegrees;

  const int mMaxMinutes;
  const int mMaxSeconds;
};

}

#endif
