#include <stdio.h>
#include <string.h>
#include <ctype.h>

enum {Create = 1, Read = 2, Update = 3, Delete = 4, Exit = 5};
enum {Yes = 1, No = 2};
enum {Continue, Break};
enum {FirstName = 1, MiddleName = 2, LastName = 3, Age = 4, Salary = 5, All = 6};
enum {Done};

typedef char string[255];

typedef struct {
int id;
string firstName;
string middleName;
string lastName;
int age;
float salary;
} Person;

void initializeDb(Person *persons, int *length);
void instruction();
void validateUserChoice(int *userChoice);
void selectProcess(int *userChoice, Person *persons, int *length, int *iterator, int *idCounter);
void startProcess(int *userChoice, Person *persons, int *length, int *iterator, int *idCounter);
void insertData(Person *persons, int *length, int *idCounter);
void displayData(Person *persons, int *length);
void updateData (Person *persons, int *length);
void deleteData (Person *persons, int *length);

int main()
{
Person *pPersons = NULL;
int *pDbSize = NULL;
int *pUserChoice = NULL;
int *pIterator = NULL;
int *pIdCounter = NULL;

int dbSize = 0, userChoice = 0, dbSize1 = 0, iterator = 0, idCounter = 1;

pDbSize = &dbSize;
pUserChoice = &userChoice;
pIterator = &iterator;
pIdCounter = & idCounter;

printf("\nEnter the size of your database: ");
scanf("%d", pDbSize);

Person persons[*pDbSize];
pPersons = persons;

initializeDb(pPersons, pDbSize);

while(*pIterator == Continue)
{
instruction();
scanf("%d", pUserChoice);

startProcess(pUserChoice, pPersons, pDbSize, pIterator, pIdCounter);
}

return 0;
}

void deleteData(Person *persons, int *length)
{
int *pId = NULL, *pAge = NULL, *pConfirm = NULL, *pDataToDelete = NULL, *pIsDoneEdit, *pSaveChanges = NULL;
string *pFirstName = NULL, *pMiddleName = NULL, *pLastName = NULL;
float *pSalary = NULL;


int id, age, confirm, dataToDelete, isDoneEdit = 1, saveChanges;
string firstName, middleName, lastName;
float salary;

pId = &id;
pAge = &age;
pConfirm = &confirm;
pFirstName = &firstName;
pMiddleName = &middleName;
pLastName = &lastName;
pSalary = &salary;
pDataToDelete = &dataToDelete;
pIsDoneEdit = &isDoneEdit;
pSaveChanges = &saveChanges;

displayData(persons, length);
printf("\n\nEnter the ID of the data you want to delete: ");
scanf("%d", pDataToDelete);

while(*pDataToDelete < 1 || *pDataToDelete > *length)
{
printf("\nData not found!\n");
displayData(persons, length);
printf("\n\nEnter the ID of the data you want to delete: ");
scanf("%d", pDataToDelete);
}

printf("%d", *pDataToDelete);
printf("%d", persons[*pDataToDelete].id);

for(int i = 0; i < *length; i++)
{
if(persons[i].id == *pDataToDelete)
{
printf("\n\nYour selected ID is: %d\n", *pDataToDelete);
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToDelete - 1].id, persons[*pDataToDelete - 1].firstName, persons[*pDataToDelete - 1].middleName, persons[*pDataToDelete - 1].lastName, persons[*pDataToDelete - 1].age, persons[*pDataToDelete - 1].salary);
break;
}
}

printf("\n\n(1)Yes (2)No\n\nAre you sure you want to delete this data?");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
strcpy(persons[*pDataToDelete - 1].firstName, "No Data Yet");
strcpy(persons[*pDataToDelete - 1].middleName, "No Data Yet");
strcpy(persons[*pDataToDelete - 1].lastName, "No Data Yet");
persons[*pDataToDelete - 1].age = 0;
persons[*pDataToDelete - 1].salary = 0;
printf("\nThe data has been deleted.");
displayData(persons, length);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on the Data.");
break;
default:
printf("Something went wrong.");
break;
}
}

