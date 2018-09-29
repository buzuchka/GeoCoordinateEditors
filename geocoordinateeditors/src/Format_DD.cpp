#include "Format_DD.hpp"

#include <QtCore/qmath.h>

int HowManyChars(int x);

namespace Geo {

Format_DD::Format_DD(double decDegValue, int precision, Separator separator)
  : AbstractFormat(decDegValue, precision, separator)
  , mDegrees(0.)
  , mMaxDegrees(360)
{
  setValue(mDecimalDegreeValue);
  configureSelections();
}

Format_DD::~Format_DD()
{}

const QString Format_DD::generateString() const
{
  QList<Selection> selections(generateSelections());
  return QString::fromUtf8("%1°").
    arg(mDegrees, qMax(2, selections.at(0).length), 'f',
    qMax(0, mPrecision), QLatin1Char('0'));
}

void Format_DD::setMaxDegrees(int maxDegreesValue)
{
  mMaxDegrees = maxDegreesValue;
  configureSelections();
}

QList<Selection> Format_DD::generateSelections() const
{
  // Вычисление длины поля градусов
  // (если точность > 0, то выделяется дополнительная позиция под точку)
  const int degreesFieldLength = HowManyChars(mMaxDegrees) +
                                 mPrecision +
                                 ((mPrecision > 0) ? 1 : 0);

  QList<Selection> selections;
  selections.append(Selection(0, degreesFieldLength));
  return selections;
}

void Format_DD::setValue(double decimalDegreesValue)
{
  double decimalDegrees(decimalDegreesValue);

  mHemisphereType = Plus;

  if (decimalDegrees < -mMaxDegrees || mMaxDegrees < decimalDegrees)
  {
    mDegrees = 0.0;
    return;
  }

  if (decimalDegrees < 0.0)
  {
    mHemisphereType = Minus;
    decimalDegrees *= -1;
  }

  mDegrees = qFloor(decimalDegrees);
}

double Format_DD::getValue() const
{
  double value(mDegrees);
  if (mHemisphereType == Minus)
    value *= -1;
  return value;
}

void Format_DD::pressed(int field, int num)
{
  if (field != 0) return;

  if (int(mDegrees) * 10 + num <= mMaxDegrees)
  {
    mDegrees = int(mDegrees) * 10;
    mDegrees += num;
  }
  else
    mDegrees = num;

  if (mDegrees >= mMaxDegrees)
    mDegrees = mMaxDegrees;
}

void Format_DD::increase(int field)
{
  if (field != 0) return;
  mDegrees += pow(10.0, -mPrecision);

  // Замыкаем в круг.
  if (mDegrees > mMaxDegrees)
    mDegrees = 0.0;
}

void Format_DD::decrease(int field)
{
  if (field != 0) return;

  mDegrees -= pow(10.0, -mPrecision);

  // Замыкаем в круг.
  if (mDegrees < 0)
    mDegrees = mMaxDegrees;
}

}
