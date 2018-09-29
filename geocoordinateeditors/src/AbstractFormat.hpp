#ifndef GEOCOORDINATEEDITORS_ABSTRACTFORMAT_HPP
#define GEOCOORDINATEEDITORS_ABSTRACTFORMAT_HPP

#include <GeoCoordinateEditors_export.h>

#include <Geo/Format.hpp>

#include <QtCore/QList>
#include <QtCore/QString>

namespace Geo {

/*!
 * \brief Класс выделения
 */
struct GEOCOORDINATEEDITORS_EXPORT Selection
{
  int startPosition; ///< Начальная позиция выделения
  int length;        ///< Длина

  Selection(int pos, int l)
    : startPosition(pos)
    , length(l)
  {}
};

/*!
  * \brief Базовый класс формата для отображения координат
  * \details Осуществляет управление текущим выделением,
  * формирует итоговое строковое представление с учетом типа полусферы,
  * меняет при необходимости символ разделителя дробной части.
  */
class GEOCOORDINATEEDITORS_EXPORT AbstractFormat
{
public:
  // Тип полусферы:
  enum HemisphereType
  {
    Plus,
    Minus
  };

  /*!
  * \brief Инициализация
  * \param decDegValue - десятичное значение градуса,
  * \param precision - количество знаков после запятой,
  * \param useCommaSeparator - флаг использования в качестве разделителя запятой
  */
  AbstractFormat(double decDegValue,
                 int precision = 0,
                 Separator separator = Period);

  virtual ~AbstractFormat();

  /*!
  * \brief Устанавливает точность
  * \param precision - точность (количество знаков после запятой)
  */
  void setPrecision(int precision);

  //! Возвращает точность
  int getPrecision() const;

  /*!
  * \brief Устанавливает текущее выделение в соответствии с позицией курсора
  * \param cursorPosition - позиция курсора
  */
  void moveSelectionTo(int cursorPosition);

  //! Устанавливает текущее выделение на позицию правее
  void moveSelectionRight();

  //! Устанавливает текущее выделение на позицию левее
  void moveSelectionLeft();

  //! Возвращает текущее выделение
  const Selection getCurrentSelection();

  /*!
   * \brief Установка обозначений положительной и отрицательной полусфер
   * \param plusChr - символ для положительной полусферы
   * \param minusChr - символ для отрицательной полусферы
   * \param position - позиция в формате
   */
  void setDesignationHemisphereType(const QString & plusChr,
                                    const QString & minusChr,
                                    HemisphereCharPosition position);

  virtual void setMaxDegrees(int maxDegreesValue){}

  //! Возвращает строковое представление координаты
  const QString getDisplayValue() const;


  virtual void setValue(double decimalDegrees) = 0;
  virtual double getValue() const = 0;

  void pressed(int num);

  //! Увеличить значение в текущей выделенной области
  void increaseValue();

  //! Уменьшить значение в текущей выделенной области
  void decreaseValue();

protected:
  //! Определение списка доступных выделений
  virtual void configureSelections();

  //! Формирование списка доступных выделений
  virtual QList<Selection> generateSelections() const = 0;

  //! Формирование строкового представления координаты
  virtual const QString generateString() const = 0;

  virtual void increase(int field) = 0;
  virtual void decrease(int field) = 0;
  virtual void pressed(int field, int num) = 0;

protected:
  double mDecimalDegreeValue;    ///< Первоначальное значение десятичных градусов
  HemisphereType mHemisphereType;

  int mPrecision;                ///< количество знаков после запятой

private:
  /*!
   * \brief Возвращает индекс текущего выделения
   * \details Скрывает от наследников наличие поля Тип полусферы
   * \return индекс текущего выделения
   */
  int getSelectedIndex() const;

private:
  QList<Selection> mSelections;  ///< Список доступных выделений
  int  mSelected;                ///< Индекс текущего выделения

  QString mPlusHsphChar;         ///< Символ для HemisphereType::Plus
  QString mMinusHsphChar;        ///< Символ для HemisphereType::Minus
  HemisphereCharPosition mHsphChrPosition; ///< Позиция поля Тип полусферы

  Separator mSeparator;          ///< Символ разделителя дробной части числа
};

}

#endif
