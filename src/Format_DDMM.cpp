#include "Format_DDMM.hpp"

#include <QtCore/qmath.h>

int HowManyChars(int x);

namespace Geo {

Format_DDMM::Format_DDMM(double decDegValue,
                         int precision,
                         Separator separator)
  : AbstractFormat(decDegValue, precision, separator)
  , mDegrees(0.)
  , mMinutes(0.)
  , mMaxDegrees(360)
  , mMaxMinutes(59)
{
  setValue(mDecimalDegreeValue);
  configureSelections();
}

Format_DDMM::~Format_DDMM()
{}

const QString Format_DDMM::generateString() const
{
  QList<Selection> selections(generateSelections());
  return QString::fromUtf8("%1° %2'").
    arg(mDegrees, selections.at(D).length, 'f', 0, QLatin1Char('0')).
    arg(mMinutes, qMax(2, selections.at(M).length), 'f',
    qMax(0, mPrecision), QLatin1Char('0'));;
}

void Format_DDMM::setMaxDegrees(int maxDegreesValue)
{
  mMaxDegrees = maxDegreesValue;
  configureSelections();
}

QList<Selection> Format_DDMM::generateSelections() const
{
  const int specificSymbolLength = 1;
  const int spaceSymbolLength = 1;

  // Вычисление длины поля минут
  // (если точность > 0, то выделяется дополнительная позиция под точку)
  const int minutesFieldLength = 2 + mPrecision + ((mPrecision > 0) ? 1 : 0);

  QList<Selection> selections;
  selections.append(Selection(0, HowManyChars(mMaxDegrees)));
  selections.append(Selection(selections.at(D).startPosition +
    selections.at(D).length +
    specificSymbolLength +
    spaceSymbolLength,
    minutesFieldLength));
  return selections;
}

void Format_DDMM::setValue(double decimalDegreesValue)
{
  double decimalDegrees(decimalDegreesValue);

  mHemisphereType = Plus;

  if (decimalDegrees < -mMaxDegrees || mMaxDegrees < decimalDegrees)
  {
    mDegrees = 0.0;
    mMinutes = 0.0;
    return;
  }

  if (decimalDegrees < 0.0)
  {
    mHemisphereType = Minus;
    decimalDegrees *= -1;
  }

  mDegrees = qFloor(decimalDegrees);

  decimalDegrees -= mDegrees;
  decimalDegrees *= 60.0;

  mMinutes = decimalDegrees;

  if (mMinutes - mMaxMinutes > 0.5*pow(10.0, mPrecision))
  {
    mMinutes = 0.0;
    mDegrees += 1;
    if (mMinutes > mMaxMinutes)
    {
      mMinutes = 0.0;
      mDegrees += 1;
    }
  }
}

double Format_DDMM::getValue() const
{
  double value(mDegrees);
  if (mMinutes > 0.0)
    value += mMinutes / 60.0;
  if (mHemisphereType == Minus)
    value *= -1;
  return value;
}

void Format_DDMM::pressed(int field, int num)
{
  Element selectedElement = (Element)field;
  switch (selectedElement)
  {
  case D:
  {
    if (int(mDegrees) * 10 + num <= mMaxDegrees)
    {
      mDegrees = int(mDegrees) * 10;
      mDegrees += num;
    }
    else
      mDegrees = num;

    if (mDegrees >= mMaxDegrees)
    {
      mDegrees = mMaxDegrees;
      mMinutes = 0.0;
    }
    break;
  }
  case M:
  {
    // Не позволяем менять минуты,
    // если градусы равны максимальному значению.
    if (mDegrees == mMaxDegrees)
      break;

    if (int(mMinutes) * 10 + num <= mMaxMinutes)
    {
      mMinutes = int(mMinutes) * 10;
      mMinutes += num;
    }
    else
      mMinutes = num;
    break;
  }
  }
}

void Format_DDMM::increase(int field)
{
  Element selectedElement = (Element)field;
  switch (selectedElement)
  {
  case D:
  {
    mDegrees += 1.0;

    // Замыкаем в круг.
    if (mDegrees > mMaxDegrees)
      mDegrees = 0.0;

    // Обнуляем минуты и секунды.
    if (mDegrees == mMaxDegrees)
      mMinutes = 0.0;
    break;
  }
  case M:
  {
    if (mDegrees < mMaxDegrees)
      mMinutes += pow(10.0, -mPrecision);

    // Замыкаем в круг.
    if (mMinutes > mMaxMinutes)
      mMinutes = 0.0;
    break;
  }
  }
}

void Format_DDMM::decrease(int field)
{
  Element selectedElement = (Element)field;
  switch (selectedElement)
  {
  case D:
  {
    mDegrees -= 1.0;

    // Замыкаем в круг.
    if (mDegrees < 0)
      mDegrees = mMaxDegrees;

    if (mDegrees == mMaxDegrees)
      mMinutes = 0.0;
    break;
  }
  case M:
  {
    if (mDegrees < mMaxDegrees)
      mMinutes -= pow(10.0, -mPrecision);

    // Замыкаем в круг.
    if (mMinutes < 0.0)
      mMinutes = mMaxMinutes;
    break;
  }
  }
}

}
