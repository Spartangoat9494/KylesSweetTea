#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
using namespace std;

const int WIDTH = 20, HEIGHT = 20;
int x, y, foodX, foodY, score;
bool gameOver;
vector<pair<int, int>> snake;
char direction;

void Setup() {
    gameOver = false;
    direction = 'R';
    x = WIDTH / 2;
    y = HEIGHT / 2;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
    score = 0;
    snake.clear();
    snake.push_back({x, y});
}

void Draw() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == foodY && j == foodX)
                cout << "F";
            else {
                bool isBody = false;
                for (auto s : snake)
                    if (s.first == j && s.second == i) {
                        cout << "o";
                        isBody = true;
                    }
                if (!isBody) cout << " ";
            }
            if (j == WIDTH - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w': if (direction != 'D') direction = 'U'; break;
            case 's': if (direction != 'U') direction = 'D'; break;
            case 'a': if (direction != 'R') direction = 'L'; break;
            case 'd': if (direction != 'L') direction = 'R'; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    pair<int, int> prev = snake[0], temp;
    switch (direction) {
        case 'U': y--; break;
        case 'D': y++; break;
        case 'L': x--; break;
        case 'R': x++; break;
    }
    
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) gameOver = true;
    
    for (auto s : snake)
        if (s.first == x && s.second == y) gameOver = true;
    
    snake.insert(snake.begin(), {x, y});
    
    if (x == foodX && y == foodY) {
        score += 10;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
    } else {
        snake.pop_back();
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}
