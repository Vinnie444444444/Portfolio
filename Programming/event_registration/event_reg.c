#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#define DISTMAX 100
#define DISTMIN 1
#define COSTMAX 200
#define COSTMIN 50
#define JMAX 150
#define JMIN 50
#define CHARITYMAX 30
#define CHARITYMIN 3
#define SIZE 80
#define STRINGSIZE 4
#define FOLDER_PATH "C:\Users\User\somefolder"


typedef struct holder{

    char orgzName[80];
    double raceDistance;
    double raceCost;
    double charityPercentage;
    double shirtPrice;
    char fixedInput[80];
    char shirtSize[1];
    int shirtctr;
    unsigned int raceCtr;
    struct holder* nextNodePtr;
    unsigned int shirtsSold;
    double shirtSales;
    double charityShirt;
    double finalSale;
    double totalCharity;
    unsigned int registrants;
    double charityAmount;
    double totalSales;
    bool check;
    
}Holder;
struct final
{
    unsigned int shirtsSold;
    double shirtSales;
    double charityShirt;
    double finalSale;
    double totalCharity;
    unsigned int registrants;
    double charityAmount;
    double totalSales;
};
const char password[7] = { "B!k34u" };
const char* sizes[STRINGSIZE] = { "(s)mall", "(m)edium", "(l)arge" , "(x)tra - large" };
const char* yesno[STRINGSIZE] = { "(Y)","(y)","(N)","(n)" };
void adminSetUp(Holder* name);
char getValidChar(char* shirtSizeptr, const char* sizesPtr[], char prompt[]);
bool getValidDouble(int MAX, int MIN, const char* inputtedPtr, double* variablePtr);
void updateTotals(Holder* name, struct final* names);
bool adminLogin(const char password[]);
bool getName(char* namePtr);
void registrationMode(Holder* registerOrgz, struct final* names);
void validCredit();
void theReceipt(double costPtr, int shirtPtr, double percentPtr, double jerseyPtr);
void initializer(Holder* name, struct final* names);
void insertNode(Holder** headPtr, char orgName[], double costptr, double distPtr, double percentPtr, double shirtPrice);
void printList(Holder* listPtr);
bool orgzSearch(Holder* headPtr, Holder** orgzPtr,char nameInput[]);
void fgetsRemoveNewLine(char* fixedInputPtr);
void freeNodes(Holder** headPtr);
void fileList(Holder* listPtr);
void finalUpdate(Holder* update, struct final* updates);


int main()
{
     Holder Caller;
    struct final Finals;
    Holder* headNodePtr = NULL;
    Holder* orgzPtr;
    bool mOrgz = false;
    initializer(&Caller, &Finals); //initializes variables
    if (adminLogin(password)) //if password was correct
    {
        do { //go through admin setup
             mOrgz = false;
            adminSetUp(&Caller);
            char answer;
            char prompt[80] = "Do you want to add another Organization? (y)es or (n)o";          
            getValidChar(&answer, yesno, prompt);



           //if they said yes to adding another organization
            if (answer == 'y')
            {
                //inserts new node and updates totals
                insertNode(&headNodePtr, Caller.orgzName,Caller.raceCost, Caller.raceDistance, Caller.charityPercentage, Caller.shirtPrice);
                updateTotals(headNodePtr, &Finals);
                mOrgz = true;
            }
            

            //if they said yes itll repeat
        } while (mOrgz == true);
        //insets node
        insertNode(&headNodePtr, Caller.orgzName, Caller.raceCost, Caller.raceDistance, Caller.charityPercentage, Caller.shirtPrice);
        printList(headNodePtr); //prints linked list and prompts
      
        

            char getName[80];
            do
            {//prompts for name of organization to register for
                puts("Enter the name of the organization you want to register.   ");

                fgetsRemoveNewLine(getName);
            } while (!orgzSearch(headNodePtr, &orgzPtr, getName)); //while the name is found in the linked list



            printf("The bike jersey cost is %.2lf\n", orgzPtr->shirtPrice);
            printf("You entered %.2lf%% of the bike race to go to charity\n", orgzPtr->charityPercentage);


            while (orgzPtr->check) //while the admin didnt put quit to exit registration mode
            {
                registrationMode(orgzPtr, &Finals); //enter registration mode to update totals
                updateTotals(orgzPtr, &Finals); //update totals
                finalUpdate(orgzPtr, &Finals); //finalize totals for later
        
            }
        
        
    }


    fileList(headNodePtr); //prints the organizations info to a file and displays whats shown in the file
   

    freeNodes(&orgzPtr); //de-allocates memory from linked list
    
}
void insertNode(Holder** headPtr, char orgName[], double costPtr, double distPtr, double percentPtr, double shirtPrice)
{
    // Create a new node 
    Holder* newNodePtr = malloc(sizeof(Holder));
    strcpy(newNodePtr->orgzName, orgName);
    newNodePtr->raceCost = costPtr;
    newNodePtr->raceDistance = distPtr;
    newNodePtr->charityPercentage = percentPtr;
    newNodePtr->shirtPrice = shirtPrice;
    newNodePtr->nextNodePtr = NULL;
    
    // If the linked list is empty, make the new node the head 
    if (*headPtr == NULL)
    {
        *headPtr = newNodePtr;
        return;
    }

    // If the node is to be inserted before the head of the list, 
    // make it the new head 
    if (strcmp(orgName, (*headPtr)->orgzName) < 0)
    {
        newNodePtr->nextNodePtr = *headPtr;
        *headPtr = newNodePtr;
        return;
    }

    // Find the appropriate place to insert the new node 
    Holder* current = *headPtr;
    while (current->nextNodePtr != NULL &&
        strcmp(current->nextNodePtr->orgzName, orgName) < 0)
    {
        current = current->nextNodePtr;
    }

    // Insert the new node 
    newNodePtr->nextNodePtr = current->nextNodePtr;
    current->nextNodePtr = newNodePtr;
}

