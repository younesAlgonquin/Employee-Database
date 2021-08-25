#ifndef assign2_h
#define assign2_h


/**************************************************************************
  Prompt for integer inputs and validate it
  returns a positive integer  
***************************************************************************/
int checkIntegerInput();

/**************************************************************************
   Display menu of actions
***************************************************************************/
void menu();

/**************************************************************************
   Prompt  for employee name
   returns the employee name
***************************************************************************/
char *getName();

/**************************************************************************
   Prompt  for employee gender and validate it
   returns the employee gender
***************************************************************************/
char *getGender();

/**************************************************************************
   Prompt  for employee job description
   returns the employee job description
***************************************************************************/
char *getProfile();

/**************************************************************************
   Prompt  for employee feature to be updated/deleted and validate it
   Returns a valid feature
***************************************************************************/
char *getFeature();

/**************************************************************************
  convert a string to uppercase
  feature: pointer to the string to be converted
  Returns a feature in uppercase
***************************************************************************/
char *toUpperCase(char *feature);

/**************************************************************************
  Prompt user to confirm update/deletion operation and validate it
  Returns users decision (Y/N)
***************************************************************************/
char *confirmChoice();

/**************************************************************************
  deletes an employee from the database
  index: the index of the entry tobe deleted in the database
  count: number of entries in the database 
***************************************************************************/
void deleteEntry(int emp_ID);

/**************************************************************************
  Asks user to chose an option from the main menu and validate the input
  Returns a valid menu option

***************************************************************************/
char getAction();

#endif /* assign2_h */