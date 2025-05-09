/*
 * GNU Chess 5.0 - pgn.c - pgn game format code Copyright (c) 1999-2002 Free
 * Software Foundation, Inc.
 *
 * GNU Chess is based on the two research programs Cobalt by Chua Kong-Sian and
 * Gazebo by Stuart Cracraft.
 *
 * GNU Chess is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2, or (at your option) any later
 * version.
 *
 * GNU Chess is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * GNU Chess; see the file COPYING.  If not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Contact Info: bug-gnu-chess@gnu.org
 */

#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>

#include "common.h"
#include "version.h"
#include "book.h"

void PGNSaveToFile(const char *file, const char *resultstr)

/****************************************************************************
 *
 *  To save a game into PGN format to a file.  If the file does not exist,
 *  it will create it.  If the file exists, the game is appended to the file.
 *
 ****************************************************************************/
{
    FILE *fp;
    char s[100];
    int len;
    char *p;
    int i;
    time_t secs;
    struct tm *timestruct;

    fp = fopen(file, "a");               /* Can we append to it? */
    if (fp == NULL) {
        printf("Cannot write to file %s\n", file);
        return;
    }

    /*
     * Write the seven tags
     */
    fprintf(fp, "[Event \"\"]\n");
    fprintf(fp, "[Site \"\"]\n");
    secs = time(0);
    timestruct = localtime((time_t *) & secs);
    fprintf(fp, "[Date \"%4d.%02d.%02d\"]\n", timestruct->tm_year + 1900,
        timestruct->tm_mon + 1, timestruct->tm_mday);
    fprintf(fp, "[Round \"\"]\n");
    if (computerplays == white)
        fprintf(fp, "[White \"%s %s\"]\n", PROGRAM, VERSION);
    else
        fprintf(fp, "[White \"%s\"]\n", name);
    if (computerplays == black)
        fprintf(fp, "[Black \"%s %s\"]\n", PROGRAM, VERSION);
    else
        fprintf(fp, "[Black \"%s\"]\n", name);
    fprintf(fp, "[WhiteELO \"%d\"]\n",
        computer == white ? myrating : opprating);
    fprintf(fp, "[BlackELO \"%d\"]\n",
        computer == white ? opprating : myrating);

    /*
     * Revive the little-known standard functions!
     */
    len = strcspn(resultstr, " {");
    fprintf(fp, "[Result \"%.*s\"]\n", len, resultstr);
    fprintf(fp, "\n");

    s[0] = '\0';
    for (i = 0; i <= GameCnt; i += 2) {
        if (i == GameCnt) {
            /*
             * Handle special case to avoid printing out blacks GameCnt+1
             * move from a preceeding game.
             * Game is not reinitialised in init, just overwritten
             */
            sprintf(s, "%s%d. %s ", s, i / 2 + 1, Game[i].SANmv);
        } else {
            sprintf(s, "%s%d. %s %s ", s, i / 2 + 1, Game[i].SANmv,
                Game[i + 1].SANmv);
        }
        if (strlen(s) > 80) {
            p = s + 79;
            while (*p-- != ' ') ;
            *++p = '\0';
            fprintf(fp, "%s\n", s);
            strcpy(s, p + 1);
        }
    }
    fprintf(fp, "%s", s);
    fprintf(fp, "%s", resultstr);
    fprintf(fp, "\n\n");
    fclose(fp);

}

void PGNReadFromFile(const char *file)

/****************************************************************************
 *
 *  To read a game from a PGN file.
 *
 ****************************************************************************/
{
    FILE *fp;
    char s[100], c, wmv[8], bmv[8];
    int moveno;
    leaf *p;

    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Cannot open file %s\n", file);
        return;
    }

    /*
     * Skip all the tags
     */
    do {
        if ((c = fgetc(fp)) == '[')
            fgets(s, 100, fp);
    } while (c == '[');
    ungetc(c, fp);

    InitVars();
    while (!feof(fp)) {
        c = fgetc(fp);
        if (c == '*')
            break;
        ungetc(c, fp);
        fscanf(fp, "%d. %7s %7s ", &moveno, wmv, bmv);
        p = ValidateMove(wmv);
        if (!p) {
            printf("Illegal move %d. %s\n", moveno, wmv);
            break;
        }
        MakeMove(white, &p->move);
        strcpy(Game[GameCnt].SANmv, wmv);
        if (*bmv == '*')
            break;
        p = ValidateMove(bmv);
        if (!p) {
            printf("Illegal move %d. ... %s\n", moveno, bmv);
            break;
        }
        MakeMove(black, &p->move);
        strcpy(Game[GameCnt].SANmv, bmv);
    }
    printf("%d\n", GameCnt);
    fclose(fp);
    ShowBoard();
    TTClear();
    return;
}

