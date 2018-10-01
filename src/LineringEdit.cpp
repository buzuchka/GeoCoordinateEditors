#include "Geo/LineringEdit.hpp"

#include "CoordinateVectorEdit.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

namespace Geo {

LineRingEdit::LineRingEdit(QWidget * parent, Qt::WindowFlags flags)
  : QWidget(parent,flags)
  , mCoordinateVectorEdit(new CoordinateVectorEdit(0, this))
  , mVertexCountSpinBox(new QSpinBox(this))
{
  connect(mCoordinateVectorEdit, SIGNAL(dataChanged(CoordinateVector)),
          this, SIGNAL(dataChanged(CoordinateVector)));

  mVertexCountSpinBox->setMinimum(0);

  connect(mVertexCountSpinBox, SIGNAL(valueChanged(int)),
          mCoordinateVectorEdit, SLOT(setVertexCount(int)));
  connect(mCoordinateVectorEdit, SIGNAL(vertexCountChanged(int)),
          mVertexCountSpinBox, SLOT(setValue(int)));
  connect(mCoordinateVectorEdit, SIGNAL(vertexCountChanged(int)),
          this, SLOT(onVertexCountChanged()));

  QHBoxLayout *vertexCountLayout = new QHBoxLayout;
  vertexCountLayout->addWidget(
        new QLabel(QObject::tr("Количество вершин:"), this));
  vertexCountLayout->addWidget(mVertexCountSpinBox);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addLayout(vertexCountLayout);
  mainLayout->addWidget(mCoordinateVectorEdit);

  mainLayout->setAlignment(Qt::AlignCenter);
  mainLayout->setContentsMargins(0, 0, 0, 0);

}

void LineRingEdit::setData(const CoordinateVector &vector)
{
  mCoordinateVectorEdit->setData(vector);
}

CoordinateVector LineRingEdit::getData()
{
  return mCoordinateVectorEdit->getData();
}

void LineRingEdit::setReadOnly(bool flag)
{
  mVertexCountSpinBox->setReadOnly(flag);
  mCoordinateVectorEdit->setReadOnly(flag);
}

void LineRingEdit::clear()
{
  mCoordinateVectorEdit->setData(CoordinateVector());
}

void LineRingEdit::setMaximum(unsigned int value)
{
  mVertexCountSpinBox->setMaximum(value);
}

void LineRingEdit::onVertexCountChanged()
{
  emit dataChanged(mCoordinateVectorEdit->getData());
}

}
