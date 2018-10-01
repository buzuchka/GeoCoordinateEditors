#ifndef GEOCOORDINATEEDITORS_FORMAT_HPP
#define GEOCOORDINATEEDITORS_FORMAT_HPP

namespace Geo {

/*!
  * \brief Перечисление доступных форматов для отображения координат в PointEdit.
  */
enum Format
{
  DDMMSS,
  DDMM,
  DD
};

/*!
  * \brief Перечисление позиций символа Тип полусферы
  * для отображения координат в PointEdit.
  */
enum HemisphereCharPosition
{
  Prefix, // перед числом
  Suffix  // после числа
};

/*!
  * \brief Перечисление доступных разделителей дробной части числа
  *  для отображения координат в PointEdit.
  */
enum Separator
{
  Period, // точка
  Comma   // запятая
};

}

#endif