void BookPGNReadFromFile(const char *file)

/****************************************************************************
 *
 *  To read a game from a PGN file and store out the hash entries to book.
 *
 ****************************************************************************/
{
    FILE *fp;
    char s[100], wmv[8], bmv[8];
    int c;
    unsigned int i;
    char header[2000];
    int moveno, result, ngames = 0;
    leaf *p;
    time_t t1, t2;
    double et;
    int examinecolor, playerfound[2];

    /*
     * Only players in the table below are permitted into the opening book from
     * the PGN files. Please expand the table as needed. Generally, I would
     * recommend only acknowledged GM's and IM's and oneself, but because of
     * the self-changing nature of the book, anything inferior will eventually
     * be eliminated through automatic play as long as you feed the games the
     * program plays back to itself with "book add pgnfile"
     */
    /*
     * XXX: Is it really a good idea to have a list like this hardcoded?
     */

    const char *const player[] = {
        "Alekhine",
        "Adams",
        "Anand",
        "Anderssen",
        "Andersson",
        "Aronin",
        "Averbakh",
        "Balashov",
        "Beliavsky",
        "Benko",
        "Bernstein",
        "Bird",
        "Bogoljubow",
        "Bolbochan",
        "Boleslavsky",
        "Byrne",
        "Botvinnik",
        "Bronstein",
        "Browne",
        "Capablanca",
        "Chigorin",
        "Christiansen",
        "De Firmian",
        "Deep Blue",
        "Deep Thought",
        "Donner",
        "Dreev",
        "Duras",
        "Euwe",
        "Evans",
        "Filip",
        "Fine",
        "Fischer",
        "Flohr",
        "Furman",
        "Gelfand",
        "Geller",
        "Gereben",
        "Glek",
        "Gligoric",
        "GNU",
        "Golombek",
        "Gruenfeld",
        "Guimard",
        "Hodgson",
        "Ivanchuk",
        "Ivkov",
        "Janowsky",
        "Kamsky",
        "Kan",
        "Karpov",
        "Kasparov",
        "Keres",
        "Korchnoi",
        "Kortschnoj",
        "Kotov",
        "Kramnik",
        "Kupreich",
        "Lasker",
        "Lautier",
        "Letelier",
        "Lilienthal",
        "Ljubojevic",
        "Marshall",
        "Maroczy",
        "Mieses",
        "Miles",
        "Morphy",
        "Mueller",                       /* Every other German has this name...
                                          */
        "Nimzowitsch",
        "Nunn",
        "Opocensky",
        "Pachman",
        "Petrosian",
        "Piket",
        "Pilnik",
        "Pirc",
        "Polgar",
        "Portisch",
        "Psakhis",
        "Ragozin",
        "Reshevsky",
        "Reti",
        "Romanish",
        "Rubinstein",
        "Saemisch",
        "Seirawan",
        "Shirov",
        "Short",
        "Silman",
        "Smyslov",
        "Sokolsky",
        "Spassky",
        "Sveshnikov",
        "Stahlberg",
        "Steinitz",
        "Tal",
        "Tarjan",
        "Tartakower",
        "Timman",
        "Topalov",
        "Torre",
        "Vidmar"
    };

    et = 0.0;
    t1 = time(NULL);
    result = -1;
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open file %s: %s\n", file, strerror(errno));
        return;
    }

    /*
     * Maybe add some more clever error handling later
     */
    if (BookBuilderOpen() != BOOK_SUCCESS)
        return;
    newpos = existpos = 0;

