#include <QApplication>

#include <Geo/CircleEdit.hpp>
#include <Geo/LineringEdit.hpp>
#include <Geo/PointEdit.hpp>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  //Geo::PointEdit pointEdit;
  //pointEdit.show();

  //Geo::CircleEdit circleEdit;
  //circleEdit.show();

  Geo::LineRingEdit lineRingEdit;
  lineRingEdit.show();

  return app.exec();
}
