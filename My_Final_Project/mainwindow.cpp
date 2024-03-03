#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "SongException.h"
#include <QMessageBox>
#include <sstream>
#include "Playlist.h"
#include <random>

MainWindow::MainWindow(SongController &c,QWidget *parent)
    : QMainWindow(parent), ctrl{c}
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->main_layout = new QHBoxLayout{this->centralWidget()};
    this->left_vertical_layout = new QVBoxLayout{};
    this->right_vertical_layout = new QVBoxLayout{};
    this->list_l = new QTableWidget{this->centralWidget()};
    this->list_r = new QListWidget{this->centralWidget()};

    this->sign_button = new QPushButton(">");
    this->main_layout->addLayout(this->left_vertical_layout);
    this->main_layout->addWidget(sign_button);
    this->main_layout->addLayout(this->right_vertical_layout);

    this->title_list_l = new QLabel{"Playlist"};
    this->left_vertical_layout->addWidget(this->title_list_l);
    this->left_vertical_layout->addWidget(this->list_l);

    this->title_list_r = new QLabel{"Lyrics"};
    this->right_vertical_layout->addWidget(this->title_list_r);
    this->right_vertical_layout->addWidget(this->list_r);


    this->form_layout = new QFormLayout{};
    this->add_layout = new QVBoxLayout{};
    this->add_layout->addLayout(this->form_layout);

    this->add_song_artist = new QLabel{"Artist :"};
    this->add_song_artist_LE = new QLineEdit{};

    this->add_song_title = new QLabel{"Title:"};
    this->add_song_title_LE = new QLineEdit{};

    this->add_song_Year = new QLabel{"Year:"};
    this->add_song_year_LE = new QLineEdit{};

    this->add_song_url = new QLabel{"URL:"};
    this->add_song_url_LE = new QLineEdit{};

    this->add_song_lyrics = new QLabel{"Lyrics:"};
    this->add_song_lyrics_LE = new QLineEdit{};



    this->add_song_button = new QPushButton("Add");
    this->delete_song_button = new QPushButton("Delete");
    this->clear_song_button = new QPushButton("Clear");
    this->filter_byArtist_button = new QPushButton("Sort by Artist");
    this->filter_byTitle_button = new QPushButton("Sort by Title");
    this->viewLyrics_button = new QPushButton("View Lyrics");
    this->random_button = new QPushButton("Random Playlist");


    this->form_layout->addRow(this->add_song_title,this->add_song_title_LE);
    this->form_layout->addRow(this->add_song_artist,this->add_song_artist_LE);
    this->form_layout->addRow(this->add_song_Year,this->add_song_year_LE);
    this->form_layout->addRow(this->add_song_url,this->add_song_url_LE);
    this->form_layout->addRow(this->add_song_lyrics,this->add_song_lyrics_LE);


    QGridLayout * grid = new QGridLayout{};
    grid->addWidget(add_song_button, 0, 0);
    grid->addWidget(delete_song_button, 0, 1);
    grid->addWidget(clear_song_button, 0, 2);
    grid->addWidget(filter_byArtist_button, 1, 0);
    grid->addWidget(filter_byTitle_button, 1, 1);
    grid->addWidget(viewLyrics_button, 1, 2);

    this->form_layout_right = new QFormLayout{};
    this->nr_songs_playlist = new QLabel{"How many songs shoul be in the new playlist?"};
    this->nr_songs_playlist_LE = new QLineEdit{};
    this->form_layout_right->addRow(this->nr_songs_playlist,this->nr_songs_playlist_LE);
    this->right_vertical_layout->addLayout(this->form_layout_right);


    this->add_layout->addLayout(grid);
    this->right_vertical_layout->addWidget(this->random_button);
    this->add_layout->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    this->left_vertical_layout->addLayout(this->add_layout);
    this->right_vertical_layout->addLayout(this->add_layout);


    connect(add_song_button, &QPushButton::clicked,
            this, &MainWindow::onAddClicked);

    connect(delete_song_button, &QPushButton::clicked,
            this, &MainWindow::onDeleteClicked);

    connect(filter_byTitle_button, &QPushButton::clicked,
            this, &MainWindow::sortByTitleClicked);

    connect(filter_byArtist_button, &QPushButton::clicked,
            this, &MainWindow::sortByArtistClicked);

    connect(viewLyrics_button, &QPushButton::clicked,
            this, &MainWindow::onViewLyricsClicked);

    connect(random_button, &QPushButton::clicked,
            this, &MainWindow::onGenerateRandomClicked);

    connect(clear_song_button, &QPushButton::clicked,
            this, &MainWindow::onClearClicked);


}

