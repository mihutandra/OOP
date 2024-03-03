#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QKeyEvent>
#include "SongController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(SongController &ctrl,QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onAddClicked();
    void onDeleteClicked();
    void onViewLyricsClicked();
    void onGenerateRandomClicked();
    void onClearClicked();

    void sortByTitleClicked();
    void sortByArtistClicked();

    void updateTableWidget();
    void filter_updateTableWidget(std::vector<Song>);

    void keyPressEvent(QKeyEvent *event);

    void clearInputFields();

private:
    Ui::MainWindow *ui;
    SongController &ctrl;
    Repo _repo;

    QHBoxLayout* main_layout;

    QLabel* title_list_l;
    QLabel* title_list_r;
    QTableWidget* list_l;
    QListWidget  *list_r;

    QFormLayout* form_layout;
    QFormLayout* form_layout_right;
    QVBoxLayout* add_layout;

    QLabel* add_song_artist;
    QLabel* add_song_title;
    QLabel* add_song_Year;
    QLabel* add_song_lyrics;
    QLabel* add_song_url;
    QLabel* nr_songs_playlist;


    QLineEdit* add_song_artist_LE;
    QLineEdit* add_song_title_LE;
    QLineEdit* add_song_lyrics_LE;
    QLineEdit* add_song_year_LE;
    QLineEdit* add_song_url_LE;
    QLineEdit* nr_songs_playlist_LE;

    QPushButton* add_song_button;
    QPushButton* random_button;
    QPushButton* next_song_button;
    QPushButton* delete_song_button;
    QPushButton* clear_song_button;
    QPushButton* sign_button;
    QPushButton* filter_byArtist_button;
    QPushButton* filter_byTitle_button;
    QPushButton* viewLyrics_button;

    QVBoxLayout* left_vertical_layout;
    QVBoxLayout* right_vertical_layout;
    QVBoxLayout* sign_layout;
    QGridLayout * grid;
    QGridLayout * grid_r;

};

#endif // MAINWINDOW_H