bool orgzSearch(Holder* headPtr, Holder** orgzPtr, char nameInput[])
{
    
        bool check = false;
        //creating pointer to traverse through linked list
        Holder* temp = headPtr;
        //traversing through linked list
        while (temp != NULL)
        {
            //checking if name is found
            if (strcmp(temp->orgzName, nameInput) == 0)
            {
                //making the found node the main node
                *orgzPtr = temp;
                
                check = true;
            }
            //else move to the next node
            temp = temp->nextNodePtr;
        }
    
    return check;
}
void printList(Holder* listPtr)
{
    //if pointer has something in it
    if (listPtr != NULL)
    {
        printf("%s", "You can register for one of the following bike races and a percentage will be raised for that organization. \n\n");

        Holder* currentPtr = listPtr;
        
        //while theres a structure print the following 
        puts("Organization      Distance        Cost        Percentage");
        while (currentPtr != NULL)
        {
            
            printf("%s ", currentPtr->orgzName);
            printf("              %.2lf miles", currentPtr->raceDistance);
            printf("        $%.2lf ", currentPtr->raceCost);
            printf("        %%%.2lf \n", currentPtr->charityPercentage);
            //continue onto next structure in linked list
            currentPtr = currentPtr->nextNodePtr;
        }
    }
    
    else
    {
        puts("List is empty");
    }
}


void fgetsRemoveNewLine(char* fixedInputPtr)
{
    char input[SIZE]; // created character array for input
    fgets(input, SIZE, stdin); // get input

    if (input[strlen(input) - 1] == '\n') // if theres a newline then remove it
    {
        input[strlen(input) - 1] = '\0'; // removes newline
    }
    strcpy(fixedInputPtr, input); // updates fixed input to user input with the newlien removed
}

void adminSetUp(Holder* name)
{

    puts("Enter organization name (Will not ask for validation)"); // prompt
    fgetsRemoveNewLine(name->fixedInput); // calls function to remove null character
    strcpy(name->orgzName, name->fixedInput);
    do
    {
        puts("Enter Cost "); // prompt
        fgetsRemoveNewLine(name->fixedInput);// calls function to remove null character


    } while (!getValidDouble(DISTMAX, DISTMIN, name->fixedInput, &name->raceCost));// while validDouble returns false repeat untill valid double entered



    do // loop so that if the input isnt a double it will re prompt
    {
        puts("Enter Distance"); // prompt
        fgetsRemoveNewLine(name->fixedInput);// calls function to remove null character

    } while (!getValidDouble(COSTMAX, COSTMIN, name->fixedInput, &name->raceDistance)); // while validDouble returns false repeat untill valid double entered

    do
    {
        printf("Enter sales price of jersey for %s\n", name->orgzName);
        fgetsRemoveNewLine(name->fixedInput);

    } while (!getValidDouble(JMAX, JMIN, name->fixedInput, &name->shirtPrice));

    do
    {
        printf("Enter percentage of the bike race sales that will be donated to %s\n", name->orgzName);
        fgetsRemoveNewLine(name->fixedInput);

    } while (!getValidDouble(CHARITYMAX, CHARITYMIN, name->fixedInput, &name->charityPercentage));

}


