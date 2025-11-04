
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

// Função para desenhar uma caixa (box) com ncurses
void box_ncurses(int lin1, int col1, int lin2, int col2) {
    int i;
    mvaddch(lin1, col1, '+');
    mvaddch(lin1, col2, '+');
    mvaddch(lin2, col1, '+');
    mvaddch(lin2, col2, '+');

    for (i = col1 + 1; i < col2; i++) {
        mvaddch(lin1, i, '-');
        mvaddch(lin2, i, '-');
    }
    for (i = lin1 + 1; i < lin2; i++) {
        mvaddch(i, col1, '|');
        mvaddch(i, col2, '|');
    }
}

// Função para mover o cursor
void linhaCol(int lin, int col) {
    move(lin, col);
}

// Função para mostrar o menu
int menu(int lin1, int col1, int qtd, char lista[10][40]) {
    int escolha = 0;
    int tecla;

    keypad(stdscr, TRUE);
    noecho();

    while (1) {
        for (int i = 0; i < qtd; i++) {
            if (i == escolha) {
                attron(A_REVERSE);
                mvprintw(lin1 + i, col1, "%s", lista[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(lin1 + i, col1, "%s", lista[i]);
            }
        }

        tecla = getch();

        switch (tecla) {
            case KEY_UP:
                escolha--;
                if (escolha < 0) escolha = qtd - 1;
                break;
            case KEY_DOWN:
                escolha++;
                if (escolha >= qtd) escolha = 0;
                break;
            case 10: // Enter
                return escolha;
        }
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "");
    initscr();
    start_color();
    curs_set(0);

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(1));

    char opcoes[10][40] = {"Opção 1", "Opção 2", "Sair"};
    int escolha;

    clear();
    box_ncurses(2, 5, 10, 40);
    mvprintw(1, 10, "=== MENU PRINCIPAL ===");
    refresh();

    escolha = menu(4, 10, 3, opcoes);

    clear();
    mvprintw(10, 10, "Você escolheu: %s", opcoes[escolha]);
    refresh();
    getch();

    endwin();
    return 0;
}
