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
void* flyingFruits();  // Threaded
void* dodgingFruits(); // Threaded
void* flyingGoblins(); // Threaded
void* dodgingGoblins(); // Threaded
void printFruitsRight();
void printFruitsLeft();
void printGoblinsRight();
void printGoblinsLeft();
void printGoblinsFeet();
void kitchenKnifeGame();
void handleDeath();
int roll10();

bool FLYINGFRUITSEND = false;
bool dodgeright = false;
bool dodgeleft = false;
bool jump = false;
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

    int cmpgod;
    int cmpstart;

    int fruitsalad = 0;
    int fruitsaladlist[4];

    srand(time(NULL));

    puts("Welcome to the Adventures of Grandma's Fruitbasket!\n"
         "You're goal is to gather fruits from your grandma's garden.\n"
         "It has been a great year and there are a lot to harvest.\n"
         "Use the WASD keys to navigate in her garden and get as many fruits and vegetables you can.\n"
         "You will get a new vegetable/fruit after each 4 steps you take - Basket is full after 4 aquired fruits\n"
         "If you are in a rush - Type godmode now to get a random set to use on your journey (may contain duplicates),\notherwise type start to begin. :)\n");


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
    char batter[4];
    puts("#########################\n"
        "###       LEVEL 2     ###\n"
        "### Grandma's Kitchen ###\n"
        "#########################");
    puts("Good job in making it to Grandma's Kitchen!\n"
        "Now it's time to prepare the fruits, but beware of The Garden Goblins.\n");

    printf("Your basket contains:\n");
    for (int k = 0; k < 4; k++) {
        batter[k] = fruitsgathered[k][0];
        printf("%s\n", fruitsgathered[k]);
    }


    while (true) {
        puts("\nPick your tool:\n"
        "1. Suspicious Juicer [Easy]\n"
        "2. Swedish Cheese Grater [?]\n"
        "3. Kitchen Knife [Hard]\n"
        "4. Godmode [Cheater]\n");

        scanf("%d", &kitchenchoice);

        if (!(kitchenchoice > 0 && kitchenchoice < 5)) {
            printf("Input 1-4 to make your choice.\n");
            while((getchar()) != '\n');  // Flush
            continue;
        }

        if (kitchenchoice == 2) {
            printf("Swedish Cheese Grater is not a good tool, try again\n");
        }

        else if (kitchenchoice == 4) {
            printf("Godmode is not allowed here!\n");
        }

        else if (kitchenchoice == 1) {
            suspiciousJuicerGame();
            break;
        }

        else if (kitchenchoice == 3) {
            kitchenKnifeGame();
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
    pthread_t id_flyingfruits, id_dodgingfruits;

    puts("In the cupboard above you notice grandma's Suspicious Juicer.\n"
        "You remember from early childhood just how unreliable it can be.\n"
        "Grandma is waiting for her cake so no time to waste!\n"
        "Set the mixer level:\n"
        "1 | 2 | 3 | 4 WARNING!!!!\n");

    while (true) {
        scanf("%d", &mixerlevel);
        if (!(mixerlevel> 0 && mixerlevel < 5)) {
            printf("Input 1-5 to set the level.\n");
            puts("Set the mixer level:\n"
                   "1 | 2 | 3 | 4 WARNING!!!!\n");
            while((getchar()) != '\n');  // Flush
            continue;
        }

        if (mixerlevel == 1) {
            mixingseconds = 10;
            printf("You are mixing...\n");
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
            printf("You are mixing...\n");
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
            printf("You are mixing...\n");
            while (secondcount <= mixingseconds) {
                switch (secondcount % 3) {
                    case 0: printf("Woosh.\n"); break;
                    case 1: printf("Swoosh.\n"); break;
                    case 2: printf("Wooooooooooosh!!\n"); break;
                    default: ;
                }
                secondcount++;
                sleep(1);
            }

            printf("\nMixing done!!\n");
            puts("Phew! The machine managed to handle the massive stress of mixing level 3. Lucky this time nothing bad\n"
                "happened and you have an OK Juice in the machine. Just some luck needed with Grandma's Oven next and you surely know that\n"
                "she will be happy with your performance!!\n");

            break;
        }

        if (mixerlevel == 4) {
            mixingseconds = 10;
            printf("You are mixing...\n");
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
            sleep(7);

            enableRawMode();
            /* Starting event threads */
            pthread_create(&id_flyingfruits, NULL, flyingFruits, NULL);
            pthread_create(&id_dodgingfruits, NULL, dodgingFruits, NULL);
            pthread_join(id_flyingfruits, NULL);
            pthread_join(id_dodgingfruits, NULL);

            disableRawMode();

            dodgecount = 0;
            puts("You survived all flying fruits with fullfledged grace!\n"
                "The neighbours heard the quarrel and their nosy noses now peak inside of Grandma's blinds.\n"
                "Their eyes grow big and they see a plate covered shiny knight gnistering in the afternoon sun.\n\n"
                "All hail Sir Fruitalot - Tamer of Suspicious Juicers!!\n");
            puts("                           .-.\n"
"                          {{#}}\n"
"          {}               8@8\n"
"        .::::.             888\n"
"    @\\\\/W\\/\\/W\\//@         8@8\n"
"     \\\\/^\\/\\/^\\//     _    )8(    _\n"
"      \\_O_{}_O_/     (@)__/8@8\\__(@)\n"
" ____________________ `~\"-=):(=-\"~`\n"
"|<><><>  |  |  <><><>|     |.|\n"
"|<>      |  |      <>|     |S|\n"
"|<>      |  |      <>|     |'|\n"
"|<>   .--------.   <>|     |.|\n"
"|     |   ()   |     |     |P|\n"
"|_____| (O\\/O) |_____|     |'|\n"
"|     \\   /\\   /     |     |.|\n"
"|------\\  \\/  /------|     |U|\n"
"|       '.__.'       |     |'|\n"
"|        |  |        |     |.|\n"
":        |  |        :     |N|\n"
" \\       |  |       /      |'|\n"
"  \\<>    |  |    <>/       |.|\n"
"   \\<>   |  |   <>/        |K|\n"
"    `\\<> |  | <>/'         |'|\n"
"jgs   `-.|__|.-`           \\ /\n"
"                            ^\n");

            sleep(3);
            printf("You take some time breathing out and wiping fruit juice off your face\n\n");
            sleep(3);
            puts("A big smile enters and spreading from ear to ear. You hear the crowd cheering and you walk proudly up to the juicer.\n"
                "Inside the demolished parts of the juicer a pile of ultra compressed golden batter has formed.\n"
                "It shines bright and the aromas of berries, tarred boots and vegetables form red steams hovering.\n"
                "Grandma's favorite! The hard work paid off!\n"
                "Time to bake.\n");

            break;

        }
    }

}

int roll10() {
    return rand() % 10 + 1;
}

void handleDeath() {
    puts("        __                                           __\n"
"       (**)                                         (**)\n"
"       IIII                                         IIII\n"
"       ####                                         ####\n"
"       HHHH     Madness comes, and madness goes     HHHH\n"
"       HHHH    An insane place, with insane moves   HHHH\n"
"       ####   Battles without, for battles within   ####\n"
"    ___IIII___        Where evil lives,          ___IIII___\n"
" .-`_._\"**\"_._`-.      and evil rules         .-`_._\"**\"_._`-.\n"
"|/``  .`\\/`.  ``\\|    Breaking them up,      |/``  .`\\/`.  ``\\|\n"
"`     }    {     '  just breaking them in    `     }    {     '\n"
"      ) () (  Quickest way out, quickest way wins  ) () (\n"
"      ( :: )      Never disclose, never betray     ( :: )\n"
"      | :: |   Cease to speak or cease to breath   | :: |\n"
"      | )( |        And when you kill a man,       | )( |\n"
"      | || |          you're a murderer            | || |\n"
"      | || |             Kill many                 | || |\n"
"      | || |        and you're a conqueror         | || |\n"
"      | || |        Kill them all ... Ooh..        | || |\n"
"      | || |           Oh you're a God!            | || |\n"
"      ( () )                       -Megadeth       ( () )\n"
"       \\  /                                         \\  /\n"
"        \\/                                           \\/\n"
);
    printf("GAME ENDED\n");
    exit(0);
}

/// Doing Stuff while listening to keyboard from dodgingPlates
void* flyingFruits() {
    int randomswitch;
    printf("Fruits are flying!!\nPrepare to guard LEFT ('A') or guard RIGHT ('D') or die!!\n");
    while (!FLYINGFRUITSEND) {
        randomswitch = roll10();
        if (randomswitch % 2 == 0) {
            printFruitsRight();
        }
        else if (randomswitch > 0) {
            printFruitsLeft();
        }
        printf("Blocked!!\n");
        dodgecount++;
    }
    printf("The fruit storm subsided...\n");
}

void* dodgingFruits() {

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
                        // **********************************************************************
    dodgeright = true;  // Lousy workaround for logic failure somewhere. Spacerabbits are amazing
    dodgeleft = true;   // **********************************************************************

    FLYINGFRUITSEND = true;
}

void printFruitsRight() {
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
        printf("Fruits hit you right in the head and you fell to the ground bleeding your brain out.\n");
        handleDeath();
    }
}

