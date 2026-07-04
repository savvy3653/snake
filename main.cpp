#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <random>
//
#define X 1
#define Y 7

struct Player {
    int x;
    int y;
};

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

void draw(const auto& vfxArr);

int main(int agrc, char** argv) {
    Player player = {X, Y};
    int appleX, appleY;

    std::vector<std::string> vfxArr = {
        "################################",
        "#                              #",
        "#                              #",
        "#                              #",
        "#                              #",
        "#                              #",
        "#                              #",
        "#                              #",
        "################################"
    };
    vfxArr[player.y][player.x] = '0';
    int count = 0; int max = 2;
    Direction direction = Direction::UP;
    std::vector<std::pair<int, int>> positions = {{player.y, player.x}};

    // Randomizer
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribX(1, 30);
    std::uniform_int_distribution<int> distribY(1, 7);

    auto randomizer = [&]() {
        while (true) {
            bool occupied = false;
            appleX = distribX(gen);
            appleY = distribY(gen);
            if (vfxArr[appleY][appleX] == '0') occupied = true;
            if (!occupied) break;
        }
        vfxArr[appleY][appleX] = 'o';
    };
    auto reset = [&]() {
        for (auto& i : positions) {
            vfxArr[i.first][i.second] = ' ';
        }
        positions.clear();
        positions = {{player.y, player.x}};
        player = {X, Y};
        count = 0; max = 2;
        system("cls");
        draw(vfxArr);
        direction = Direction::UP;
        vfxArr[appleY][appleX] = ' ';
        randomizer();
    };
    randomizer();
    while (true) {
        system("cls");
        draw(vfxArr);
        if (_kbhit()) {
            int c = _getch();
            switch (c) {
                case 'w':
                    direction = Direction::UP;
                    break;
                case 'a':
                    direction = Direction::LEFT;
                    break;
                case 's':
                    direction = Direction::DOWN;
                    break;
                case 'd':
                    direction = Direction::RIGHT;
                    break;
            }
        }
        switch (direction) {
            case UP:
                if (vfxArr[player.y-1][player.x] != '#' && vfxArr[player.y-1][player.x] != '0') {
                    player.y--;
                    if (vfxArr[player.y][player.x] == 'o') {
                        max += 1;
                        randomizer();
                    }
                } else reset();
                break;
            case LEFT:
                if (vfxArr[player.y][player.x-1] != '#' && vfxArr[player.y][player.x-1] != '0') {
                    player.x--;
                    if (vfxArr[player.y][player.x] == 'o') {
                        max += 1;
                        randomizer();
                    }
                } else reset();
                break;
            case DOWN:
                if (vfxArr[player.y+1][player.x] != '#' && vfxArr[player.y+1][player.x] != '0') {
                    player.y++;
                    if (vfxArr[player.y][player.x] == 'o') {
                        max += 1;
                        randomizer();
                    }
                } else reset();
                break;
            case RIGHT:
                if (vfxArr[player.y][player.x+1] != '#' && vfxArr[player.y][player.x+1] != '0') {
                    player.x++;
                    if (vfxArr[player.y][player.x] == 'o') {
                        max += 1;
                        randomizer();
                    }
                } else reset();
                break;
        }

        vfxArr[player.y][player.x] = '0';
        if (count >= max) {
            int y = positions[0].first;
            int x = positions[0].second;
            vfxArr[y][x] = ' ';
            positions.erase(positions.begin());
            count--;
        }
        count++;
        positions.emplace_back(player.y, player.x);
        Sleep(300);
    }
    std::cin.get();
    return 0;
}

void draw(const auto& vfxArr) {
    for (const auto& vfx : vfxArr) {
        std::cout << vfx << '\n';
    }
}