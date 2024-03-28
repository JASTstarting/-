#pragma once

void Screensaver(); // ���������� ��������� �����(��������)
void Menu(); // ���������� ���� ���� 
void StartNewGame(); // ���������� ������ �� ���� ���������� ����� � ��������
void PlayGame(int row, int col); // �������� ��� ����, ������������ ��������� �������� ������� � ��������� �������.
void CheckMatch(int firstCardRow, int firstCardCol, int secondCardRow, int secondCardCol, int& moves, clock_t startTime, int row, int col); //  ���������, ��������� �� ��� ��������� �����.
void ShowResults(clock_t startTime, int moves); // ���������� ���������� ����.
void InitializeBoard(int row, int col); // �������������� ������� ���� �������.
void AllCardsOpen(int row, int col); // ��������� ��� ����� �� ������� ����.
void PrintBoard(int rows, int columns, int selectedRow, int selectedCol); // ������� ������� ��������� �������� ����.
bool IsGameOver(int row, int col); // ���������, ��������� �� ����.
void SelectCard(int& selectedRow, int& selectedCol, int row, int col, clock_t startTime, int& moves); // ��������� ������ �������� �����.
char GetDirection(); // �������� ���� ����������� �� ������.
void PlaySoundFromProjectFolder(const char* soundName); // ������������� ���� Windows, ��������� ������ �����.