void updateData(Person *persons, int *length)
{
int *pId = NULL, *pAge = NULL, *pConfirm = NULL, *pDataToEdit = NULL, *pColumnToEdit = NULL, *pIsDoneEdit, *pSaveChanges = NULL;
string *pFirstName = NULL, *pMiddleName = NULL, *pLastName = NULL;
float *pSalary = NULL;


int id, age, confirm, dataToEdit, columnToEdit, isDoneEdit = 1, saveChanges;
string firstName, middleName, lastName;
float salary;

pId = &id;
pAge = &age;
pConfirm = &confirm;
pFirstName = &firstName;
pMiddleName = &middleName;
pLastName = &lastName;
pSalary = &salary;
pDataToEdit = &dataToEdit;
pColumnToEdit = &columnToEdit;
pIsDoneEdit = &isDoneEdit;
pSaveChanges = &saveChanges;

displayData(persons, length);
printf("\n\nEnter the ID of the data you want to edit: ");
scanf("%d", pDataToEdit);

while(*pDataToEdit < 1 || *pDataToEdit > *length)
{
printf("\nData not found!\n");
displayData(persons, length);
printf("\n\nEnter the ID of the data you want to edit: ");
scanf("%d", pDataToEdit);
}


for(int i = 0; i < *length; i++)
{
if(persons[i].id == *pDataToEdit)
{
printf("\nYour selected ID is: %d\n", *pDataToEdit);
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
break;
}
}

printf("\n\n(1)First Name (2)Middle Name (3)Last Name (4)Age (5)Salary (6)All");
printf("\n\nEnter the column you want to edit: ");
scanf("%d", pColumnToEdit);

while(*pColumnToEdit < 1 || *pColumnToEdit > 6)
{
printf("\nInvalid choice!");
printf("\n\n(1)First Name (2)Middle Name (3)Last Name (4)Age (5)Salary (6)All");
printf("\n\nEnter the column you want to edit: ");
scanf("%d", pColumnToEdit);
}

switch(*pColumnToEdit)
{
case FirstName:
while(isDoneEdit != Done)
{
printf("\nCurrent First Name: %s", persons[*pDataToEdit - 1].firstName);
printf("\n\nEnter a new First Name: ");
scanf("%s", pFirstName);
printf("\n(1) Yes (2) Cancel\n\nSave changes?");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
strcpy(persons[*pDataToEdit - 1].firstName, *pFirstName);
printf("\nChanges on First Name have been saved.");
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on First Name.");
break;
default:
printf("Something went wrong.");
break;
}
}
break;
case MiddleName:
while(isDoneEdit != Done)
{
printf("\nCurrent Middle Name: %s", persons[*pDataToEdit - 1].middleName);
printf("\n\nEnter a new Middle Name: ");
scanf("%s", pMiddleName);
printf("\n(1) Yes (2) Cancel\n\nSave changes?");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
strcpy(persons[*pDataToEdit - 1].middleName, *pMiddleName);
printf("\nChanges on Middle Name have been saved.");
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on Middle Name.");
break;
default:
printf("Something went wrong.");
break;
}
}
break;
case LastName:
while(isDoneEdit != Done)
{
printf("\nCurrent Last Name: %s", persons[*pDataToEdit - 1].lastName);
printf("\n\nEnter a new Last Name: ");
scanf("%s", pLastName);
printf("\n(1) Yes (2) Cancel\n\nSave changes?");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
strcpy(persons[*pDataToEdit - 1].lastName, *pLastName);
printf("\nChanges on Last Name have been saved.");
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on Last Name.");
break;
default:
printf("Something went wrong.");
break;
}
}
break;
case Age:
while(isDoneEdit != Done)
{
printf("\nCurrent Age: %d", persons[*pDataToEdit - 1].age);
printf("\n\nEnter a new Age: ");
scanf("%d", pAge);
printf("\n(1) Yes (2) Cancel\n\nSave changes?");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
persons[*pDataToEdit - 1].age = *pAge;
printf("\nChanges on Age have been saved.");
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on Age.");
break;
default:
printf("Something went wrong.");
break;
}
}
break;
case Salary:
while(isDoneEdit != Done)
{
printf("\nCurrent Salary: %.2f", persons[*pDataToEdit - 1].salary);
printf("\n\nEnter a new Salary: ");
scanf("%f", pSalary);
printf("\n(1) Yes (2) Cancel\n\nSave changes? ");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
persons[*pDataToEdit - 1].salary = *pSalary;
printf("\nChanges on Salary have been saved.");
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on Salary.");
break;
default:
printf("Something went wrong.");
break;
}
}
break;
case All:
while(isDoneEdit != Done)
{
printf("\nCurrent First Name: %s", persons[*pDataToEdit - 1].firstName);
printf("\n\nEnter a new First Name: ");
scanf("%s", pFirstName);
printf("\nCurrent Middle Name: %s", persons[*pDataToEdit - 1].middleName);
printf("\n\nEnter a new Middle Name: ");
scanf("%s", pMiddleName);
printf("\nCurrent Last Name: %s", persons[*pDataToEdit - 1].lastName);
printf("\n\nEnter a new Last Name: ");
scanf("%s", pLastName);
printf("\nCurrent Age: %d", persons[*pDataToEdit - 1].age);
printf("\n\nEnter a new Age: ");
scanf("%d", pAge);
printf("\nCurrent Salary: %.2f", persons[*pDataToEdit - 1].salary);
printf("\n\nEnter a new Salary: ");
scanf("%f", pSalary);
printf("\n(1) Yes (2) Cancel\n\nSave changes? ");
scanf("%d", pSaveChanges);

switch (*pSaveChanges)
{
case Yes:
strcpy(persons[*pDataToEdit - 1].firstName, *pFirstName);
strcpy(persons[*pDataToEdit - 1].middleName, *pMiddleName);
strcpy(persons[*pDataToEdit - 1].lastName, *pLastName);
persons[*pDataToEdit - 1].age = *pAge;
persons[*pDataToEdit - 1].salary = *pSalary;
printf("\nChanges on Data have been saved.");
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[*pDataToEdit - 1].id, persons[*pDataToEdit - 1].firstName, persons[*pDataToEdit - 1].middleName, persons[*pDataToEdit - 1].lastName, persons[*pDataToEdit - 1].age, persons[*pDataToEdit - 1].salary);
isDoneEdit = Done;
break;
case No:
isDoneEdit = Done;
printf("No changes have been made on the Data.");
break;
default:
printf("Something went wrong.");
break;
}
}
break;
default:
printf("Something went wrong.");
break;
}

}

