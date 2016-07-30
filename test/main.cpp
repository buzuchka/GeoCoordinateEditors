#include <QApplication>

#include <degreecoordinateeditor.h>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    DegreeCoordinateEditor coordinateEditor;
    coordinateEditor.show();
    return app.exec();
}
