#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printNiceFlag(int inchoice);
void printBadFlag(int inchoice);

int main(void) {

  int userchoice;

  while (true) {
      puts(
  "\x1B[32m                                          ***  ***\n"
  "                                      **************\n"
  "                                     ***** **** ** ***\n"
  "                                *** *****  *         **\n"
  "                              **********   *   ** ***\n"
  "                              ********       *   *****\n"
  "                            *******         *      ***\n"
  "                         * ******* **       *     **\n"
  "                       ******    *** *      *    **\n"
  "                      *******    *  * ******     *\n"
  "                     ********* ***    *          *\n"
  "                    **********         *          *\n"
  "                   *   ****                        *\n"
  "                      *****            **           *\n"
  "                      *** *             *          *\n"
  "                    **   *              *         *\n"
  "                   **   *               *          *\n"
  "                   ***  *               *          *\n"
  "                  **  *               * *           *\n"
  "                  **  *             **** **         *\n"
  "                  **  *             *      *       *\n"
  "               ****                *      **       *\n"
  "               ***   *             *     *          *\n"
  "              ***                  *    *           *\n"
  "             ****  ***            *    *             *\n"
  "          ******* *             **   **             *\n"
  "          *****   *           **   ***                *\n"
  "        ****      *          **    *                   *\n"
  "      ****        *         **     *                  *\n"
  "    *****         *         *      *                 *\n"
  "    ****          *         *       *               *\n"
  "    **             *       *        *              *\n"
  "    ******         *       *       *              *\n"
  "    **            *         *      **           *\n"
  "    ****                     ** **  ***    ****\n"
  "    ***        *  *            * *    ****\n"
  "    ***       ** *            *\n"
  "    ****     *****          ***\n"
  "     **     *   *         ***\n"
  "      **   *    **        **\n"
  "        **       *        *   **\n"
  "             **  *        *  **\n"
  "           ****   *       ** **\n"
  "          *** **   *      *\n"
  "          *   **  **   ****\n"
  "          *  *******  *\n"
  "          ** * ******* *           **\n"
  "           ********    *         ***  *\n"
  "                                 ******\x1B[m\n");

      printf("Welcome to the amazing World of Scandinavia!\n");
      printf("The Northern Region of Europe where we still have toilet paper and zero tofu dreg constructions.\n");
      printf("Pick a country to learn more about from the list below:\n\n");

      puts(
          "1. Norway\n"
          "2. Sweden\n"
          "3. Finland\n"
          "4. Denmark\n"
          "5. Iceland\n"
          "6. EXIT\n");


      while (true) {
          scanf("%d", &userchoice);
          if (userchoice > 0 && userchoice < 7) {
              break;
          }
          printf("Invalid choice. Please input integer number.\n");
          while((getchar()) != '\n');  // Flush
      }

      switch (userchoice) {
          case 1:
              printBadFlag(userchoice);
              puts("\nNorway is a great country if you want to have a lot of money, eat salmon and have good societal care for families.\n"
                   "It is said to have amazing nature fjords and cities with trams. If you ever encounter a Norweigan person you will know\nit just by listening,"
                   " Norweigan people always sounds happy and euforic even when they are mad.\n"
                   "Amongst metal people it is viewed as one of the countries with the trvest Black Metal with bands such as:\n"
                   "Burzum, Immortal, Mayhem, Gorgoroth, Darkthrone, Satyricon and more.\n");
              break;

          case 2:
              printNiceFlag(userchoice);
              puts("\nSweden is the Land of Lagom and where Kungen lives. Swedes consist mainly of two kinds:\n"
                   "The nerds who fear the sun and the people who grilla on Saturdays. If you need to know directions to stays during your visit,\n"
                   "you better not ask a Swede since they will mainly look confused on why you are asking them and not asking your phone.\n"
                   "If you want to know a Swede you better treat it with fika or alcohol. Otherwise there is no guarantee for speech.\n");
              break;

          case 3:
              printNiceFlag(userchoice);
              puts("\nFinland is the Land of Forests, Lakes and Metal.\n"
                  "They tend to have as many nerds as their neighbouring country Land of Lagom and historically great musicians and demo groups have"
                  "been bred here. Finland tend to rank amongst the highest of coffee consumption, happiness per capita and excellent grades in education.\n"
                  "Many homes have their own Sauna either separate on the land they own or in the basement of appartment buildings.\n"
                  "If you want to stay in Finland for a longer duration, forget about English and learn Finnish instead, they can find it rude otherwise.\n"
                  "Sauna, Sisu, Memma and Power Metal \\m/\n");
              break;

          case 4:
              printNiceFlag(userchoice);
              puts("\nDenmark is mostly known for Pølse, Danish pastry and people that sound funny when they speak. They tend to be kind and pleasant people to be with\n"
                   "and it must be due to their tobacco consumption, that or The Spirit of Hygge. No mountains and close to the sea wherever you are.\n"
                   "The Land of Lego with its signature amusement park Legoland. They score well in being one of the happiest countries so if you are depressed,\n"
                   "or want to smoke during pregnancy, you should move here.");
              break;

          case 5:
              printBadFlag(userchoice);
              puts("\nIceland is a country, and maybe there were Vikings there in former ages but after all volcano eruptions they are now sheep farmers.\n"
                   "The two most popular sports in Iceland are football and handball.\n"
                   "Nature is impressive and amazing with goodies of hot springs, volcanoes, canyons, ice caves, aurora borealis and anything you can dream of.\n"
                   "If you need a quiet place with having to drive about 1 hour to the closest store with sparce opening hours Iceland is the country for you.\n"
                   "They also have no Mc Donald's.\n");
              break;

          case 6:
              exit(0);

          default:
              while((getchar()) != '\n');  // Flush

      }

      while((getchar()) != '\n');  // Flush
      printf("Press enter to get back to the menu.\n");
      while( getchar() != '\n' );

      //return 0;
  }
    return 0;

}

