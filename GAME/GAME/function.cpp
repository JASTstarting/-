#include <iostream>
#include <ctime>
#include <conio.h> // ��� _getch()
#include <cstdlib>
#include <windows.h>
#include <string>
#include "function.h"


using std::cout;
using std::cin;
using std::endl;
using std::swap;
using std::string;

// ���������� ����������
int** board; // ��������� ������ ��� �������� �������� ����
bool** revealed; // ��������� ������ ��� �������� ���������� � ���, ������� �� �����
int moves = 0; // ���������� ����� (����������� ����)


void PlaySoundFromProjectFolder(const char* soundName) {
    char fullPath[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, fullPath); // �������� ������� ����������
    string pathStr(fullPath); // ������������ � string ��� �������� ������ �� ��������

    // ������ ������ ���� � ����� �����
    pathStr += "\\sounds\\";
    pathStr += soundName;

    // ������������ string � std::wstring
    int size_needed = MultiByteToWideChar(CP_ACP, 0, pathStr.c_str(), -1, NULL, 0);
    std::wstring wFullPath(size_needed, 0);
    MultiByteToWideChar(CP_ACP, 0, pathStr.c_str(), -1, &wFullPath[0], size_needed);

    // ������������� ����
    PlaySound(wFullPath.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}

void Screensaver() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ������ ���� ������
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    PlaySoundFromProjectFolder("menu.wav");
    cout << endl << endl;
    cout << "                                              �������� ����..." << endl;
    Sleep(1000);

    system("cls");
    cout << endl << endl;
    cout << "                                 *******************************************" << endl;
    Sleep(500);
    cout << "                                 *       *************************         *" << endl;
    Sleep(500);
    cout << "                                 *       *                       *         *" << endl;
    Sleep(500);
    cout << "                                 *       *       ���� ������     *         *" << endl;
    Sleep(500);
    cout << "                                 *       *                       *         *" << endl;
    Sleep(500);
    cout << "                                 *       *************************         *" << endl;
    Sleep(500);
    cout << "                                 *******************************************" << endl;
    Sleep(2000);

    system("cls");
    cout << endl << endl;
    cout << "                                                 ��������";
    for (int i = 0; i < 5; ++i) {
        Sleep(500);
        cout << ".";
    }
    Sleep(500);
    system("cls");

    cout << endl << endl;
    cout << "                                             ���� ����������!" << endl;
    Sleep(1500);
}

void Menu() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    PlaySoundFromProjectFolder("start.wav");
    system("cls");
    cout << endl << endl;
    cout << "                                         *******************************\n"
        "                                         *                             *\n"
        "                                         *         ���� ����           *\n"
        "                                         *                             *\n"
        "                                         *******************************\n\n"
        "                                         ������� 1, ����� ������ ����� ����\n"
        "                                         ������� 2, ����� �����\n\n"
        "                                               ������� ���� �����: ";

    string input; // �������� �� ������ ��� ���������������� ����������
    int choice;
    getline(cin, input); // ��������� ������ ������ �����

    //  ��������������� ��������� ������ � �����(����������� ��������� ������������ ����������, ������ � ����������� �� � catch)
    try {
        choice = stoi(input); // �������������� ������ � �����
    }
    catch (...) {
        choice = -1; // ���� �������������� �� �������, ������������� choice � ������������ ��������
    }
    cout << endl;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    while (choice != 1 && choice != 2) {

        cout << "����������, �������� ���������� �����.\n";
        Sleep(60);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        cout << "������� ���� �����: ";
        getline(cin, input); // ��������� ������ ������ �����

        try {
            choice = stoi(input); // �������������� ������ � �����
        }
        catch (...) {
            choice = -1; // ���� �������������� �� �������, ������������� choice � ������������ ��������
        }
        cout << endl;
    }

    switch (choice) {

    case 1:
        StartNewGame();
        break;
    case 2:
        cout << "������ �� ����..." << endl;
        Sleep(60);
        exit(0);
    }
}

