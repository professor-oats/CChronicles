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
void suspiciousJuicerGame();
void* flyingPlates();  // Threaded
void* dodgingPlates(); // Threaded
void printPlatesRight();
void printPlatesLeft();
void rollingPinGame();
void kitchenKnifeGame();
void handleDeath();
int roll10();

bool FLYINGPLATESEND = false;
bool dodgeright = false;
bool dodgeleft = false;
int dodgecount = 0;


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
            fruitsalad = rand() % 256;
            getFruit(fruitsalad, i);
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
                        if (fruitsalad > 255) {   // Disable out of bound
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
            puts("^");
            fruitfactor *= 1;
        }

        else if (c == 'a') {
            puts("<");
            fruitfactor *= 2;
        }

        else if (c == 's') {
            puts("v");
            fruitfactor *= 3;
        }

        else if (c == 'd') {
            puts(">");
            fruitfactor *= 4;
        }

        stepcount++;

    }

    disableRawMode();


    // KITCHEN - Have each choice have their own mini game here
    // Kitchen knife will spawn the goblins
    // Goblins will attack and user will have to dodge, when hit it's game over
    // Rolling Pin will prompt to roll up up up down down down up up down down up
    // - On sequence miss the user must start over.
    // Swedish Cheese Grater is just a dummy and will ask user for a rechoice
    KITCHEN:
    int kitchenchoice;
    int battermixlevel;
    int luckycheck;
    char batter[4];
    puts("#########################\n"
        "###       LEVEL 2     ###\n"
        "### Grandma's Kitchen ###\n"
        "#########################");
    puts("Good job in making it to Grandma's Kitchen!\n"
        "Now it's time to prepare the fruits, but beware of The Garden Goblins.\n");

    printf("Your basket contains:\n");
    for (int k = 0; k < 4; k++) {
        printf("%s\n", fruitsgathered[k]);
    }


    while (true) {
        puts("\nPick your tool:\n"
        "1. Suspicious Juicer [Easiest]\n"
        "2. Rolling Pin [Easy]\n"
        "3. Swedish Cheese Grater [?]\n"
        "4. Kitchen Knife [Hard]\n"
        "5. Godmode [Cheater]");

        scanf("%d", &kitchenchoice);

        if (!(kitchenchoice > 0 && kitchenchoice < 6)) {
            printf("Input 1-5 to make your choice.\n");
            while((getchar()) != '\n');  // Flush
            continue;
        }

        if (kitchenchoice == 3) {
            printf("Swedish Cheese Grater is not a good tool, try again\n");
        }

        else if (kitchenchoice == 5) {
            printf("Godmode is not allowed here!");
        }

        else if (kitchenchoice == 1) {
            suspiciousJuicerGame();
            break;
        }


    }

    EXIT:
    return 0;

}


void getFruit(int invalue, int inindex) {
    strcpy(fruitsgathered[inindex],fruits[invalue]);
    printf("You found: %s\n", fruitsgathered[inindex]);

}

