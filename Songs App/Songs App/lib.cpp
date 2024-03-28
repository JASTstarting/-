#include "lib.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

struct Song {
    string title;
    string author;
    string lyrics;
    int year = 0;
};

bool isSongExists(const Song* songs, int count, const Song& newSong) {
    for (int i = 0; i < count; ++i) {
        if (songs[i].title == newSong.title && songs[i].author == newSong.author && songs[i].year == newSong.year) {
            return true; // ����� ��� ����������
        }
    }
    return false; // ����� ���������
}

void pauseScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ������ ���� ������
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "������� Enter, ����� ����������...";
    cin.ignore();
    cin.get();
}

void addSongManually(Song*& songs, int& count) {
    Song newSong; // ������� ����� ������ Song, ���� ���������� ����� �����
    cout << "������� �������� �����: ";
    getline(cin, newSong.title);

    cout << "������� ������ �����: ";
    getline(cin, newSong.author);

    string yearInput;
    cout << "������� ��� �������� ����� (0 ���� ����������): ";
    // ��������� �������� �� ��������� �������� ������
    while (true) {
        getline(cin, yearInput);
        if (isNumber(yearInput)) {
            // ���� ������� ������ �������� ������, ����������� � � int
            newSong.year = stoi(yearInput);
            break; // ������� �� �����, ��� ��� �������� ���������� ����
        }
        else {
            cout << "������������ ����. ����������, ����������� ������ �����: ";
        }
    }

    cout << "������� ����� �����: ";
    getline(cin, newSong.lyrics);

    // �������� �� ������������� �����
    if (isSongExists(songs, count, newSong)) {
        cout << "����� � ����� ���������, ������� � ����� ��� ����������. ���������� ��������." << endl;
    }
    else {
        // ���� ����� ���������, ��������� �
        addSong(songs, count, newSong);
    }
}

void loadSongFromFile(Song*& songs, int& count) {
    string filename;
    cout << "������� ��� ����� ��� ��������: ";
    getline(cin, filename);

    filename += ".txt"; // ��������� ���������� �����
    cout << endl;
    // ��������� ���� ��� ������
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ����." << endl;
        return;
    }

    // ������ ������ � ����� �� �����
    Song newSong;
    getline(file, newSong.title); // ��������� ��������
    getline(file, newSong.author); // ��������� ������
    file >> newSong.year; // ��������� ���

    // ��������� ����� ����� �� ����� �����
    string line;
    while (getline(file, line)) {
        newSong.lyrics += line + "\n"; // ��������� ������ ������ � ������ �����
    }
    file.close();
    // ��������� ���� �� ��� ����� �����
    if (isSongExists(songs, count, newSong)) {
        cout << "����� '" << newSong.title << "' ��� ����������. �������� ��������." << endl;
    }
    else {
        addSong(songs, count, newSong);
        cout << "����� '" << newSong.title << "' ��������� �� ����� '" << filename << "'." << endl;
    }
}

void addSong(Song*& songs, int& count, const Song& newSong) {
    // ������ �������� �� ������� ���������� �����
    if (isSongExists(songs, count, newSong)) {
        cout << "����� ����� ��� ����������. ���������� ��������." << endl;
        return;
    }
    // ������� ��������� ������ ����� �� ���� ������ ������
    Song* temp = new Song[count + 1];

    // �������� ������������ ����� �� ��������� ������� �� ���������
    for (int i = 0; i < count; ++i) {
        temp[i] = songs[i];
    }
    temp[count] = newSong; // ��������� ����� ����� � ����� ���������� �������

    delete[] songs;
    songs = temp; // ��������� ��������� �� ����� ������ ����� � ���������� songs
    count++;

    cout << "����� '" << newSong.title << "' ������� ���������." << endl;
}

void displaySongs(const Song* songs, int count) {
    // �������� �� ������� ����� � ��������
    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }
    // ������� ������ ����� �� �����
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ": " << "�������� �����: " << songs[i].title << " (����� �����: " << songs[i].author;
        if (songs[i].year != 0) {
            cout << ", ��� ��������: " << songs[i].year;
        }
        cout << ")" << endl;
    }
}

void editSong(Song* songs, int count) {

    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ": " << "�������� �����: " << songs[i].title << " (����� �����: " << songs[i].author;
        if (songs[i].year != 0) {
            cout << ", ��� ��������: " << songs[i].year;
        }
        cout << ")" << endl;
    }
    cout << endl;
    // ����������� � ������������ ����� ����� ��� ��������������
    int songNumber;
    cout << "������� ����� ����� ��� ��������������: ";
    cin >> songNumber;
    // ��������� �� ������������
    if (songNumber < 1 || songNumber > count) {
        cout << "�������� ����� �����." << endl;
        return;
    }
    songNumber--; // ��� ���������� � 1

    // ����������� ����� ������ � ����� 
    cout << "������� ����� �������� �����: ";
    cin.ignore();
    getline(cin, songs[songNumber].title);

    cout << "������� ������ ������ ������: ";
    getline(cin, songs[songNumber].author);

    cout << "������� ����� ��� �������� ����� (0 ���� ����������): ";
    cin >> songs[songNumber].year;
    cin.ignore();

    cout << "������� ����� ����� �����: ";
    getline(cin, songs[songNumber].lyrics);

    cout << "����� ������� ��������" << endl;
}