void printFruitsLeft() {
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
        printf("Fruits hit you right in the head and you fell to the ground bleeding your brain out.\n");
        handleDeath();
    }
}

void kitchenKnifeGame() {
    pthread_t id_flyinggoblins, id_dodginggoblins;
    dodgeright = 0;
    dodgeleft = 0;
    dodgecount = 0;
    FLYINGFRUITSEND = 0;
    int runcount = 0;
    char ckg;

    printf("You pick up Grandma's Kitchen Knife and grab it firmly...\n");
    puts("                                                       ___\n"
"                                                      |_  |\n"
"                                                        | |\n"
"__                      ____                            | |\n"
"\\ ````''''----....____.'\\   ````''''--------------------| |--.             _____      .-.\n"
" :.                      `-._                           | |   `''-----''''```     ``''|`: :|\n"
"  '::.                       `'--.._____________________| |                           | : :|\n"
"    '::..       ----....._______________________________| |                           | : :|\n"
"      `'-::...__________________________________________| |   .-''-..-'`-..-'`-..-''-.cjr :|\n"
"           ```'''---------------------------------------| |--'                         `'-'\n"
"                                                        | |\n"
"                                                       _| |\n"
"                                                      |___| cjr\n"
);
    sleep(3);
    printf("Btzzzzz btzz..\n");
    sleep(3);
    puts("It starts glowing and vibrating, there are some ancient norse runes engraved in the cold steel.\n"
        "It is resonating and the blade turns icy blue, you have learnt from watching Lord of The Rings that enemies are nearby.\n"
        "SQUEEEEEEEEEEEEEEEEEK SQUOOOOOOORK!!!\n"
    "A horde of Goblins are amounting over the yonder. No time to ponder - You break the door open and start to defend against the hordes!\n\n");
    sleep(3);

    printf("Use 'A' to slash left, 'D' to slash right, 'J' to jump and 'W' to run\n");
    printf("Combat start! Run towards the Goblins by pressing 'W' rapidly\n");

    enableRawMode();
    while (read(STDIN_FILENO, &ckg, 1) == 1 && runcount < 7) {
        if (ckg == 'w') {
            printf("^\n");
            runcount++;
        }

    }

    printf("Goblins to your right, goblins to your left, goblins everywhere!!\n");

    /* Starting event threads */
    pthread_create(&id_flyinggoblins, NULL, flyingGoblins, NULL);
    pthread_create(&id_dodginggoblins, NULL, dodgingGoblins, NULL);
    pthread_join(id_flyinggoblins, NULL);
    pthread_join(id_dodginggoblins, NULL);

    disableRawMode();

}

