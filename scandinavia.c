#include <stdbool.h>
#include <stdio.h>
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
  "                                 ******\033[m\n");

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
              break;

          case 2:
              printNiceFlag(userchoice);
              break;

          case 3:
              printNiceFlag(userchoice);
              break;

          case 4:
              printNiceFlag(userchoice);
              break;

          case 5:
              printBadFlag(userchoice);
              break;

          default:
              while((getchar()) != '\n');  // Flush
              return 0;
      }

      return 0;
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