void MainWindow::updateTableWidget()
{
    list_l->clear();
    const std::vector<Song> &allSonga = ctrl.get_all_songs();

    list_l->setColumnCount(2);
    list_l->setRowCount(allSonga.size());
    list_l->setHorizontalHeaderLabels({"Artist","Title"});
    int row =  0;
    for(auto& p: allSonga)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(p.get_artist().c_str());
        list_l->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(p.get_title().c_str());
        list_l->setItem(row, 1, newItem);

        row++;
    }
}

void MainWindow::clearInputFields()
{
    add_song_title_LE->clear();
    add_song_artist_LE->clear();
    add_song_lyrics_LE->clear();
    add_song_url_LE->clear();
    add_song_year_LE->clear();
    nr_songs_playlist_LE->clear();
}

void MainWindow::onAddClicked()
{
    std::string title = add_song_title_LE->text().toStdString();
    std::string artist = add_song_artist_LE->text().toStdString();
    int year = add_song_year_LE->text().toInt();
    std::string url = add_song_url_LE->text().toStdString();
    std::vector<std::string> lyrics;
    std::string inputLyrics = add_song_lyrics_LE->text().toStdString();

    // Split the input lyrics into individual lines
    std::istringstream iss(inputLyrics);
    std::string line;
    while (std::getline(iss, line))
    {
        lyrics.push_back(line);
    }

    try
    {
        ctrl.add_song(title,artist,year,url,lyrics);
        updateTableWidget();
        clearInputFields();
    }
    catch (const SongException& ex)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ex.what()));
    }

    qDebug()<<"clicked";
}

void MainWindow::onDeleteClicked()
{
    std::string title = add_song_title_LE->text().toStdString();
    std::string artist = add_song_artist_LE->text().toStdString();
    int year = add_song_artist_LE->text().toInt();


    Song newSong(title,artist,year);
    try
    {
        ctrl.remove(newSong);
        updateTableWidget();
        clearInputFields();
    }
    catch (const SongException& ex)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ex.what()));
    }

    qDebug()<<"clicked";
}

void MainWindow::onClearClicked()
{
    list_l->clear();
    ctrl.clear();
    list_l->setColumnCount(0);
    list_l->setRowCount(0);
}

void MainWindow::onViewLyricsClicked()
{
    list_r->clear();

    std::string title = add_song_title_LE->text().toStdString();
    std::string artist = add_song_artist_LE->text().toStdString();
    Song newSong{ctrl.search_song(title,artist)};

   try
    {
        for (const std::string& str : newSong.get_lyrics())
        {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(str));
            list_r->addItem(item);
        }
        clearInputFields();
    }
    catch (const SongException& ex)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ex.what()));
    }
}