/// Doing Stuff while listening to keyboard from dodgingPlates
void* flyingGoblins() {
    int randomswitchkg;
    while (!FLYINGFRUITSEND) {
        randomswitchkg = roll10();
        if (randomswitchkg % 3 == 0) {
            printGoblinsRight();
            puts("                     ______\n"
"                  .-\"      \"-.\n"
"                 /            \\\n"
"                |              |\n"
"                |,  .-.  .-.  ,|\n"
"                | )(__/  \\__)( |\n"
"                |/     /\\     \\|\n"
"      (@_       (_     ^^     _)\n"
" _     ) \\_______\\__|IIIIII|__/__________________________\n"
"(_)@8@8{}<________|-\\IIIIII/-|___________________________>\n"
"       )_/        \\          /\n"
"      (@           `--------` jgs\n"
"\n"
"              FAAAAAAAAAAAAAAAATTSSSSS\n"
);
        }
        else if (randomswitchkg == 1) {
            printGoblinsLeft();
            puts("                              .___.\n"
"          /)               ,-^     ^-.\n"
"         //               /           \\\n"
".-------| |--------------/  __     __  \\-------------------.__\n"
"|WMWMWMW| |>>>>>>>>>>>>> | />>\\   />>\\ |>>>>>>>>>>>>>>>>>>>>>>:>\n"
"`-------| |--------------| \\__/   \\__/ |-------------------'^^\n"
"         \\\\               \\    /|\\    /\n"
"          \\)               \\   \\_/   /\n"
"                            |       |\n"
"                            |+H+H+H+|\n"
"                            \\       /\n"
"                             ^-----^\n"
"\n"
"                      CHOOOOOOOOOOOOOODDDDD\n"
);
        }
        else if (randomswitchkg == 2) {
            printGoblinsFeet();
            printf("Dodged!!\n");
        }
    }
    printf("The Goblin Hordes fled...\n");
}

