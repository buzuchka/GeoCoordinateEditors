#include "CoordinateVectorEdit.hpp"

#include <Geo/PointEdit.hpp>

#include <QGridLayout>
#include <QHeaderView>

namespace Geo {

CoordinateVectorEdit::CoordinateVectorEdit(int vertexCount, QWidget * parent)
  : QTableWidget(vertexCount, 1, parent),
    m_readonlyFlag(false)
{
  //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  horizontalHeader()->setStretchLastSection(true);
  setSelectionMode(QAbstractItemView::NoSelection);

  setVertexCount(vertexCount);

  // Установка ширины виджета по ширине виджета редактора точки.
  // Добавлено 10% из-за нумерации строк в таблице.
  setMinimumWidth(PointEdit().minimumWidth() * 1.1);
}

PointEdit* CoordinateVectorEdit::getGeoPoint(int index)
{
  PointEdit *pointEdit = 0;

  // если еще нет точек
  if (rowCount() == 0)
    return pointEdit;

  // организуем зацикливание
  // - при запросе точки с отрицательным индексом  - выдадим последнюю
  // с большим максимального - выдаем 0ую
  if (index >= rowCount())
    index = 0;
  if (index < 0)
    index = rowCount();
  pointEdit = dynamic_cast<PointEdit*> (cellWidget(index,0));
  return pointEdit;
}

void CoordinateVectorEdit::setReadOnly(bool flag)
{
  m_readonlyFlag = flag;
}

void CoordinateVectorEdit::setVertexCount(int count)
{
  int oldCount = rowCount();

  QStringList headers;
  headers.append(tr("Координаты вершин"));
  setHorizontalHeaderLabels(headers);

  setRowCount(count);
  emit vertexCountChanged(count);

  qreal lastLat = 0, lastLon = 0;
  PointEdit *lastVertex = dynamic_cast<PointEdit *>(cellWidget(oldCount - 1, 0));
  if (lastVertex)
  {
    lastLat = lastVertex->getDecimalDegreesLatitude();
    lastLon = lastVertex->getDecimalDegreesLongitude();
  }
  for (int i = oldCount; i < count; i++)
  {
    PointEdit *pointEdit = new PointEdit(false, this);
    pointEdit->setReadOnly(m_readonlyFlag);
    connect(pointEdit, SIGNAL(changed(double, double)), this, SLOT(onPointChanged()));

    setCellWidget(i, 0, pointEdit);

    // Для возможности редактировать значения в виджетах
    // с использованием колесика мыши
    setFocusProxy(pointEdit);

    if (lastVertex)
    {
      pointEdit->setDecimalDegreesLatitude(lastLat);
      pointEdit->setDecimalDegreesLongitude(lastLon);
    }
  }

  // организуем навигацию между точками
  for (int i = oldCount; i < count; i++)
  {
    PointEdit *pointEdit = getGeoPoint(i);
    PointEdit *prevPoint = getGeoPoint(i - 1);
    if (prevPoint)
    {
      connect(pointEdit, SIGNAL(prevLat()), prevPoint, SLOT(focusLatEditAtStart()));
      connect(pointEdit, SIGNAL(prevLon()), prevPoint, SLOT(focusLonEditAtStart()));
      connect(prevPoint, SIGNAL(nextLat()), pointEdit, SLOT(focusLatEditAtStart()));
      connect(prevPoint, SIGNAL(nextLon()), pointEdit, SLOT(focusLonEditAtStart()));
    }
  }

  setVisible(true);
}

void CoordinateVectorEdit::onPointChanged()
{
  emit dataChanged(getData());
}

CoordinateVector CoordinateVectorEdit::getData()
{
  CoordinateVector vector;
  int vertexCount = rowCount();
  for (int i = 0; i < vertexCount; i++)
  {
    PointEdit * point = dynamic_cast<PointEdit*>(cellWidget(i, 0));
    if (point)
      vector.push_back(Coordinate(
                         point->getDecimalDegreesLatitude(),
                         point->getDecimalDegreesLongitude()));
  }
  return vector;
}

void CoordinateVectorEdit::setData(const CoordinateVector &vector)
{
  int vertexCount = (int)vector.size();
  setVertexCount(vertexCount);
  for (int i = 0; i < vertexCount; i++)
  {
    Coordinate coordinate(vector.at(i));
    PointEdit * pointEdit = dynamic_cast<PointEdit*>(cellWidget(i, 0));
    if (pointEdit)
    {
      pointEdit->setDecimalDegreesLatitude(coordinate.latitude());
      pointEdit->setDecimalDegreesLongitude(coordinate.longitude());
    }
  }
}

}