void init_dataBase(std::vector<Song>& dataBase)
{
    Song s1("My Wonderful","Jessica Simpson",1999,
            "https://www.youtube.com/watch?v=-tU-aW-oqsk",
            {"A time when I was down and out", "No lovin in my life","this angel came and brought about"});
    Song s2("Just Because","John Lennon",1985,
            "https://iuhp0ojp_ykuygku",
            {"''Ah, remember this?", "Why, I must have been thirteen when this came out!", "Or was it fourteen?"});
    Song s3("Heart-Shaped Box","Nirvana",2000,
            "https://www.youtube.com/watch?v=by6lyNC3D9Y",
            {"Are we rolling?","She eyes me like a Pisces when I am weak","I've been buried in a heart-shaped box for weeks"});
    Song s4("Seven Years In Tibet","David Bowie",1997,
            "https://www.youtube.com/watch?v=9ORAPdqpsRg",
            {"You've been shot in the head","And I'm holding your brains","The old woman said","So I drink in the shadows"});

    Song s5("Better Man", "5 Seconds of Summer",2018,
            "https://www.youtube.com/watch?v=oase9QzyxyY",
            {"Find me at a quarter to three, cigarette in my hand","I'd be at every party, I wouldn't miss a chance",
               "New friends again and again, gone when the morning comes"});

    Song s6("I Fall Apart", "Post Malone",2016,
            "https://www.youtube.com/watch?v=0sHKUpOVMO0",
            {"Oooh, I fall apart","Oooh, yeah, mmhmm","She told me that I'm not enough, yeah","And she left me with a broken heart, yeah"});

    Song s7("Blue on Black","Five Finger Death Punch",2018,
            "https://www.youtube.com/watch?v=IMCfSjF_vSg",
            {"Night falls and I'm alone", "Skin, yeah, chilled me to the bone","You turned and you ran, oh yeah"," Oh oh, slipped right from my hand"});

    Song s8("Mestecanis","Bucovina",2006,
            "https://www.youtube.com/watch?v=0y-bbtYaY_c",
            {"Cântare munţilor cărunţi","Care cu-a lor creste sprijină cerul","Şi-a lor codri neumblaţi","Tainic leagăn unde ne-am născut."});

    Song s9("Snuff","Slipknot", 2010,
            "https://www.youtube.com/watch?v=LXEKuttVRIo",
            {"Bury all your secrets in my skin","Come away with innocence, and leave me with my sins",
             "Come away with innocence, and leave me with my sins", "The air; around me still feels like a cage",
             "And love is just a camouflage for what resembles rage again"});
    Song s10("Stressed Out", "21 Pilots", 2015,
             "https://www.youtube.com/watch?v=jkuIUHIL-PJH",
             {"I wish I found some better sounds no one's ever heard","I wish I had a better voice that sang some better words"});

    dataBase.push_back(s1);
    dataBase.push_back(s2);
    dataBase.push_back(s3);
    dataBase.push_back(s4);
    dataBase.push_back(s5);
    dataBase.push_back(s6);
    dataBase.push_back(s7);
    dataBase.push_back(s8);
    dataBase.push_back(s9);
    dataBase.push_back(s10);
}


void MainWindow::onGenerateRandomClicked()
{
    list_l->clear();

    int nrSongs = nr_songs_playlist_LE->text().toInt();
    std::vector<Song> dataBase;
    init_dataBase(dataBase);
    Playlist _playlist;
    //initialize vector with file data
    Playlist newPlaylist = _playlist.generateRandom(nrSongs,dataBase);

    for(int i = 0; i<newPlaylist.get_playlist().size(); i++)
    {
        try
        {
            ctrl.add_song(newPlaylist.get_playlist()[i].get_title(),newPlaylist.get_playlist()[i].get_artist(),
                          newPlaylist.get_playlist()[i].get_year(),newPlaylist.get_playlist()[i].get_url(),
                          newPlaylist.get_playlist()[i].get_lyrics());
            updateTableWidget();
            clearInputFields();
        }
        catch (const SongException& ex)
        {
            QMessageBox::warning(this, "Error", QString::fromStdString(ex.what()));
        }
    }
}


void MainWindow::filter_updateTableWidget(std::vector<Song> sortedList)
{
    list_l->clear();
    const std::vector<Song> &allPets = sortedList;

    list_l->setColumnCount(2);
    list_l->setRowCount(allPets.size());
    int row =  0;
    for(auto& p: allPets)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(p.get_artist().c_str());
        list_l->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(p.get_title().c_str());
        list_l->setItem(row, 1, newItem);

        row++;

    }

}

void MainWindow::sortByTitleClicked()
{
    bool ascending = true;

    filter_updateTableWidget(ctrl.sortByTitle(ascending));

    qDebug()<<"clicked";
}

void MainWindow::sortByArtistClicked()
{
    bool ascending = true;

    filter_updateTableWidget(ctrl.sortByArtist(ascending));

    qDebug()<<"clicked";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Z){
        qDebug()<<"key pressed CTRL+Z";
        ctrl.undo();
        updateTableWidget();
    }
    else
    {
        if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Y){
            qDebug()<<"key pressed CTRL+Y";
            ctrl.redo();
            updateTableWidget();
        }
    }
}

MainWindow::~MainWindow()
{
    //delete ui;
}

