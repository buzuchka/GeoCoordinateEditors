#include "AbstractFormat.hpp"

namespace Geo {

AbstractFormat::AbstractFormat(double decDegValue, int precision, Separator separator)
  : mDecimalDegreeValue(decDegValue)
  , mHemisphereType((decDegValue < 0) ? Minus : Plus)
  , mPrecision(precision)
  , mSelected(0)
  , mPlusHsphChar(QLatin1Char('+'))
  , mMinusHsphChar(QLatin1Char('-'))
  , mHsphChrPosition(Prefix)
  , mSeparator(separator)
{}

AbstractFormat::~AbstractFormat()
{}

void AbstractFormat::setPrecision(int precision)
{
  mPrecision = precision;
  configureSelections();
}

int AbstractFormat::getPrecision() const
{
  return mPrecision;
}

const QString AbstractFormat::getDisplayValue() const
{
  QString displayValue(generateString());

  if (mSeparator == Comma)
    displayValue.replace(
    QLatin1String("."),
    QLatin1String(","));

  QString hemisphereTypeChar(mPlusHsphChar);
  if (mHemisphereType == Minus)
    hemisphereTypeChar = mMinusHsphChar;

  if (mHsphChrPosition == Prefix)
  {
    displayValue.prepend(QLatin1Char(' '));
    displayValue.prepend(hemisphereTypeChar);
  }
  else
  {
    displayValue.append(QLatin1Char(' '));
    displayValue.append(hemisphereTypeChar);
  }

  return displayValue;
}

void AbstractFormat::pressed(int num)
{
  // Игнорируем нажатие клавиш, если выделено поле Тип полусферы
  if (((mHsphChrPosition == Prefix) && (mSelected > 0)) ||
    ((mHsphChrPosition == Suffix) && (mSelected != mSelections.count() - 1)))
    pressed(getSelectedIndex(), num);
}

void AbstractFormat::increaseValue()
{
  if (((mHsphChrPosition == Prefix) && (mSelected > 0)) ||
    ((mHsphChrPosition == Suffix) && mSelected != mSelections.count() - 1))
    increase(getSelectedIndex());
  else
    mHemisphereType = ((mHemisphereType == Plus) ? Minus : Plus);
}

void AbstractFormat::decreaseValue()
{
  if (((mHsphChrPosition == Prefix) && (mSelected > 0)) ||
    ((mHsphChrPosition == Suffix) && (mSelected != mSelections.count() - 1)))
    decrease(getSelectedIndex());
  else
    mHemisphereType = ((mHemisphereType == Plus) ? Minus : Plus);
}

int AbstractFormat::getSelectedIndex() const
{
  int selectedIndex = mSelected;
  if (mHsphChrPosition == Prefix)
    if (selectedIndex > 0)
      selectedIndex -= 1;
  return selectedIndex;
}

void AbstractFormat::configureSelections()
{
  mSelections.clear();
  mSelections = generateSelections();

  const int specificSymbolLength = 1;
  const int spaceSymbolLength = 1;

  // Вычисление длины поля тип полусферы
  const int hemisphereFieldLength = mPlusHsphChar.length();

  if (mHsphChrPosition == Prefix)
  {
    // Двигаем стартовые позиции текущих выделений
    for (int i = 0; i < mSelections.count(); ++i)
      mSelections[i].startPosition += (hemisphereFieldLength + spaceSymbolLength);
    mSelections.prepend(Selection(0, hemisphereFieldLength));
  }
  else
  {
    const int hemisphereFieldLStart =
      mSelections.last().startPosition +
      mSelections.last().length +
      spaceSymbolLength +
      specificSymbolLength;
    mSelections.append(Selection(hemisphereFieldLStart, hemisphereFieldLength));
  }
}

void AbstractFormat::moveSelectionTo(int pos)
{
  // По умолчанию выделение на первый элемент
  mSelected = 0;

  for (int i = 0; i < mSelections.count(); ++i)
  {
    if (pos >= mSelections.at(i).startPosition &&
      pos <= (mSelections.at(i).startPosition +
      mSelections.at(i).length))
    {
      mSelected = i;
      break;
    }
  }
}

void AbstractFormat::moveSelectionRight()
{
  if (mSelected != (mSelections.count() - 1))
    mSelected += 1;
}

void AbstractFormat::moveSelectionLeft()
{
  if (mSelected > 0)
    mSelected -= 1;
}

const Selection AbstractFormat::getCurrentSelection()
{
  return mSelections.at(mSelected);
}

void AbstractFormat::setDesignationHemisphereType(const QString &plusChr,
  const QString &minusChr,
  HemisphereCharPosition position)
{
  mPlusHsphChar = plusChr;
  mMinusHsphChar = minusChr;
  mHsphChrPosition = position;
  configureSelections();
}

} // !Geo

// Возвращает количество символов в числе
int HowManyChars(int x)
{
  int k = 1;
  int n = 0;
  while (x / k != 0) {
    ++n;
    k *= 10;
  }
  return n;
}