void suspiciousJuicerGame() {
    int mixerlevel;
    int mixingseconds;
    int secondcount = 0;
    int luckynumber;
    bool earringaquired = false;
    //char cjg;
    pthread_t id_flyingplates, id_dodgingplates;
    puts("In the cupboard above you notice grandma's Suspicious Juicer.\n"
        "You remember from early childhood just how unreliable it can be.\n"
        "Grandma is waiting for her cake so no time to waste!\n"
        "Set the mixer level:\n"
        "1 | 2 | 3 | 4 | 5 WARNING!!!!\n");

    while (true) {
        scanf("%d", &mixerlevel);
        if (!(mixerlevel> 0 && mixerlevel < 6)) {
            printf("Input 1-5 to set the level.\n");
            puts("Set the mixer level:\n"
                   "1 | 2 | 3 | 4 | 5 WARNING!!!!\n");
            while((getchar()) != '\n');  // Flush
            continue;
        }

        if (mixerlevel == 1) {
            mixingseconds = 10;
            printf("You are mixing.\n");
            while (secondcount <= mixingseconds) {
                switch (secondcount % 3) {
                    case 0: printf("Clang.\n"); break;
                    case 1: printf("Clang.\n"); break;
                    case 2: printf("Clunk.\n"); break;
                    default: ;
                }
                secondcount++;
                sleep(1);
            }

            luckynumber = roll10();

            printf("\nMixing done!!\n");
            puts("White smoke comes out of the juicer and the low mixing level yielded\n"
                "chunky rocklike fuit parts you wonder if grandma will approve of ...\n");

            if (luckynumber > 9) {
                puts("But you were lucky this time and Goddess Fortuna shone on the Suspicious Juicer!\n"
                    "In the insides of the fruit meats you find grandma's lost earring, wonder how it ended up there!");
                earringaquired = true;

                luckynumber = roll10();

                if (luckynumber < 2) {
                    puts("You reach out with your stroganoff fingers inside the Suspicious Juicer\n."
                        "Stupid you forgot to pull the plug and you accidently turn the mixer on again ...\n"
                        "You lose your fingers and grandma have to drive you to the hospital.\n");
                    handleDeath();
                }
            }

            break;
        }

        if (mixerlevel == 2) {
            mixingseconds = 10;
            printf("You are mixing.\n");
            while (secondcount <= mixingseconds) {
                switch (secondcount % 3) {
                    case 0: printf("Vrrr.\n"); break;
                    case 1: printf("Vrrr.\n"); break;
                    case 2: printf("WWWRRRRR!!\n"); break;
                    default: ;
                }
                secondcount++;
                sleep(1);
            }

            printf("\nMixing done!!\n");
            puts("A silent sigh sipper out from the Suspicious Juicer and your are happy that it made it just another time.\n"
                "Not much of juice, more like a gray batter. You realise just how mid and OHIO this vegetable batter is.\n"
                "Your best bet now is to success well with Grandma's Oven!\n");

            break;


        }

        if (mixerlevel == 3) {
            mixingseconds = 10;
            printf("You are mixing.\n");
            while (secondcount <= mixingseconds) {
                switch (secondcount % 3) {
                    case 0: printf("Woosh.\n"); break;
                    case 1: printf("Swoosh.\n"); break;
                    case 2: printf("Wooooooooooosh!!\n"); break;
                    default: ;
                }
                secondcount++;
            }

            printf("\nMixing done!!\n");
            puts("Phew! The machine managed to handle the massive stress of mixing level 3. Lucky this time nothing bad\n"
                "happened and you have an OK Juice in the machine. Just some luck needed with Grandma's Oven next and you surely know that\n"
                "she will be happy with your performance!!\n");

            break;
        }

        if (mixerlevel == 4) {
            mixingseconds = 10;
            printf("You are mixing.\n");
            while (secondcount <= mixingseconds) {
                switch (secondcount % 3) {
                    case 0: printf("GAAAUR.\n"); break;
                    case 1: printf("MAAWWR.\n"); break;
                    case 2: printf("FFFTSafafaffaffafafaffafffafafa!!\n"); break;
                    default: ;
                }
                secondcount++;
                sleep(1);
            }

            printf("\nCATASTROPHY!! MADNESS!!\n");
            puts("Machine is overheating and glowing, fruit juices are overfilling and spilling on the walls and all over\n"
                 "Grandma's dear kitchen!! You act fast and go for the plug, pull it out violently but the machine won't stop.\n"
                 "Its capacitor is overloaded and is now supplying it with continuous current. Grab a plate and defend yourself!\n");

            enableRawMode();
            /* Starting event thread */
            pthread_create(&id_flyingplates, NULL, flyingPlates, NULL);
            pthread_create(&id_dodgingplates, NULL, dodgingPlates, NULL);
            pthread_join(id_flyingplates, NULL);
            pthread_join(id_dodgingplates, NULL);


            //pthread_join(id_flyingplates, NULL);
            disableRawMode();
            printf("YOU SURVIVED YOU BASTARD!\n");
            dodgecount = 0;

            break;

        }
    }

}

int roll10() {
    return rand() % 10 + 1;
}

void handleDeath() {
    printf("GAME ENDED");
    exit(0);
}

/// Doing Stuff while listening to keyboard
/// Let's learn if we can use functions as we want for the thread
void* flyingPlates() {
    int randomswitch;
    printf("Plates are flying!!\nPrepare to guard LEFT ('A') or guard RIGHT ('D') or die!!\n");
    while (!FLYINGPLATESEND) {
        randomswitch = roll10();
        if (randomswitch % 2 == 0) {
            printPlatesRight();
        }
        else if (randomswitch > 0) {
            printPlatesLeft();
        }
        printf("Blocked!!\n");
        dodgecount++;
    }
    printf("Printing Thread Finished!\n");
}

void* dodgingPlates() {

    char cjg;
    while (read(STDIN_FILENO, &cjg, 1) == 1 && dodgecount < 3) {
        if (!(cjg == 'a' || cjg == 'd')) {
            dodgeright = false;
            dodgeleft = false;
            continue;
        }
        if (cjg == 'a') {
            dodgeleft = true;
            dodgeright = false;
            sleep(1);
            dodgeleft = false;
        }
        else if (cjg == 'd') {
            dodgeright = true;
            dodgeleft = false;
            sleep(1);
            dodgeright = false;
        }
    }

    dodgeright = true;
    dodgeleft = true;
    FLYINGPLATESEND = true;
}

void printPlatesRight() {
    sleep(1);
    printf("3\n");
    sleep(1);
    printf("2\n");
    sleep(1);
    printf("1\n");
    sleep(1);
    printf("Guard RIGHT!!\n");
    sleep(1);
    if (!dodgeright) {
        printf("Plate hit you right in the head and you fell to the ground bleeding your brain out.\n");
        handleDeath();
    }
}

void printPlatesLeft() {
    sleep(1);
    printf("3\n");
    sleep(1);
    printf("2\n");
    sleep(1);
    printf("1\n");
    sleep(1);
    printf("Guard LEFT!!\n");
    sleep(1);
    if (!dodgeleft) {
        printf("Plate hit you right in the head and you fell to the ground bleeding your brain out.\n");
        handleDeath();
    }
}