void insertData(Person *persons, int *length, int *idCounter)
{
int *pId = NULL, *pAge = NULL, *pConfirm = NULL, *pNumOfEntry = NULL;
string *pFirstName = NULL, *pMiddleName = NULL, *pLastName = NULL;
float *pSalary = NULL;

int id, age, confirm, numOfEntry;
string firstName, middleName, lastName;
float salary;

pId = &id;
pAge = &age;
pConfirm = &confirm;
pNumOfEntry = &numOfEntry;
pFirstName = &firstName;
pMiddleName = &middleName;
pLastName = &lastName;
pSalary = &salary;

printf("Enter number of data entry: ");
scanf("%d", pNumOfEntry);

for(int i = 0; i < *pNumOfEntry; i++)
{
printf("\nEnter your first name: ");
scanf("%s", pFirstName);

printf("\nEnter middle name: ");
scanf("%s", pMiddleName);

printf("\nEnter your last name: ");
scanf("%s", pLastName);

printf("\nEnter your age: ");
scanf("%d", pAge);

printf("\nEnter your salary: ");
scanf("%f", pSalary);

printf("\nID: %d", *idCounter);
printf("\nFirst Name: %s", *pFirstName);
printf("\nMIddle Name: %s", *pMiddleName);
printf("\nLast Name: %s", *pLastName);
printf("\nAge: %d", *pAge);
printf("\nSalary: %.2f", *pSalary);

printf("\nDo you want to save this data? \nSelect from (1) Yes and (2) No: ");
scanf("%d", pConfirm);

while(*pConfirm < 1 || *pConfirm > 2)
{
printf("\nInvalid choice. Choose from 1 and 2: ");
scanf("%d", pConfirm); 
}

switch(*pConfirm)
{
case Yes:
for(int i = 0; i < *length; i++)
{
if(strcmp(persons[i].firstName, "No data yet") == 0)
{
persons[i].id = *idCounter;
strcpy(persons[i].firstName, *pFirstName);
strcpy(persons[i].middleName, *pMiddleName);
strcpy(persons[i].lastName, *pLastName);
persons[i].age = *pAge;
persons[i].salary = *pSalary;
*idCounter += 1;
break;
}
}
printf("\nData has been saved successfully\n");
break;
case No:
printf("\nData has not been saved");
break;
default:
printf("Something went wrong.");
break;
}

}
displayData(persons, length);
}

void displayData(Person *persons, int *length)
{
printf("\nID\tFirst Name\tMiddle Name\tLast Name\tAge\tSalary\t");
for(int i = 0; i <= (*length - 1); i++)
{
printf("\n%1d %16s %16s %13s %9d %10.2f", persons[i].id, persons[i].firstName, persons[i].middleName, persons[i].lastName, persons[i].age, persons[i].salary);
}
}

void startProcess(int *userChoice, Person *persons, int *length, int *iterator, int *idCounter)
{
validateUserChoice(userChoice);
selectProcess(userChoice, persons, length, iterator, idCounter);
}

void selectProcess(int *userChoice, Person *persons, int *length, int *iterator, int *idCounter)
{

switch(*userChoice)
{
case Create:
insertData(persons, length, idCounter);
break;
case Read:
displayData(persons, length);
break;
case Update:
updateData(persons, length);
break;
case Delete:
deleteData(persons, length);
break;
case Exit:
*iterator = Break;
printf("Come Again");
break;
default:
printf("Invalid Choice");
break;
}
}

void validateUserChoice(int *userChoice)
{
while(*userChoice < 1 || *userChoice > 5)
{
printf("\nInvalid Choice.");
instruction();
scanf("%d", userChoice);
}

}

void instruction()
{
printf("\n\n1. Insert Data");
printf("\n2. Display Data");
printf("\n3. Update a Data");
printf("\n4. Delete a Data");
printf("\n5. Exit");
printf("\n\nSelect from the options (1) (2) (3) (4) (5):  ");
}

void initializeDb(Person *persons, int *length)
{
for(int i = 0; i < *length; i++)
{
persons[i].id = (i + 1);
strcpy(persons[i].firstName, "No data yet");
strcpy(persons[i].middleName, "No data yet");
strcpy(persons[i].lastName, "No data yet");
persons[i].age = 0;
persons[i].salary = 0;
}
}
