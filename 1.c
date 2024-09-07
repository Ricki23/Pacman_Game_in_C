#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define H 15  // Playfield height
#define W 40  // Playfield width

char playfield[H][W] = {
    "****************************************",
    "* .....................................*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*......................................*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*..*..*..*..*..*..*..*..*..*..*..*..*..*",
    "*......................................*",
    "****************************************"
};

int food_collect = 0, game_end = 0;
int py = 1, px = 1;  
int gy1 = 1, gx1 = 38, gy2 = 13, gx2 = 1;  

void game_result() {
    system("cls");  
    if (food_collect == 500) {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t        Congratulations!\n");
        printf("\t\t\t       You won the game!\n");
        printf("\t\t\t     Your total score is %d\n", food_collect);
    } else {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t\t          Better luck!\n");
        printf("\t\t\t       You lost the game!\n");
        printf("\t\t\t     Your total score is %d\n", food_collect);
    }
}

void move_ghosts() {
    if (gy1 == 1 && gx1 > 1) {
        gx1--;  // Move ghost 1 left
    } else if (gx1 == 1 && gy1 < 7) {
        gy1++;  // Move ghost 1 down
    } else if (gy1 == 7 && gx1 < 38) {
        gx1++;  // Move ghost 1 right
    } else if (gx1 == 38 && gy1 > 1) {
        gy1--;  // Move ghost 1 up
    }

    if (gy2 == 13 && gx2 < 38) {
        gx2++;  // Move ghost 2 right
    } else if (gx2 == 38 && gy2 > 7) {
        gy2--;  // Move ghost 2 up
    } else if (gy2 == 7 && gx2 > 1) {
        gx2--;  // Move ghost 2 left
    } else if (gx2 == 1 && gy2 < 13) {
        gy2++;  // Move ghost 2 down
    }
}

void user_input() {
    char c1;
    if (kbhit()) {
        c1 = getch();
        switch (c1) {
            case 72:  // Up arrow
                if (playfield[py - 1][px] != '*') py--;
                break;
            case 80:  // Down arrow
                if (playfield[py + 1][px] != '*') py++;
                break;
            case 75:  // Left arrow
                if (playfield[py][px - 1] != '*') px--;
                break;
            case 77:  // Right arrow
                if (playfield[py][px + 1] != '*') px++;
                break;
        }
    }
}

void setup() {
    // Reset playfield for Pacman's and ghosts' movements
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (playfield[i][j] == '#') {
                playfield[i][j] = ' ';
            }
            if (playfield[i][j] == '@') {
                playfield[i][j] = '.';
            }
        }
    }

    // Update food collection
    if (playfield[py][px] == '.') {
        food_collect++;
        playfield[py][px] = ' ';  // Pacman ate the food
    }

    if (playfield[py][px] == '*') {  // Pacman hits a wall
        py = 1;
        px = 1;
    }

    // Mark Pacman and ghosts in the playfield
    playfield[py][px] = '#';   // Pacman
    playfield[gy1][gx1] = '@'; // Ghost 1
    playfield[gy2][gx2] = '@'; // Ghost 2

    // End the game if Pacman meets a ghost
    if (playfield[py][px] == '@') {
        game_end = 1;
    }
}

void draw_playfield() {
    system("cls");  // Clear the screen for Windows, use "clear" for Linux/Mac
    printf("\n\n\n\n");
    for (int i = 0; i < H; i++) {
        printf("\t\t");
        for (int j = 0; j < W; j++) {
            printf("%c", playfield[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d\n", food_collect);
}

int main() {
    int i = 100;
    while (game_end != 1) {
        setup();
        user_input();
        move_ghosts();
        draw_playfield();
        _sleep(200);  // For Windows (use `usleep(200000)` on Linux/Mac)
        if (i < 1000)
            i = i + 100;
        else
            i = 100;
    }
    game_result();
    getch();
    return 0;
}