void deleteSong(Song*& songs, int& count) {

    cout << "������ �����:" << endl;

    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }
    // ����� ������ ����� ����� ���������
    else {
        for (int i = 0; i < count; ++i) {
            cout << i + 1 << ": " << "�������� �����: " << songs[i].title << " (����� �����: " << songs[i].author;
            if (songs[i].year != 0) {
                cout << ", ��� ��������: " << songs[i].year;
            }
            cout << ")" << endl;
        }
        cout << endl;

        int songNumber;
        cout << "������� ����� ����� ��� ��������: ";
        cin >> songNumber;
        cin.ignore(); // ������� ������ ����� ����� cin

        if (songNumber < 1 || songNumber > count) {
            cout << "�������� ����� �����." << endl;
            return deleteSong(songs, count);
        }
        songNumber--; // ��� ���������� � 1

        // ��������� �������� �����, ������� ���������� �������
        string removedSongTitle = songs[songNumber].title;

        // ������� ���������� ����� �� ���� ������� �����, ������ ��������� �����
        for (int i = songNumber; i < count - 1; ++i) {
            songs[i] = songs[i + 1];
        }
        cout << "����� " << removedSongTitle << " ������� �������" << endl;
        count--;
    }
}

void saveSongToFile(const Song* songs, int count) {

    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }

    displaySongs(songs, count); // �������� ������ ����� ��� ������

    cout << "������� ����� ����� ��� ����������: ";
    int songNumber;
    cin >> songNumber;
    cin.ignore(); // ������� ����� ����� ����� �����

    if (songNumber < 1 || songNumber > count) {
        cout << "�������� ����� �����." << endl;
        return;
    }
    songNumber--; // ��� ���������� � 1

    // �������� ������ �� ��������� �����
    const Song& song = songs[songNumber];
    string filename = song.title + ".txt"; // ���������� �������� ����� ��� ��� ����� � ��������� ����������

    // �������� ������������ �������� � ����� �����
    for (char& c : filename) {
        if (c == '\\' || c == '/' || c == ':' || c == '*' || c == '?' || c == '\"' || c == '<' || c == '>' || c == '|') {
            c = '_';
        }
    }

    // ���������, ��� ���� � ����� ������ �� ����������
    string fullPath = filename;
    ifstream testFile(fullPath);
    if (testFile.good()) {
        // ���� ���� ����������, ��������� ��� � ������� ���������
        testFile.close();
        cout << "���� '" << filename << "' ��� ����������. ����� �� ���� ���������." << endl;
        return;
    }

    // ������� � ��������� ���� ��� ������ � ��������� ���������� � �����
    ofstream file(fullPath);
    if (file.is_open()) {
        file << song.title << endl;
        file << song.author << endl;
        file << song.year << endl;
        file << song.lyrics;
        file.close();
        cout << "����� '" << song.title << "' ��������� � ���� '" << filename << "'." << endl << endl;
    }
    else {
        cout << "�� ������� ������� ���� ��� ������." << endl;
    }
}

bool isNumber(const string& str) {
    // ���������, �������� �� ������ ������ ������ ������(� ����� �������� �� ������� ������� c � ������ str)
    for (char const& c : str) {
        if (isdigit(c) == 0) // ���������, �������� �� ������� ������ ������
            return false;  // ���� ������ �� �������� ������, ���������� false
    }
    return true; // // ���� ��� ������� ������ �������� �������, ���������� true
}

void searchByAuthor(const Song* songs, int count) {

    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }

    string author;
    cout << "������� ������ ��� ������: ";
    getline(cin, author);
    cout << endl;
    // ���� ����� ����� ������ ������, �� ������� � �������
    for (int i = 0; i < count; ++i) {
        if (songs[i].author == author) {
            cout << songs[i].title << " (" << songs[i].year << ")" << endl;
            cout << songs[i].lyrics << endl << endl;
        }
    }
}

void searchByWord(const Song* songs, int count) {

    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }

    string word;
    cout << "������� ����� ��� ������ � ������� �����: ";
    getline(cin, word);
    cout << endl;

    // ���� �����,�� ������� �� �������
    for (int i = 0; i < count; ++i) {
        // ���������, ���������� �� ��������� word � ������ ���� �����
        if (songs[i].lyrics.find(word) != string::npos) { // string::npos - ����������, ��� ��������� �� ���� ������� � ������.
            cout << songs[i].title << " (" << songs[i].author << ", " << songs[i].year << ")" << endl;
            cout << songs[i].lyrics << endl << endl;
        }
    }
}

void printLyrics(const Song* songs, int count) {

    if (count == 0) {
        cout << "������� ����." << endl;
        return;
    }

    // ����� ������ ����� ����� �������
    cout << "������ �����:" << endl;
    for (int i = 0; i < count; ++i) {
        cout << i + 1 << ": " << "�������� �����: " << songs[i].title << " (����� �����: " << songs[i].author;
        if (songs[i].year != 0) {
            cout << ", ��� ��������: " << songs[i].year;
        }
        cout << ")" << endl;
    }
    cout << endl;

    int songNumber;
    cout << "������� ����� ����� ��� ������ ������: ";
    cin >> songNumber;
    cout << endl;
    if (songNumber < 1 || songNumber > count) {
        cout << "�������� ����� �����." << endl;
        return;
    }
    songNumber--; // ��� ���������� � 1

    cout << "����� ����� '" << songs[songNumber].title << "':" << endl;
    cout << songs[songNumber].lyrics << endl;
}