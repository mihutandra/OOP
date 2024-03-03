#include "mainwindow.h"

#include <QApplication>
#include "TestRepo.h"
#include "TestSongController.h"
#include "TestFileRepo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repo repo;
    SongController ctrl{repo};
    MainWindow w{ctrl};
    w.show();
    TestRepo::TestAllRepo();
    TestSongController::testAllSongController();
    TestFileRepo::testAllFileRepo();
    return a.exec();
}