nextgame:

    header[0] = 0;
    InitVars();
    NewPosition();
    CLEAR(flags, MANUAL);
    CLEAR(flags, THINK);
    myrating = opprating = 0;

    playerfound[black] = playerfound[white] = 0;

    /*
     * Skip all the tags
     */
    /*
     * XXX: This has two problems: 1) Leading whitespace leads to
     * undefined stuff in s, and completely confuses the program.
     * 2) If there is a game between two players in the list, only
     * the moves of the white player will be added.
     */

    /*
     * Skip whitespace
     */
    while ((c = fgetc(fp)) != EOF) {
        if (c != ' ' && c != '\t' && c != '\n') {
            ungetc(c, fp);
            break;
        }
    }

    while ((c = fgetc(fp)) == '[') {
        ungetc(c, fp);
        fgets(s, 100, fp);
        strcat(header, s);
        if (strncmp(s + 1, "White ", 6) == 0) {
            examinecolor = white;
            ngames++;
        } else if (strncmp(s + 1, "Black ", 6) == 0) {
            examinecolor = black;
        } else if (strncmp(s + 1, "Result", 6) == 0) {
            if (strncmp(s + 7, " \"1-0", 5) == 0) {
                result = R_WHITE_WINS;
            } else if (strncmp(s + 7, " \"0-1", 5) == 0) {
                result = R_BLACK_WINS;
            } else if (strncmp(s + 7, " \"1/2-1/2", 9) == 0) {
                result = R_DRAW;
            } else {
                result = R_NORESULT;
            }
            continue;
        } else
            continue;
        /*
         * We get only here if White or Black matched, it is ugly but it
         * works. Attention: If at some point we want to put this array
         * of authorized players in some external file, we have to keep
         * track of the size of that array in some other way.
         */
        for (i = 0; i < (sizeof(player) / sizeof(*player)); i++) {
            if (strstr(s + 7, player[i]) != NULL) {
                playerfound[examinecolor] = 1;
            }
        }
    }
    ungetc(c, fp);
    while (1) {
        if (fscanf(fp, "%d. %7s ", &moveno, wmv) < 2)
            break;

        if (wmv[0] == '1' || wmv[0] == '[' || wmv[0] == '*'
            || strcmp(wmv, "0-1") == 0)
            break;

        p = ValidateMove(wmv);
        if (!p) {
            puts(header);
            ShowBoard();
            printf("Illegal move %d. %s\n", moveno, wmv);
            break;
        }
        MakeMove(white, &p->move);
        if (playerfound[white]) {
            if (BookBuilder(result, white) != BOOK_SUCCESS)
                break;
        }
        strcpy(Game[GameCnt].SANmv, wmv);

        if (fscanf(fp, "%7s ", bmv) < 1)
            break;
        if (bmv[0] == '1' || bmv[0] == '[' || bmv[0] == '*'
            || strcmp(bmv, "0-1") == 0)
            break;

        p = ValidateMove(bmv);
        if (!p) {
            puts(header);
            ShowBoard();
            printf("Illegal move %d. ... %s\n", moveno, bmv);
            break;
        }
        MakeMove(black, &p->move);
        if (playerfound[black]) {
            if (BookBuilder(result, black) != BOOK_SUCCESS)
                break;
        }
        strcpy(Game[GameCnt].SANmv, bmv);
    }

    /*
     * Read to end of game but don't parse
     */
    while (!feof(fp)) {
        fgets(s, 100, fp);
        if (s[0] == '\n')
            break;
    }
    /*
     * printf ("%d(%d)\n", GameCnt,BOOKDEPTH);
     */
    if (!feof(fp)) {
        if (ngames % 10 == 0)
            printf("%d\r", ngames);
        fflush(stdout);
        goto nextgame;
    }

    fclose(fp);
    if (BookBuilderClose() != BOOK_SUCCESS) {
        perror("Error writing opening book");
    }

    /*
     * Reset the board otherwise we leave the last position in the book on the
     * board.
     */
    header[0] = 0;
    InitVars();
    NewPosition();
    CLEAR(flags, MANUAL);
    CLEAR(flags, THINK);
    myrating = opprating = 0;

    t2 = time(NULL);
    et += difftime(t2, t1);
    putchar('\n');

    /*
     * Handle divide-by-zero problem
     */
    if (et < 0.5) {
        et = 1.0;
    };

    printf("Time = %.0f seconds\n", et);
    printf("Games compiled: %d\n", ngames);
    printf("Games per second: %f\n", ngames / et);
    printf("Positions scanned: %d\n", newpos + existpos);
    printf("Positions per second: %f\n", (newpos + existpos) / et);
    printf("New & unique added: %d positions\n", newpos);
    printf("Duplicates not added: %d positions\n", existpos);
}

/*
 * -----------------------------------------------------------------------------
 * vim: ft=c colorcolumn=81 autoindent shiftwidth=4 tabstop=4 expandtab
 */
