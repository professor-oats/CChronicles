#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h> // Multithreading
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>


void getFruit(int invalue, int inindex);

int handleSteps(char instring[]) {

}

// Struct and functions to set/unset terminal to raw mode to read bytes from stdin - Enable keypressed
struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char fruits[256][15] = {
    "Cherry", "Banana", "Apple", "SnakePlisken", "GrannyCat", "OldBoot", "Pear", "VolvoV70", "Burzum",
    "DrDre", "Cornflake", "Wheat", "Papaya", "Mango", "Potato", "Tomato", "DragonBall", "FineWhisky", "KrakenSlayer", "Pocahontas",
    "Spinach", "Date", "Blueberry", "Strawberry", "Bulbasaur", "Pikachu", "Mushroom", "Mozart", "Gatorade",
    "Onion", "Garlic", "Bumblebee", "Cinnamon", "Leek", "PolkaCane", "Ettelman", "Plum", "BlackBean", "Almond",
    "Hazelnut", "Chestnut", "Avocado", "Pineapple", "Pomegranate", "Raspberry", "Grapes", "Lemon", "Orange", "GrannyTeeth",
    "Oreos", "Greenpea", "Chickpea", "Rhubarb", "Thyme", "Mint", "Thistle", "LostLamb", "Carrot", "Chili",
    "Oregano", "Cucumber", "Peanut", "AngryNeighbour", "Lawnmover", "Sadfish", "CuteMouse", "LittlePony", "Goblin", "MagicDust",
    "Paprika", "Lychee", "Excalibur", "Wormwood", "Nightshade", "FlyAmanthia", "FlaxSeeds", "SmallSnail", "PineSap", "MapleSap",
    "Unicycle",
    "Cherry", "Banana", "Apple", "SnakePlisken", "GrannyCat", "OldBoot", "Pear", "VolvoV70", "Burzum",
    "DrDre", "Cornflake", "Wheat", "Papaya", "Mango", "Potato", "Tomato", "DragonBall", "FineWhisky", "KrakenSlayer", "Pocahontas",
    "Spinach", "Date", "Blueberry", "Strawberry", "Bulbasaur", "Pikachu", "Mushroom", "Mozart", "Gatorade",
    "Onion", "Garlic", "Bumblebee", "Cinnamon", "Leek", "PolkaCane", "Ettelman", "Plum", "BlackBean", "Almond",
    "Hazelnut", "Chestnut", "Avocado", "Pineapple", "Pomegranate", "Raspberry", "Grapes", "Lemon", "Orange", "GrannyTeeth",
    "Oreos", "Greenpea", "Chickpea", "Rhubarb", "Thyme", "Mint", "Thistle", "LostLamb", "Carrot", "Chili",
    "Oregano", "Cucumber", "Peanut", "AngryNeighbour", "Lawnmover", "Sadfish", "CuteMouse", "LittlePony", "Goblin", "MagicDust",
    "Paprika", "Lychee", "Excalibur", "Wormwood", "Nightshade", "FlyAmanthia", "FlaxSeeds", "SmallSnail", "PineSap", "MapleSap",
    "Unicycle",
    "Cherry", "Banana", "Apple", "SnakePlisken", "GrannyCat", "OldBoot", "Pear", "VolvoV70", "Burzum",
     "DrDre", "Cornflake", "Wheat", "Papaya", "Mango", "Potato", "Tomato", "DragonBall", "FineWhisky", "KrakenSlayer", "Pocahontas",
     "Spinach", "Date", "Blueberry", "Strawberry", "Bulbasaur", "Pikachu", "Mushroom", "Mozart", "Gatorade",
     "Onion", "Garlic", "Bumblebee", "Cinnamon", "Leek", "PolkaCane", "Ettelman", "Plum", "BlackBean", "Almond",
     "Hazelnut", "Chestnut", "Avocado", "Pineapple", "Pomegranate", "Raspberry", "Grapes", "Lemon", "Orange", "GrannyTeeth",
     "Oreos", "Greenpea", "Chickpea", "Rhubarb", "Thyme", "Mint", "Thistle", "LostLamb", "Carrot", "Chili",
     "Oregano", "Cucumber", "Peanut", "AngryNeighbour", "Lawnmover", "Sadfish", "CuteMouse", "LittlePony", "Goblin", "MagicDust",
     "Paprika", "Lychee", "Excalibur", "Wormwood", "Nightshade", "FlyAmanthia", "FlaxSeeds", "SmallSnail", "PineSap", "MapleSap",
     "Unicycle",
     "Nothing", "Nothing", "Nothing", "Nothing", "Nothing","Nothing", "Nothing", "Nothing", "Nothing", "Nothing", "Nothing", "Nothing", "Nothing"};