char getValidChar(char* shirtSizePtr, const char* sizesPtr[], char prompt[])
{

    bool goat = true; // set bool flag to true
    char checker; // declare the variabel that will be storing input

    while (goat) // while it is true go through the loop
    {
        printf("%s\n", prompt);

        checker = tolower(getchar()); // getting a single character and lowers it to allow uper case entries

        while (getchar() != '\n');
        for (int i = 0; i < STRINGSIZE; i++) // for loop to go through each string in the array which is four times for the four sizes.
        {
            if (sizesPtr[i][1] == checker) // checks index 1 of array to what the user inputted. 
            {
                goat = false; // if input was valid it sets bool to false and ends the while loop
            }
        }
    }

    strcpy(shirtSizePtr, &checker);
    return checker; // return value
}

bool getValidDouble(int MAX, int MIN, const char* inputtedPtr, double* variablePtr)
{
    char* end; // character to be compared to check its not a character and is a double
    errno = 0; // error for when o1ut of range
    double validDouble = strtod(inputtedPtr, &end); //makes the input a double for checking against character, min and max
    bool validCheck = false; //sets bool to false so if it doesnt get updated it will return false

    if (end == inputtedPtr) // if the input is a character such as end it will give invalid double since its still a string
    {
    }
    else if ('\0' != *end) {  // if theres a charater after the number it throws this error
    }
    else if ((validDouble == LONG_MAX || validDouble == LONG_MIN) && ERANGE == errno) { //How to correctly use this 
        while (getchar() != '\n');
    }
    else if (validDouble > MAX) { // if its greater than the max input throw error
    }
    else if (validDouble < MIN) { // if input is to small
    }
    else { // if the input is a valid double then change the checker to true which ends up returning true
        validCheck = true;
        *variablePtr = strtod(inputtedPtr, &end); // converts string into double and sets it to cost pointer
    }
    if (!validCheck)
    {
        printf("Error: Enter value from %d to %d\n", MIN, MAX);
    }
    return validCheck;


}



bool adminLogin(const char password[])
{
    bool bbo = false; // sets to false so if a bad passwords entered then it wont need to be changed
    unsigned int i = 0; // counter so that only 3 attemtps are allowed
    while (i < 3) // while counter is less than three prompt
    {
        char enter[80]; //stores input
        puts("Enter admin pin ");
        fgetsRemoveNewLine(enter); //removes newline from input

        if (strcmp(enter, password) == 0) //if the password equals the input
        {
            bbo = true;  //sets bool to true
            puts("Set up the fundraising information for the organization. ");
            i = 4; // sets counter to 4 to end loop 
        }
        else
        {
            puts("Error: the password is incorrect"); //error from wrong password
        }
        i++; //counter so that it can run at most 3 times
    }
    if (i == 3) //if it equals 3 which is only possible from 3 bad inputs
    {
        puts("Exiting admin set-up"); //exits set up 
    }
    return bbo; //returns the result of the function
}