void printNiceFlag(int inchoice) {

    char FIRSTCOLOR[] = "\x1B[34m";
    char SECONDCOLOR[] = "\x1B[33m";

    if (inchoice == 3) {
        strcpy(FIRSTCOLOR,"\x1B[37m");
        strcpy(SECONDCOLOR, "\x1B[34m");
    }

    else if (inchoice == 4) {
        strcpy(FIRSTCOLOR,"\x1B[31m");
        strcpy(SECONDCOLOR, "\x1B[37m");
    }

    printf("%s#####%s|**|%s############\n", FIRSTCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|**|%s############\n", SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|**|%s############\n", SECONDCOLOR, FIRSTCOLOR);
    printf("%s*****+**+************\n", SECONDCOLOR);
    printf("%s#####%s|**|%s############\n", FIRSTCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|**|%s############\n", SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|**|%s############\033[m\n", SECONDCOLOR, FIRSTCOLOR);

}

void printBadFlag(int inchoice) {
    char FIRSTCOLOR[] = "\x1B[31m";
    char SECONDCOLOR[] = "\x1B[37m";
    char THIRDCOLOR[] = "\x1B[34m";

    if (inchoice == 5) {
        strcpy(FIRSTCOLOR,"\x1B[34m");
        strcpy(THIRDCOLOR, "\x1B[31m");
    }

    printf("%s#####%s|%s**%s|%s############\n", FIRSTCOLOR, SECONDCOLOR, THIRDCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|%s**%s|%s############\n", SECONDCOLOR, THIRDCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|%s**%s|%s############\n", SECONDCOLOR, THIRDCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("%s―――――+%s**%s+――――――――――――\n", SECONDCOLOR, THIRDCOLOR, SECONDCOLOR);
    printf("%s======**=============\n", THIRDCOLOR);
    printf("%s―――――+%s**%s+――――――――――――\n", SECONDCOLOR, THIRDCOLOR, SECONDCOLOR);
    printf("%s#####%s|%s**%s|%s############\n", FIRSTCOLOR, SECONDCOLOR, THIRDCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|%s**%s|%s############\n", SECONDCOLOR, THIRDCOLOR, SECONDCOLOR, FIRSTCOLOR);
    printf("#####%s|%s**%s|%s############\033[m\n", SECONDCOLOR, THIRDCOLOR, SECONDCOLOR, FIRSTCOLOR);
}