void StartNewGame() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    int row, col;
    cout << "����������, ������� ���������� ����� � ������� ����: ";
    cin >> row;
    cout << "����������, ������� ���������� �������� � ������� ����: ";
    cin >> col;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    while (row * col % 2 != 0) {

        cout << "������� ���� ������ ����� ������ ���������� ����� � ��������.\n"
            "����������, ������� ���������� ����� � �������� ��� �������� ���� ��� ���.\n";
        Sleep(180);
        cout << "����������, ������� ���������� ����� � ������� ����: ";
        cin >> row;
        cout << "����������, ������� ���������� �������� � ������� ����: ";
        cin >> col;
    }

    InitializeBoard(row, col);
    AllCardsOpen(row, col);
    Sleep(5000);

    PlayGame(row, col);
}

void PlayGame(int row, int col) {

    clock_t startTime = clock();
    int selectedRow = 0, selectedCol = 0; // ��������� ������� ������

    while (!IsGameOver(row, col)) {
        // ����� ������ �����
        SelectCard(selectedRow, selectedCol, row, col, startTime, moves);

        int firstCardRow = selectedRow, firstCardCol = selectedCol; // ��������� ������� ������ ��������� �����

        // ����� ������ �����
        SelectCard(selectedRow, selectedCol, row, col, startTime, moves);

        if (firstCardRow != selectedRow || firstCardCol != selectedCol) {
            CheckMatch(firstCardRow, firstCardCol, selectedRow, selectedCol, moves, startTime, row, col);
        }
        else {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "�� ������� �� �� ����� �����. ����������, �������� ������.\n";
            Sleep(1000); // ���� ����� ��������� ���������
        }
    }

    ShowResults(startTime, moves);
}

void CheckMatch(int firstCardRow, int firstCardCol, int secondCardRow, int secondCardCol, int& moves, clock_t startTime, int row, int col) {

    system("cls"); // ������� ����� ����� ������� �����������
    PrintBoard(row, col, -1, -1); // �������� ����� ��� ������������ ������

    if (board[firstCardRow][firstCardCol] == board[secondCardRow][secondCardCol]) {
        cout << "���������� �������!" << endl;

        PlaySoundFromProjectFolder("tada.wav");

        revealed[secondCardRow][secondCardCol] = true; // ��������� �������� ���������
        revealed[firstCardRow][firstCardCol] = true;
    }
    else {
        cout << "���������� �� �������." << endl;

        PlaySoundFromProjectFolder("chord.wav");

        Sleep(2000); // ��� ����� ������������ ������� ��������

        revealed[firstCardRow][firstCardCol] = false; // ��������� ��������
        revealed[secondCardRow][secondCardCol] = false;
    }
}

void ShowResults(clock_t startTime, int moves) {

    int totalTime = static_cast<int>(clock() - startTime) / CLOCKS_PER_SEC;

    system("cls"); // ������� ����� ����� ������� �����������

    cout << "����������! �� ��������� ����.\n";
    cout << "�� �������� ���� �� " << moves << " �����.\n";
    cout << "����� ����������� �����: " << totalTime << " ������.\n";
    cout << "������� ����� ������� ��� ����������� � ����...";

    _getch(); // ������� ������� ������� �������������, ����� ��������� � ����

    return Menu();
}

void InitializeBoard(int rows, int columns) {

    int area = rows * columns;
    int* numbers = new int[area];

    for (int i = 0; i < area / 2; ++i) {

        numbers[i] = i;
        numbers[i + (area / 2)] = i;
    }

    srand(time(0));

    for (int i = area - 1; i > 0; --i) {

        int j = rand() % (i + 1);
        swap(numbers[i], numbers[j]);
    }

    board = new int* [rows];
    revealed = new bool* [rows];

    for (int i = 0; i < rows; ++i) {

        board[i] = new int[columns];
        revealed[i] = new bool[columns];

        for (int j = 0; j < columns; ++j) {

            board[i][j] = numbers[(i * columns) + j];
            revealed[i][j] = false;
        }
    }
    delete[] numbers;
}