char fruitsgathered[4][15];


int main(void) {

    int i = 0;
    char c;
    char firstchoice[20];
    char firstchoicebig[20];
    char stepstaken[4];
    char fruitbasket[60];

    int cmpgod;
    int cmpstart;
    int basketindex;

    int fruitsalad = 0;
    int fruitsaladlist[4];

    srand(time(NULL));

    puts("Welcome to the Adventures of Grandma's Fruitbasket!\n"
         "You're goal is to gather fruits from your grandma's garden.\n"
         "It has been a great year and there are a lot to harvest.\n"
         "Use the WASD keys to navigate in her garden and get as many fruits and vegetables you can.\n"
         "You will get a new vegetable/fruit after each 4 steps you take - Basket is full after 4 aquired fruits\n"
         "If you are in a rush - Type godmode now to get a random set to use on your journey (may contain duplicates),\n otherwise type start to begin. :)\n");


    while (true) {
        scanf("%s", firstchoice);

        while (firstchoice[i]) {
            firstchoicebig[i] = toupper(firstchoice[i]);
            i++;
        }

        firstchoicebig[i] = '\0';

        cmpgod = strcmp(firstchoicebig, "GODMODE");
        cmpstart = strcmp(firstchoicebig, "START");


        if (!(cmpgod == 0 || cmpstart == 0)) {
            printf("Wrong input, try again!\n");
            i=0;
            continue;
        }

        break;

    }

    if (cmpgod == 0) {
        for (i = 0; i < 4; i++) {
            fruitsalad = rand() % 63;
            getFruit(fruitsalad, i); // CHANGE THIS
        }

        goto KITCHEN;
    }


    // Start game here
    int gathercount = 0, stepcount = 0, fruitfactor = 1, gardensplitter = 0;
    enableRawMode();  // RAWmode terminal to enable keypressed
    while (read(STDIN_FILENO, &c, 1) == 1 && gathercount < 4) {
        if (!(c == 'w' || c == 'a' || c == 's' || c == 'd')) {
            continue;
        }

        if (stepcount > 3) {
            if (fruitfactor < 5) {
                fruitfactor = fruitfactor + 30;
            }
            if (fruitfactor > gardensplitter) {
                fruitsalad = (rand() % (fruitfactor - gardensplitter)) + gardensplitter;
            }
            else {
                fruitsalad = rand() % fruitfactor;
            }
            fruitsaladlist[gathercount] = fruitsalad;
            if (gathercount > 0) {    // Reduce amount of duplicates here
                for (int j = 0; j < gathercount; j++) {
                    if (fruitsaladlist[j] == fruitsalad) {
                        if (fruitsalad > 62) {   // Disable out of bound
                            fruitsalad = 0;
                        }
                        fruitsalad++;
                    }
                }
            }

            getFruit(fruitsalad, gathercount);
            gathercount++;
            stepcount = 0;
            fruitfactor = 1;
        }


        else if (stepcount == 0) {
            switch (c) {
                case 'w': gardensplitter = 0; break;
                case 'a': gardensplitter = 10; break;
                case 's': gardensplitter = 20; break;
                case 'd': gardensplitter = 30; break;
                default: ;
            }
        }


        if (c == 'w') {
            puts(
                "o  o  o\n"
            " o o o o");
            fruitfactor *= 1;
        }

        else if (c == 'a') {
            fruitfactor *= 2;
        }

        else if (c == 's') {
            fruitfactor *= 3;
        }

        else if (c == 'd') {
            fruitfactor *= 4;
        }

        stepcount++;

    }

    disableRawMode();


    // KITCHEN
    KITCHEN:
    printf("Inside Kitchen\n");

    return 0;

}


void getFruit(int invalue, int inindex) {
    strcpy(fruitsgathered[inindex],fruits[invalue]);
    printf("You found: %s\n", fruitsgathered[inindex]);

}