#include <QApplication>

#include <Geo/PointEdit.hpp>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    Geo::PointEdit pointEdit;
    pointEdit.show();
    return app.exec();
}
