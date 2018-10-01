#include "DegreeCoordinateEdit.hpp"

#include <Format_DD.hpp>
#include <Format_DDMM.hpp>
#include <Format_DDMMSS.hpp>

#include <cassert>

#include <QMouseEvent>

namespace Geo {

DegreeCoordinateEdit::DegreeCoordinateEdit(QWidget *parent, Format format)
  : QLineEdit(parent)
  , m_decimalDegrees(0.)
  , m_format(0)
{
  setFormat(format);
}

DegreeCoordinateEdit::~DegreeCoordinateEdit()
{
  delete m_format;
}

void DegreeCoordinateEdit::setDecimalDegreesValue(double decimalDegrees)
{
  m_decimalDegrees = decimalDegrees;
  m_format->setValue(decimalDegrees);
  updateText();
}

double DegreeCoordinateEdit::getDecimalDegreesValue() const
{
  return m_format->getValue();
}

void DegreeCoordinateEdit::setMaxDegrees(const int maxDegreesValue)
{
  m_format->setMaxDegrees(maxDegreesValue);
  updateSize();
  updateText();
}

void DegreeCoordinateEdit::setFormat(Format format,
                                     int precision,
                                     Separator separator)
{
  if(m_format)
    delete m_format;

  switch(format)
  {
  case Geo::DDMMSS:
  {
    m_format = new Format_DDMMSS(m_decimalDegrees, precision, separator);
    break;
  }
  case Geo::DDMM:
  {
    m_format = new Format_DDMM(m_decimalDegrees, precision, separator);
    break;
  }
  case Geo::DD:
  {
    m_format = new Format_DD(m_decimalDegrees, precision, separator);
    break;
  }
  default:
  {
    assert("DegreeCoordinateEdtor::setFormat - Unknown format!");
    break;
  }
  }
  updateSize();

  m_format->setValue(m_decimalDegrees);
  updateText();
}

void DegreeCoordinateEdit::
setDesignationHemisphereType(const QString &plusChr,
                             const QString &minusChr,
                             HemisphereCharPosition position)
{
  m_format->setDesignationHemisphereType(plusChr, minusChr, position);
  updateSize();
  updateText();
}

void DegreeCoordinateEdit::updateSize()
{
  int width =
      fontMetrics().width(QLatin1Char('9')) *
      m_format->getDisplayValue().length() * 0.92;
  setMinimumWidth(width);
}

void DegreeCoordinateEdit::updateText()
{
  setText(m_format->getDisplayValue());
}

void DegreeCoordinateEdit::updateSelection()
{
  Selection selection(m_format->getCurrentSelection());
  QLineEdit::setSelection(selection.startPosition, selection.length);
}

void DegreeCoordinateEdit::focusInEvent(QFocusEvent * e)
{
  QLineEdit::focusInEvent(e);

  m_format->moveSelectionTo(0);

  if (!isReadOnly())
    updateSelection();
}

void DegreeCoordinateEdit::focusOutEvent(QFocusEvent *e)
{
  if (!isReadOnly())
  {
    m_format->moveSelectionTo(0);
    QLineEdit::deselect();
  }
  QLineEdit::focusOutEvent(e);
}

void DegreeCoordinateEdit::mousePressEvent(QMouseEvent *e)
{
  QLineEdit::mousePressEvent(e);
  if (!isReadOnly() && (e->button() & Qt::LeftButton) )
  {
    m_format->moveSelectionTo(cursorPositionAt(e->pos()));
    updateSelection();
  }
}

void DegreeCoordinateEdit::mouseMoveEvent(QMouseEvent *e)
{
  // Чтобы пользователь не мог сбить выделение
  if (isReadOnly())
    QLineEdit::mouseMoveEvent(e);
}

void DegreeCoordinateEdit::keyPressEvent(QKeyEvent *e)
{
  if (isReadOnly())
    QLineEdit::keyPressEvent(e);
  else
  {
    switch (e->key())
    {
    case Qt::Key_Escape:
    case Qt::Key_Enter:
      QLineEdit::keyPressEvent(e);
      break;

      // Ввод данных
    case Qt::Key_0:
      m_format->pressed(0);
      break;
    case Qt::Key_1:
      m_format->pressed(1);
      break;
    case Qt::Key_2:
      m_format->pressed(2);
      break;
    case Qt::Key_3:
      m_format->pressed(3);
      break;
    case Qt::Key_4:
      m_format->pressed(4);
      break;
    case Qt::Key_5:
      m_format->pressed(5);
      break;
    case Qt::Key_6:
      m_format->pressed(6);
      break;
    case Qt::Key_7:
      m_format->pressed(7);
      break;
    case Qt::Key_8:
      m_format->pressed(8);
      break;
    case Qt::Key_9:
      m_format->pressed(9);
      break;

      // Увеличение и уменьшение выделенных значений кнопками
    case Qt::Key_Up:
    case Qt::Key_Plus:
      if (e->modifiers() & Qt::CTRL)
      {
        emit up();
        return;
      }
      m_format->increaseValue();
      break;

    case Qt::Key_Down:
    case Qt::Key_Minus:
      if (e->modifiers() & Qt::CTRL)
      {
        emit down();
        return;
      }
      m_format->decreaseValue();
      break;

    case Qt::Key_Backspace:
    case Qt::Key_Delete:
      m_format->setValue(0);
      break;

      // Перемещеие выделения кнопками
    case Qt::Key_Right:
      if (e->modifiers() & Qt::CTRL)
      {
        emit right();
        return;
      }
      m_format->moveSelectionRight();
      break;
    case Qt::Key_Left:
      if (e->modifiers() & Qt::CTRL)
      {
        emit left();
        return;
      }
      m_format->moveSelectionLeft();
      break;

      // Быстрый переход между соседними виджетами DegreeCoordinateEdit
    case Qt::Key_D:
      emit right();
      return;
    case Qt::Key_A:
      emit left();
      return;
    case Qt::Key_W:
      emit up();
      return;
    case Qt::Key_S:
      emit down();
      return;
    }
  }
  updateText();
  updateSelection();
}

void DegreeCoordinateEdit::wheelEvent(QWheelEvent *event)
{
  if (isReadOnly() || !hasFocus())
    return;

  if (event->orientation() == Qt::Vertical)
  {
    if (event->delta() > 0)
      m_format->increaseValue();
    else
      m_format->decreaseValue();
  }
  updateText();
  updateSelection();

  event->ignore();
}

}
