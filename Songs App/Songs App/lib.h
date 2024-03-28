#pragma once


#include<iostream>
using std::string;

struct Song;
void addSongManually(Song*& songs, int& count); // ��� ���������� ����� ������� � ������ ����� 
void loadSongFromFile(Song*& songs, int& count); // ��������� ����� �� ����� � ��������� �� � ������ ����� 
void addSong(Song*& songs, int& count, const Song& newSong); // ��������� ����� ����� (newSong) � ������ �����
void displaySongs(const Song* songs, int count); // ���������� ������ ���� �����, ������������ � �������
void editSong(Song* songs, int count); // ��������� ������������� ���������� � ����� � �������
void deleteSong(Song*& songs, int& count); // ������� ����� �� �������
void saveSongToFile(const Song* songs, int count); // ��������� ��� ����� �� ������� songs � ��������� ����.
void searchByAuthor(const Song* songs, int count); // ���� ����� �� ����� ������ � �������
void searchByWord(const Song* songs, int count); // ��������� ����� ����� �� ��������� ����� � ������ �����.
void printLyrics(const Song* songs, int count); //  ���������� ������ �������� ����� �� ������� 
bool isSongExists(const Song* songs, int count, const Song& newSong); // ���������, ���������� �� ����� newSong � ������� songs
bool isNumber(const string& str); // ���������, �������� �� ������ str ������.
void pauseScreen(); // ���������������� ���������� ��������� � ������� ����� ������������ ��� �����������.