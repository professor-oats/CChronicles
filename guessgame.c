#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"

int generateRandom();

int main(void) {

    int usernumber;
    char colorinput[7];
    char colorbig[7];
    char foes[30];
    bool right = false;

    int cmpr;
    int cmpg;
    int cmpb;
    int cmpy;

    printf("Welcome to the number guessing game between 1-100\n");
    printf("Start by selecting your random seed from the colors below\n");

    while (!right) {
        int i = 0;

        printf("%sred\n", KRED);
        printf("%sgreen\n", KGRN);
        printf("%sblue\n", KBLU);
        printf("%syellow\n\n", KYEL);

        scanf("%s", colorinput);

        while (colorinput[i]) {
            colorbig[i] = toupper(colorinput[i]);
            i++;
        }

        colorbig[i] = '\0';

        cmpr = strcmp("RED", colorbig);
        cmpg = strcmp(colorbig, "GREEN");
        cmpb = strcmp(colorbig, "BLUE");
        cmpy = strcmp("YELLOW", colorbig);

        // Globber here

        if (!(cmpr == 0 || cmpg == 0 || cmpb == 0 || cmpy == 0)) {
            printf("Wrong input, try again!\n");
            continue;
        }

        right = true;

    }

    while (true) {
        printf("Pick a number between 1-37\n");
        scanf("%d", &usernumber);

        if (usernumber > 0 && usernumber < 38) {
            break;
        }

        printf("Wrong number, try again!\n");
        while((getchar()) != '\n');  // Flush

    }

    FILE *fptr;
    // Store the content of the file
    int number;
    char word[15];

    // RED
    if (cmpr == 0) {
        fptr = fopen("redcolor.txt", "r");

        if (fptr == NULL) {
            printf("Error opening file\n");
        }

        // Read the content pair of twos and print it

        for (int i = 0; i < usernumber; i++) {
            if (fscanf(fptr, "%14s %x", word, &number) == 2) {
                //spacerabbits are amazing
            } else {
                printf("Failed to read data from file.\n");
            }
        }
        fclose(fptr);
        char redteam[] = "Mountain Wolfriders";
        strcpy(foes, redteam);
        printf("After exiting the cave your hear noises and great roaring at a not so far distance.\nYour breath is heavy from dust, ashes and stomach full of brine.\nNo time to rest, you are up against hordes of %s %s!\nTheir seed number is: %d and they will decapitate anyone standing in their path.\n\nDraw your sword!\n", word, redteam, number);
    }

    // GREEN
    else if (cmpg == 0) {
        fptr = fopen("greencolor.txt", "r");

        if (fptr == NULL) {
            printf("Error opening file\n");
        }

        // Read the content pair of twos and print it

        for (int i = 0; i < usernumber; i++) {
            if (fscanf(fptr, "%14s %x", word, &number) == 2) {
                //printf("You got: %s!\nSeed number: %d\n", word, number);
            } else {
                printf("Failed to read data from file.\n");
            }
        }
        fclose(fptr);
        char greenteam[] = "Mindless Swampwalkers";
        strcpy(foes, greenteam);
        printf("Wandering the lands you dream of soft meadows with cowlike creatures hopping happily to the rhythm of The Sun's ultraviolet frequency.\nHowever you are stickily stuck in this tar swamp with roots entangling your limbs.\nLurking in the mossy substance under your feet are the %s %s.\nDon't let their emotionless faces lure you, their seed number is: %d and they have an appetite for your limbs just as high.\n\nStay your ground!\n", word, greenteam, number);
    }

    // BLUE
    else if (cmpb == 0) {
        fptr = fopen("bluecolor.txt", "r");

        if (fptr == NULL) {
            printf("Error opening file\n");
        }

        // Read the content pair of twos and print it

        for (int i = 0; i < usernumber; i++) {
            if (fscanf(fptr, "%14s %x", word, &number) == 2) {
                //spacerabbits are amazing
            } else {
                printf("Failed to read data from file.\n");
            }
        }
        fclose(fptr);
        char blueteam[] = "Sunken Undead";
        strcpy(foes, blueteam);
        printf("Thunderstorms and oceanwaves are roaring, the black sky crumbles down on any passenger still alive on the ship.\nCracked kneecaps and shattered skulls ramble in every corner and shackles hold you down from reaching freedom and air.\nHow will you escape the %s %s??\nThey are as strong as they look old with their seed number of: %d.\n\nWill you drown and become the undead?\n", word, blueteam, number);
    }

    else if (cmpy == 0) {
        fptr = fopen("yellowcolor.txt", "r");

        if (fptr == NULL) {
            printf("Error opening file\n");
        }

        // Read the content pair of twos and print it

        for (int i = 0; i < usernumber; i++) {
            if (fscanf(fptr, "%14s %x", word, &number) == 2) {
                //spacerabbits are amazing
            } else {
                printf("Failed to read data from file.\n");
            }
        }
        fclose(fptr);
        char yellowteam[] = "Great Sandmammoth";
        strcpy(foes, yellowteam);
        printf("Solar rays, sun flares and desert sand.\nMirage ways, monster lairs in these bare wastelands.\nThe cooling Teardrops of Avalon borrowed from the caravan two days ago are running empty, time is running out and your pulse is turning to instincts.\nWith heightened animalistic senses your keen eyes witness a %s %s!\nIt still hasn't found your presence but its mass is as big as its seed number of: %d.\n\nWill you risk your life taking it down or wait until the next caravan?\n", word, yellowteam, number);
    }

    // Seeding done. Game starts here
    int answernumber = generateRandom(number);
    int guessednumber;

    printf("Game has started. Guess the number between 1-100\n");

    while (true) {
        scanf("%d", &guessednumber);

        if (guessednumber < 1 || guessednumber > 100) {
            printf("Wrong in input, try again!\n");
            while((getchar()) != '\n');  // Flush
            continue;
        }

        if (guessednumber == answernumber) {
            printf("Congratulations!! You defeated the %s %s. You guessed %d, which is the correct number!!\n", word, foes, guessednumber);
            return 0;
        }

        if (guessednumber > answernumber) {
            printf("Your number is too great. Guess again...\n");
        }

        else {
            printf("Your number is too small. Guess again...\n");
        }
        while((getchar()) != '\n');  // Flush
    }
}


int generateRandom(int colorvaluein) {
    srand(time(0));
    int count;
    int randomnumber;
    int max = 100;
    int randomscope = 20;
    int min = 1;

    count = abs((colorvaluein * rand()) % randomscope + 1);  // because sometimes negative


    for (int i = 0; i < count; i++) {
        randomnumber = rand() % (max - min + 1) + min;
    }

    return randomnumber;
}
