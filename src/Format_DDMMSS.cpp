#include "Format_DDMMSS.hpp"

#include <QtCore/qmath.h>

int HowManyChars(int x);

namespace Geo {

Format_DDMMSS::Format_DDMMSS(double decDegValue,
                             int precision,
                             Separator separator)
  : AbstractFormat(decDegValue, precision, separator)
  , mDegrees(0.)
  , mMinutes(0.)
  , mSeconds(0.)
  , mMaxDegrees(360)
  , mMaxMinutes(59)
  , mMaxSeconds(59)
{
  setValue(mDecimalDegreeValue);
  configureSelections();
}

Format_DDMMSS::~Format_DDMMSS()
{}

const QString Format_DDMMSS::generateString() const
{
  QList<Selection> selections(generateSelections());
  return QString::fromUtf8("%1° %2' %3\"").
    arg(mDegrees, selections.at(D).length, 'f', 0, QLatin1Char('0')).
    arg(mMinutes, selections.at(M).length, 'f', 0, QLatin1Char('0')).
    arg(mSeconds, qMax(2, selections.at(S).length), 'f',
    qMax(0, mPrecision), QLatin1Char('0'));;
}

void Format_DDMMSS::setMaxDegrees(int maxDegreesValue)
{
  mMaxDegrees = maxDegreesValue;
  configureSelections();
}

QList<Selection> Format_DDMMSS::generateSelections() const
{
  const int specificSymbolLength = 1;
  const int spaceSymbolLength = 1;

  // Вычисление длины поля секунд
  // (если точность > 0, то выделяется дополнительная позиция под точку)
  const int secondsFieldLength = 2 + mPrecision + ((mPrecision > 0) ? 1 : 0);

  QList<Selection> selections;
  selections.append(Selection(0, HowManyChars(mMaxDegrees)));
  selections.append(Selection(selections.at(D).startPosition +
    selections.at(D).length +
    specificSymbolLength +
    spaceSymbolLength, 2));
  selections.append(Selection(selections.at(M).startPosition +
    selections.at(M).length +
    specificSymbolLength +
    spaceSymbolLength,
    secondsFieldLength));
  return selections;
}

void Format_DDMMSS::setValue(double decimalDegreesValue)
{
  double decimalDegrees(decimalDegreesValue);

  mHemisphereType = Plus;

  if (decimalDegrees < -mMaxDegrees || mMaxDegrees < decimalDegrees)
  {
    mDegrees = 0.0;
    mMinutes = 0.0;
    mSeconds = 0.0;
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

  mMinutes = qFloor(decimalDegrees);

  decimalDegrees -= mMinutes;
  decimalDegrees *= 60.0;

  mSeconds = decimalDegrees;
  if (mSeconds - mMaxSeconds > 0.5*pow(10.0, mPrecision))
  {
    mSeconds = 0.0;
    mMinutes += 1;
    if (mMinutes > mMaxMinutes)
    {
      mMinutes = 0.0;
      mDegrees += 1;
    }
  }
}

double Format_DDMMSS::getValue() const
{
  double value(mDegrees);
  if (mMinutes > 0.0)
    value += mMinutes / 60.0;
  if (mSeconds > 0.0)
    value += mSeconds / 3600.0;
  if (mHemisphereType == Minus)
    value *= -1;
  return value;
}

void Format_DDMMSS::pressed(int field, int num)
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
      mSeconds = 0.0;
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
  case S:
  {
    // Не позволяем менять секунды,
    // если градусы равны максимальному значению.
    if (mDegrees == mMaxDegrees)
      break;

    if (int(mSeconds) * 10 + num <= mMaxSeconds)
    {
      mSeconds = int(mSeconds) * 10;
      mSeconds += num;
    }
    else
      mSeconds = num;
    break;
  }
  }
}

void Format_DDMMSS::increase(int field)
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
    {
      mMinutes = 0.0;
      mSeconds = 0.0;
    }
    break;
  }
  case M:
  {
    if (mDegrees < mMaxDegrees)
      mMinutes += 1.0;

    // Замыкаем в круг.
    if (mMinutes > mMaxMinutes)
      mMinutes = 0.0;
    break;
  }
  case S:
  {
    if (mDegrees < mMaxDegrees)
      mSeconds += pow(10.0, -mPrecision);

    // Замыкаем в круг.
    if (mSeconds > mMaxSeconds)
      mSeconds = 0.0;
    break;
  }
  }
}

void Format_DDMMSS::decrease(int field)
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

    // Обнуляем минуты и секунды.
    if (mDegrees == mMaxDegrees)
    {
      mMinutes = 0.0;
      mSeconds = 0.0;
    }
    break;
  }
  case M:
  {
    if (mDegrees < mMaxDegrees)
      mMinutes -= 1.0;

    // Замыкаем в круг.
    if (mMinutes < 0.0)
      mMinutes = mMaxMinutes;
    break;
  }
  case S:
  {
    if (mDegrees < mMaxDegrees)
      mSeconds -= pow(10.0, -mPrecision);

    // Замыкаем в круг.
    if (mSeconds < 0.0)
      mSeconds = mMaxSeconds;
    break;
  }
  }
}

}