void* dodgingGoblins() {

    char ckkg;
    while (read(STDIN_FILENO, &ckkg, 1) == 1 && dodgecount < 7) {
        if (!(ckkg == 'a' || ckkg == 'd' || ckkg == 'j')) {
            dodgeright = false;
            dodgeleft = false;
            jump = false;
            continue;
        }
        if (ckkg == 'a') {
            dodgeleft = true;
            dodgeright = false;
            jump = false;
            sleep(1);
            dodgeleft = false;
        }
        else if (ckkg == 'd') {
            dodgeright = true;
            dodgeleft = false;
            jump = false;
            sleep(1);
            dodgeright = false;
        }

        else if (ckkg == 'j') {
            jump = true;
            dodgeright = false;
            dodgeleft = false;
            sleep(1);
            jump = false;
        }
    }
    jump = true;        // **********************************************************************
    dodgeright = true;  // Lousy workaround for logic failure somewhere. Spacerabbits are amazing
    dodgeleft = true;   // **********************************************************************

    FLYINGFRUITSEND = true;
}

void printGoblinsRight() {
    sleep(1);
    printf("3\n");
    sleep(1);
    printf("2\n");
    sleep(1);
    printf("1\n");
    sleep(1);
    printf("Slash RIGHT!!\n");
    sleep(1);
    if (!dodgeright) {
        printf("Goblins hit you from the right and you fell to the ground bleeding your brain out.\n");
        handleDeath();
    }
    dodgecount++;
}

void printGoblinsLeft() {
    sleep(1);
    printf("3\n");
    sleep(1);
    printf("2\n");
    sleep(1);
    printf("1\n");
    sleep(1);
    printf("Slash LEFT!!\n");
    sleep(1);
    if (!dodgeleft) {
        printf("Goblins hit you from the left and you fell to the ground bleeding your brain out.\n");
        handleDeath();
    }
    dodgecount++;
}

void printGoblinsFeet() {
    sleep(1);
    printf("JUMP!!\n");
    sleep(1);
    if (!jump) {
        printf("Goblins gobbled your feet and you fell to the ground bleeding.\n The thirsty hordes take turns splitting your body into parts.\n");
        handleDeath();
    }
    dodgecount++;
}