void registrationMode(Holder* registerOrgz, struct final* names)
{
    registerOrgz->raceCtr = 1;
    char name[80];
    
    if (!getName(name))
    {   //prompts for getValidChar
        printf("Do you want to purchase a jersey for %.2lf\n", registerOrgz->shirtPrice);
        char prompt1[150] = { "Please enter y or n" };
        char prompt2[150] = { "Enter your size (s)mall, (m)edium, (l)arge, or (x)large" };
        char prompt3[50] = { "Do you want a receipt(y)es or (n)o ?" };
        char comp;

        //sets variable to inputted char
        comp = getValidChar(registerOrgz->shirtSize, yesno, prompt1);

        names->registrants++;

        if (comp == 'y') //if input was yes to a jersey
        {
            getValidChar(registerOrgz->shirtSize, sizes, prompt2); //ask what size of jeysey
            //set jersey to 1 for calcuations
            names->shirtsSold=1; 
            registerOrgz->shirtctr = 1;
            printf("The entered size: %c\n\n\n\n\n", registerOrgz->shirtSize[0]);
        }           //set counter to 0 for calculations
        else { registerOrgz->shirtctr = 0; names->shirtsSold = 0;
        }

        //sets cost
        double theCost = (registerOrgz->shirtctr * registerOrgz->shirtPrice) + registerOrgz->raceCost;
        double charity = ((registerOrgz->shirtPrice* registerOrgz->shirtctr + registerOrgz->raceCost) * (registerOrgz->charityPercentage / 100));
        printf("Your total cost is %.2f Enter your Credit Card (will only accept XXXX-####-##### input, throws exepction otherwise)\n", theCost);
        validCredit();
        printf("Thank you %s for your purchase. %.2lf of the ticket sales will go to charity\n", name, charity);

        //if they inputted yes to a receipt
        comp = getValidChar(registerOrgz->shirtSize, yesno, prompt3);
        if (comp == 'y')
        {
            theReceipt(registerOrgz->raceCost, names->shirtsSold, registerOrgz->charityPercentage, registerOrgz->shirtPrice);
        }
        

    }//if they failed the password
    else if (!adminLogin(password))
    {
        puts("Error-- Failed Password, Re prompting Name");

    }
    else//if they entered the correct password to exit registration mode
    {
        puts("password was entered, exiting program ");
        registerOrgz->check = false;
    }

    puts("Could not figure out how to change what organization user can choose. Can only register for one organization right now.");
}
void theReceipt(double costPtr, int shirtPtr, double percentPtr, double jerseyPtr)
{
    double totalCost = 0; // cost for later
    double donation = 0;
    
    
    printf("Race: %.2lf\n", costPtr);
    if (shirtPtr == 1) //if they wanted a shirt
    {
        
        printf("Jersey %.2lf\n", jerseyPtr);
    }
         
        totalCost = (jerseyPtr * shirtPtr)+ costPtr;

    donation = totalCost * (percentPtr / 100);
    printf("Total Cost %.2lf\nDonation to Charity %.2lf\n\n", totalCost, donation);
}
void validCredit()
{
    // variables to be used in the function
    char str[20]; // stores value
    int l = 0; // counter 1
    int b = 0; //counter 2

    //bool for making sure all three parts of the credit card are valied
    bool bmo = false; 
    bool xmo = false;
    bool mmo = false;


    do
    {
        
        fgets(str, 20, stdin); //gets credit card input
        char* token = strtok(str, "-"); // creates token to store the all the values untill theres a "-"
        l = strlen(token); //sets the legnth of the input 
        for (int i = 0; i < l; i++) //for loop using the length of the token to go through the string one character at a time
        {
            if (token[i] >= 'A' && token[i] <= 'Z') // if the input is a letter
            {
                b++; // if its a letter than second counter one is added
            }
            if (b == 4) // if the counter is 4 which is only attainable through all input being valid
            {
                bmo = true; //sets first check to true

            }
        }
        b = 0; // resets counter for second string
        token = strtok(NULL, "-"); //sets token to second part of the string untill "-" , its the middle part of the credit card
       
            l = strlen(token); // sets l to the legnth of the string
            for (int i = 0; i < l; i++)//for loop using the length of the token to go through the string one character at a time
            {
                //same algorithm as first part of string but checking for numbers and not letters
                if (isdigit(token[i])) //if the character is a digit
                {
                    b++;
                    bmo = false;
                }
                if (b == 4)
                {
                    bmo = true; //second flag to true

                }

            }


                token = strtok(NULL, "-"); //token to final part of the string which will hit null
                b = 0; //resets counter
                l = strlen(token);
                for (int i = 0; i < l; i++)
                {
                    if (isdigit(token[i]))
                    {
                        b++;
                        bmo = false;
                    }
                    if (b == 5)
                    {
                        bmo = true;

                    }
                
            
        }
        //while all the flags are true then ends but if not it re promts for credit card untill valid
    } while (bmo == false && xmo == false && mmo == false);
    
}