void PrintBoard(int rows, int columns, int selectedRow, int selectedCol) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    const int cardHeight = 5; // ������ ��������
    const int cardWidth = 7; // ������ ��������
    const int spaceBetween = 3; // ���������� ����� ���������� � ������ ���

    int totalHeight = rows * (cardHeight + spaceBetween) + spaceBetween;
    int totalWidth = columns * (cardWidth + spaceBetween) + spaceBetween;

    for (int i = 0; i < totalHeight; ++i) {
        for (int j = 0; j < totalWidth; ++j) {
            int cardRow = i / (cardHeight + spaceBetween);
            int cardCol = j / (cardWidth + spaceBetween);

            // ��������� ������������� ���������� ������ ��������
            int relY = i % (cardHeight + spaceBetween) - spaceBetween;
            int relX = j % (cardWidth + spaceBetween) - spaceBetween;

            bool isCardArea = relY >= 0 && relX >= 0;
            bool isBorder = relY == 0 || relY == (cardHeight - 1) || relX == 0 || relX == (cardWidth - 1);
            bool isCenter = relY == (cardHeight / 2) && relX == ((cardWidth / 2) - 1);

            if (isCardArea) {
                if (cardRow == selectedRow && cardCol == selectedCol && isBorder) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                    cout << "#"; // �������� ������� ��������� ��������
                }
                else if (isBorder) {
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout << "+"; // ������������ ������� ��������
                }
                else if (isCenter && revealed[cardRow][cardCol]) {
                    cout << board[cardRow][cardCol]; // ������� ����� ��������, ���� ��� �������
                }
                else {
                    cout << " "; // ��������� ���������� ������������ ��������                    
                }
            }
            else {
                cout << " "; // ��������� ������������ ����� ����������
            }
        }
        cout << endl;
    }
}

void AllCardsOpen(int rows, int columns) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    for (int i = 0; i < rows; ++i) {
        cout << " " << endl;
        for (int j = 0; j < columns; ++j) {
            cout << board[i][j] << "   ";
        }
        cout << endl;
    }
}

bool IsGameOver(int rows, int columns) {

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (!revealed[i][j]) {
                return false;
            }
        }
    }
    return true;
}

char GetDirection() {

    char c = _getch();
    if (c == -32) { // ��� �������
        c = _getch();
        return c;
    }
    return c;
}

void SelectCard(int& selectedRow, int& selectedCol, int row, int col, clock_t startTime, int& moves) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char direction;

    do {
        system("cls");
        PrintBoard(row, col, selectedRow, selectedCol);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

        cout << "���������� �����������: " << moves << endl;
        cout << "�����: " << static_cast<int>(clock() - startTime) / CLOCKS_PER_SEC << endl;
        cout << "����������� ������� �� ��������� ��� �����������, ������� Enter, ����� ������� �����." << endl;

        direction = GetDirection();

        switch (direction) {
        case 72: // ������� �����
            if (selectedRow > 0) selectedRow--;
            break;
        case 80: // ������� ����
            if (selectedRow < row - 1) selectedRow++;
            break;
        case 75: // ������� �����
            if (selectedCol > 0) selectedCol--;
            break;
        case 77: // ������� ������
            if (selectedCol < col - 1) selectedCol++;
            break;
        case 13: // Enter
            if (!revealed[selectedRow][selectedCol]) {
                revealed[selectedRow][selectedCol] = true; // ��������� ��������
                moves++; // ����������� ���������� �����
            }
            else {
                cout << "��� �������� ��� �������. �������� ������." << endl;
                Sleep(1000); // ���� ����� ��������� ���������
            }
            break;
        }
    } while (direction != 13); // ���������, ���� �� ����� ����� Enter
}