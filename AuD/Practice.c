#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


int programToRun = 7;

const float pi = 3.14;

void printASCIICode();
void reverseString();
void rot13();
void lightCalculator();
void circleRadius();
void calculator();
void mathExam();
void diceRoll();

int main()
{
    switch (programToRun)
    {
        case 0: printASCIICode();  break;
        case 1: reverseString();  break;
        case 2: rot13(); break;
        case 3:  lightCalculator(); break;
        case 4: circleRadius(); break;
        case 5: calculator(); break;
        case 6: mathExam(); break;
        case 7: diceRoll(); break;
    }
    printf("\n");
    return 0;
}

void printASCIICode()
{
    char character;
    scanf("%c", &character);
    printf("'%c' Has the ASCII Code : %d",character,character);
}

void reverseString()
{
    printf("Type a String (Under 20 characters) \n");
    char String[20];
    fgets(String, sizeof(String), stdin);

    int length = strlen(String);
    if (length > 20) { printf("The string has to be under 20 characters long! \n"); reverseString(); return;}

    char returnString[20];
    int end = length-1, i;
    for (i = 0; i < length; i++)
    {
        returnString[end] = String[i];
        end--;
    }
    returnString[i] = '\0'; //cut off the String after the intended end
    printf("%s", returnString);
}

void rot13() //Rot13 is an ancient cryptography procedure. It encrypts a message by shifting each character 13 letters in alphabetical order (modulo z).
{
    printf("Type a letter that you want to be encrypted\n");
    int charCode;
    scanf("%c", &charCode);

    short capitalized = -1;
    if (charCode >= 97 && charCode <= 122) {capitalized = 0;}
    else if (charCode >= 65 && charCode <= 90) {capitalized = 1;}
    if (capitalized == -1) {printf("Please type an actual letter\n"); return;}

    charCode+= 13;
    switch (capitalized)
    {
        case 0: if (charCode > 122) {charCode = 96 + charCode -122; } break;
        case 1: if (charCode > 90) {charCode = 64 + charCode -90; } break;
    }
    printf("Encrypted character: %c", charCode);
}


void lightCalculator()
{
    printf("Please type a decimal number, anything else becomes a 0\n");
    int x;
    scanf("%d", &x);
    printf("Please type a second decimal number, anything else becomes a 0\n");
    int y;
    scanf("%d", &y);

    int sum = x+y, difference = x-y, product = x*y;
    float quotient = (float)x/(float)y;

    printf(" The sum of your numbers is: %d\n The difference of your numbers is: %d\n The product of your numbers  is: %d\n", sum, difference, product);
    printf(" The quotient of your is: %f\n", quotient);

}

void circleRadius()
{
    printf("Please type in a radius of a circle\n");
    float radius;
    scanf("%f", &radius);
    float area = pi*radius*radius;
    printf("Your circle has an area of approximately %f", area);
}

void calculator()
{
    int x, y;
    char operator;
    char operators[5] = {'+', '-', '/', '*', '%'};
    printf("Please type an integer number\n");
    scanf(" %d", &x);
    printf("Please type a second integer number\n");
    scanf(" %d", &y);
    printf("Please type an operator (+, -, /, *, %)\n");
    scanf(" %c", &operator);

    int i;
    for (i = 0; i < 6; i++)
    {
        if (operator == operators[i]) {break;}
    }
    if (i == 5) {printf("That is not a valid operator."); return;}

    float result;
    switch (i)
    {
        case 0: result = x+y; break;
        case 1: result = x-y; break;
        case 2: result = (float)x/(float)y; break;
        case 3: result = x*y; break;
        case 4: result = x%y; break;
    }

    printf("%d %c %d = %f", x, operators[i], y, result);
}

void mathExam()
{
    long timeStart = time(NULL);
    srand(timeStart);
    int correctAnswers = 0;
    for (int i = 5; i > 0; --i)
    {
        int a = rand() % 19 + 1;
        int b = rand() % 19 + 1;
        int s;

        printf("%d + %d = ", a, b);

        scanf("%d", &s);

        if(s == a + b){ printf("Correct\n"); ++correctAnswers;}
        else {printf("Incorrect\n");}
    }

    printf("You got %d/5 questions correct\n", correctAnswers);
    long timeEnd= time(NULL) - timeStart;
    printf("It took you %ld seconds to complete the Test", timeEnd);
}

void diceRoll()
{
    srand(time(NULL));
    int diceNum = rand() % 6 +1;
    /*
     *    0, 1, 2          0     0
     *    3, 4, 5  -> 5 =     0     = 1, 0, 1, 0, 1, 0, 1, 0, 1
     *    6, 7, 8          0     0
    */
    int d[9];
    if (diceNum % 2 == 1) {d[4] = 1;}
    else if (diceNum == 6) {d[3] = 1; d[5] = 1;}

    if (diceNum > 1) {d[0] = 1; d[8] = 1;}
    if (diceNum > 3) {d[2] = 1; d[6] = 1;}

    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0) {printf("\n");}

        if (d[i] == 1) { printf("O ");}
        else { printf("  ");}
    }
}