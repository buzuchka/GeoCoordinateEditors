#include <QApplication>

#include <Geo/PointEdit.hpp>
#include <Geo/CircleEdit.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    Geo::PointEdit pointEdit;
    pointEdit.show();

    //Geo::CircleEdit circleEdit;
    //circleEdit.show();

    return app.exec();
}