bool getName(char* racerNamePtr)
{
    bool joint = false; // bool for if its quit
    puts("Enter your first name and last name to register for the ride (Enter quit to exit)");
    char name[80];
    fgetsRemoveNewLine(name); //removed newline from input

    if (strcmp(name, "quit") == 0) //if the input entered is quit 
    {
        joint = true; //bool is set to true  for later 

    }
    else
    {
        strcpy(racerNamePtr, name); // stores input to the name in the structure

    }
    return joint; // returns if quit was entered or a name was
}

void initializer( Holder* name, struct final* names)
{
    name->shirtctr = 0;
    names->shirtsSold = 0;
    names->shirtSales = 0;
    names->charityShirt = 0;
    names->finalSale = 0;
    names->totalCharity = 0;

    names->registrants = 0;
    names->charityAmount = 0;
    names->totalSales = 0;

}
void updateTotals(Holder* name, struct final* names)
{

    names->totalSales += names->registrants * name->raceCost;
    names->charityAmount += names->totalSales * (name->charityPercentage / 100);
    names->shirtSales += names->shirtsSold * name->shirtPrice;
    names->charityShirt = names->shirtSales * (name->charityPercentage / 100);
    names->finalSale = (names->totalSales) + (names->shirtSales);
    names->totalCharity = names->charityAmount + names->charityShirt;

}



void fileList(Holder* listPtr)
{
    FILE* filePtr;
    filePtr = fopen("org1.txt", "w");


    if (listPtr != NULL)
    {
        printf("%s", "The Exported File: \n\n");

        Holder* currentPtr = listPtr;


        while (currentPtr != NULL)
        {
            fprintf(filePtr, "Organization Name: %s", currentPtr->orgzName);
            fprintf(filePtr, "Distance: %.2lf\n", currentPtr->raceDistance);
            fprintf(filePtr, "Race Cost: %.2lf\n", currentPtr->raceCost);
            fprintf(filePtr, "Registrants: %u\n", currentPtr->raceCtr);
            fprintf(filePtr, "Total Race Sales: %.2lf\n", currentPtr->totalSales);
            fprintf(filePtr,"Jersey Cost: %.2lf\n", currentPtr->shirtPrice);
            fprintf(filePtr,"Total Jersey Sales: %.2lf\n", currentPtr->shirtSales);
            fprintf(filePtr,"Total Sales: %.2lf\n", currentPtr->finalSale);
            fprintf(filePtr,"Charity Percent: %.2lf\n", currentPtr->charityPercentage);
            fprintf(filePtr,"Charity Amount: %.2lf\n\n", currentPtr->charityAmount);

            // display and go to next node
            printf("Organization: %s\n",currentPtr->orgzName );
            printf("Distance: %.2lf\n", currentPtr->raceDistance);
            printf("Race Cost: %.2lf\n", currentPtr->raceCost);
            printf("Registrants: %u\n", currentPtr->raceCtr);
            printf("Total Race Sales: %.2lf\n", currentPtr->totalSales);
            printf("Jersey Cost: %.2lf\n", currentPtr->shirtPrice);
            printf("Total Jersey Sales: %.2lf\n", currentPtr->shirtSales);
            printf("Total Sales: %.2lf\n", currentPtr->finalSale);
            printf("Charity Percent: %.2lf\n", currentPtr->charityPercentage);
            printf("Charity Amount: %.2lf\n\n", currentPtr->charityAmount);
            fclose(filePtr);
            currentPtr = NULL;
        }
    }

    else
    {
        puts("List is empty");
    }
    
}

void finalUpdate(Holder *update, struct final *updates)
{
    update->shirtsSold = updates->shirtsSold;
    update->shirtSales = updates->shirtSales;
    update->charityShirt = updates->charityShirt;
    update->finalSale = updates->finalSale;
    update->totalCharity = updates->totalCharity;
    update->registrants = updates->registrants;
    update->charityAmount = updates->charityAmount;
    update->totalSales = updates->totalSales;

}



void freeNodes(Holder** headPtr)
{
    Holder* currentPtr = *headPtr;
    Holder* nextNodePtr = NULL;

    while (currentPtr != NULL)
    {
        nextNodePtr = currentPtr->nextNodePtr;
        free(currentPtr);
        currentPtr = NULL;
    }

    *headPtr = NULL;
}