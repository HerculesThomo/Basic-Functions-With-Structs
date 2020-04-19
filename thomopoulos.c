#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
* Δημιουργώ μια δομή φοιτητή ο οποίος περιέχει τα εξής χαρακτηρηστικά:
* Αριθμό μητρώου - Όνομα - Επώνυμο - Διεύθυνση - Τηλέφωνο
* Όλα τα χαρακτηρηστικά είναι τύπου χαρακτήρα διότι ο αριθμός μητρώου
* μπορεί να περιέχει χαρακτήρες & το τηλ΄έφωνο μπορεί να περιέχει τον
* κωδικό +30 γι αυτό το λόγο έχω κάνει το μήκος που μπορεί να δεχτεί το
* τηλέφωνο να είναι 14 χαρακτήρες
*/
struct foitiths {
  char am[8];
  char name[20];
  char surname[20];
  char address[20];
  char phone[14];
  struct foitiths *next;
}*head;

/**
* Στο σημείο αυτό καλώ όλες τις συναρτήσεις που έχω υλοποιήσει
* για το προγραμμά μου παρακάτω. Αυτό το κάνω επειδή οι συναρτήσεις
* έχουν υλοποιηθεί κάτω απο την main και αν δεν τις ορίσω εδώ δεν
* θα μπορεί να τις αναγνωρίσει το πρόγραμμα
*/
void menu(); //H main καλεί την menu και ξεκινάει το πρόγραμμα
void saveFile();// Αποθήκευση σε αρχείο
void clearCMD();// Καθαρισμός οθόνης
void readFile();// Διάβασμα από αρχείο
void menu_options();// Εμ΄φανιση επιλογών menu
void displayAllStudents();// Εμφάνιση όλων των φοιτητών
void displayEditOptions();// Εμφάνιση menu όταν ο χρήστης επιλέξει να τροποποιήσει κάποιον φοιτητή
void deleteStudent(char arithmosMitrwou[]);// Διαγραφή φοιτητή με βάση τον αριθμό μητρώου
void searchAStudent(char arithmosMitrwou[]);// Εμφάνιση φοιτητή με βάση τον αριθμό μητρώου
void countWrongUsersInput(int counter, int attempts);// Σε 3 λάθος επιλογές του menu το πρόγραμμα τερματίζει
void insertValuesAndClearStream(char text[], char variable[], int lenght);// Δέχεται την ε΄ίσοδο του χρήστη και καθαρίζει το buffer
void addStudent(char am[], char name[], char surname[], char address[], char phone[]);// Προσθέτει έναν φοιτητή
void editStudent(char arithmosMitrwou[], char am[], char name[], char surname[], char address[], char phone[]);// Τροποποιεί τα στοιχεία ενός φοιτητή

/**
* Από την main ξεκινάει το προγραμμά μου όπου καλεί την μέθοδο menu
*/
int main() {
  readFile();
  menu();
  return 0;
}

/**
* Η μέθοδος αυτή εμφανίζει το κυρίως menu του προγράμματος
*/
void menu_options() {
  printf("//////////////////////////////////\n");
  printf("//////////////////////////////////\n");
  printf("/////////// Menu /////////////////\n");
  printf("///////// 1. Add student /////////\n");
  printf("///////// 2. Display students ////\n");
  printf("///////// 3. Delete student //////\n");
  printf("///////// 4. Search student //////\n");
  printf("///////// 5. Edit student ////////\n");
  printf("///////// 6. Clear screen ////////\n");
  printf("///////// 7. Exit ////////////////\n");
  printf("//////////////////////////////////\n");
  printf("//////////////////////////////////\n");
}

/**
* Η μέθοδος αυτή εμφανίζει τις επιλογές που έχει ο χρήστης για να
* αλλάξει τα στοιχεία εν΄ος φοιτητή
*/
void displayEditOptions() {
  printf("//////////////////////////////////////\n");
  printf("//////////////////////////////////////\n");
  printf("////// Change student's data /////////\n");
  printf("///////// 1. Change AM ///////////////\n");
  printf("///////// 2. Change Name /////////////\n");
  printf("///////// 3. Change Surname //////////\n");
  printf("///////// 4. Change Address //////////\n");
  printf("////////// 5. Change Phone ///////////\n");
  printf("//////////////////////////////////////\n");
  printf("//////////////////////////////////////\n");
}

/**
* Η μέθοδος παίρνει 3 ορίσματα
* @text Είναι το μήνυμα που θέλουμε να εμφανιστεί στον χρήστη
* @variable Είναι η μεταβλητή που θα πάρει την τιμή που θα δώσει ο χρήστης
* @lenght Είναι το μέγιστο επιτρεπτό όριο.
* Εαν η είσοδος του χρήστη είναι μεγαλύτερη απο το επιτρεπόμενο όριο κόβει την
* είσοδο στο μεγιστο και καθαρίζει το buffer
*/
void insertValuesAndClearStream(char text[], char variable[], int lenght) {
  int i = 0;
  printf("%s\n", text);
  // fgets(variable, lenght, stdin);//Η συνάρτηση αυτή δέχεται συγκεκριμένο μέγεθος εισόδου ο΄πότε μπορώ να βάλω ένα όριο στην είσοδο του χρήστη + δεν κόβει το string όταν ο χρήστης πατήσει το space. Την έχω σχολιάσει επειδή μετά την είσοδο του χρήστη προσθέτει ένα "\n" και έχω θέμα μόλις διαβάσω δεδομένα από αρχείο κσι πατήσω αποθήκευση σε αρχείο
  scanf("%s", variable);// Η scanf δεν διαβάζει το string μετά το πάτημα του space - αλλά δεν αντιμετωπίζω προβλήματα μετά την αποθήκευση και διάβασμα του αρχείου.
  if(!strchr(variable, '\n')) {
      while(getchar() != '\n');
  }
}

/**
* Μετράει τις λάθος εισόδους που θα δώσει ο χρήστης
* Εάν ο χρήστης δώσει πάνω απο 3 λάθος εισόδους το
* πρόγραμμα τερματίζει
*/
void countWrongUsersInput(int counter, int attempts) {
  attempts = 3 - counter;
  printf("Wrong choice \n");
  printf("Enter a valid choice\n");
  printf("Attempts left %d: \n", attempts);
  if(attempts == 0) {
    printf("Terminating the program\n");
    exit(1);
  }
}

/**
* Καθαρίζει την κονσόλα απο τις επιλογές του χρήστη
* Η μέθοδος αυτή δουλεύει μόνο για λειτουργικό windows
*/
void clearCMD() {
  system("cls");
}

/**
* Δημιουργεί έναν φοιτητή
* Παίρνει 5 ορίσματα όλα πίνακες χαρακτήρων
* @am Είναι ο αριθμός μητρώου του φοιτητή **Το έχω υπό μορφή πίνακα χαρακτήρων διότι ένας αριθμός μητρώου μπορεί να περιέχει και γράμματα
* @name Το όνομα ενός φοιτητή
* @surname Το επίθετο ενός φοιτητή
* @address Η διεύθυνση ενός φοιτητή
* @phone Το τηλέφωνο ενός φοιτητή **Έχει τη μορφή πίνακα χαρακτήρων διότι μπορεί να έχει αποθηκευτεί με κάποιο κωδικό π.χ +30
*/
void addStudent(char am[], char name[], char surname[], char address[], char phone[]) {
  struct foitiths *temp;
  temp = (struct foitiths *)malloc(1*sizeof(struct foitiths));
  strcpy(temp -> am, am);
  strcpy(temp -> name, name);
  strcpy(temp -> surname, surname);
  strcpy(temp -> address, address);
  strcpy(temp -> phone, phone);

  if(head == NULL) {
    head = temp;
    head -> next = NULL;
  } else {
    temp -> next = head;
    head = temp;
  }
}

/**
* Εμφανίζει όλους τους φοιτητές
*/
void displayAllStudents() {
  struct foitiths *iterator;
  iterator = head;
  if(iterator == NULL) {
    printf("No student has been recorded yet\n");
    return;
  }
  printf("******************************************************************************\n");
  while(iterator != NULL) {
    printf("Student with AM: \n%s, First Name: \n%s, Last name: \n%s, Address: \n%s, Phone Number: \n%s\n",
        iterator -> am, iterator -> name, iterator -> surname, iterator -> address, iterator -> phone);
    iterator = iterator -> next;
    printf("******************************************************************************\n");
  }
  printf("******************************************************************************\n");
}

/**
* Εμφανίζει έναν συγκεκριμένο φοιτητή με βάση τον αριθμό μητρώου
* Εάν ο φοιτητής αυτός δεν έχει ακόμα αποθηκευτεί το πρόγραμμα
* μας εμφανίζει το αντίστοιχο μήνυμα σφάλματος
*/
void searchAStudent(char arithmosMitrwou[]) {
  bool onomaFound = false;
  struct foitiths *search;
  search = head;
  if(search == NULL) {
    printf("The student has not been written\n");
    return;
  }
  insertValuesAndClearStream("Give the name of the student you wanna search: ", arithmosMitrwou, 8);
  while(search != NULL) {
    if(strcmp(search -> am, arithmosMitrwou) == 0) {
      printf("Student with AM: %s, First Name: %s, Last Name: %s, Address: %s, Phone number: %s\n",
          search -> am, search -> name, search -> surname, search-> address, search -> phone);
          onomaFound = true;
          break;
    }
    search = search -> next;
    }
  if(onomaFound == false) {
    printf("O Foititis me to sigkekrimeno AM den yparxei !\n");
  }
}
 /**
 * Διαγραφή ενός φοιτητή
 * Εάν ο φοιτητής δεν υπάρχει το πρόγραμμα μας εμφανίζει το αντίστοιχο μήνυμα σφάλματος
 */
void deleteStudent(char arithmosMitrwou[]) {
  bool studentFound = false;
  struct foitiths *deletion;
  struct foitiths *previous;
  deletion = head;
  previous = NULL;
  if(deletion == NULL) {
    printf("No student has been recorded yet\n");
    return;
  }
  insertValuesAndClearStream("Give the AM of the student you want to delete: ", arithmosMitrwou, 8);
  while(deletion != NULL) {
    if(strcmp(deletion -> am, arithmosMitrwou) == 0) {
          if(previous == NULL) {
            deletion = head;
            head = head -> next;
            free(deletion);
            studentFound = true;
            break;
          } else {
            previous -> next = deletion -> next;
            free(deletion);
            deletion = previous -> next;
            studentFound = true;
            break;
          }
    } else {
      previous = deletion;
      deletion = deletion -> next;
    }
  }
  if(studentFound == false) {
    printf("The student doesn't exist!\n");
  } else {
    printf("The student has been found and successfully deleted!\n");
  }
}

/**
* Τροποποιεί τα στοιχεία ενός φοιτητή
* Δέχεται 6 ορίσματα όλα τύπου πίνακα χαρακτήρων
* @arithmosMitrwou = @am
* @name Το ΄όνομα του φοιτητή
* @surname Το επώνυμο του φοιτητή
* @address Η διεύθυνση του φοιτητή
* @phone Το τηλέφωνο του φοιτητή
*/
void editStudent(char arithmosMitrwou[], char am[], char name[], char surname[], char address[], char phone[]) {
  bool studentFound = false;
  int attempts, counter = 0;
  char usersOption;
  struct foitiths *edit;
  edit = head;
  if(edit == NULL) {
    printf("No student to edit!\n");
    return;
  }
  insertValuesAndClearStream("Give the am of the student you want to edit: ", arithmosMitrwou, 8);
  while(edit != NULL) {
    if(strcmp(edit -> am, arithmosMitrwou) == 0) {
      studentFound = true;
      displayEditOptions();
      insertValuesAndClearStream("Give your choice: ", &usersOption, 2);
      switch (usersOption) {
        case '1':
          insertValuesAndClearStream("Enter AM: ", am, 8);
          strcpy(edit -> am, am);
          break;
        case '2':
          insertValuesAndClearStream("Enter First Name: ", name, 20);
          strcpy(edit -> name, name);
          break;
        case '3':
          insertValuesAndClearStream("Enter Last Name: ", surname, 20);
          strcpy(edit -> surname, surname);
          break;
        case '4':
          insertValuesAndClearStream("Enter Address: ", address, 20);
          strcpy(edit -> address, address);
          break;
        case '5':
          insertValuesAndClearStream("Enter Phone Number: ", phone, 14);
          strcpy(edit -> phone, phone);
          break;
        default:
            // counter ++;
            // countWrongUsersInput(counter, attempts);
          printf("Wrong choice!\n");
      }
    }
    edit = edit -> next;
  }
  if(studentFound == false) {
    printf("The student with AM: %d has not been found\n", arithmosMitrwou);
  }
}

/**
* Το menu καλείται στην main και χρησημοποιεί όλες τις παραπάνω συναρτήσεις
*
*/
void menu() {
  int attempts, counter = 0;
  char name[20], surname[20], address[20], am[8], phone[14], usersOption, onoma[20], arithmosMitrwou[8];
  while(1) {
  menu_options();
  insertValuesAndClearStream("Give your choice: ", &usersOption, 3);
  switch (usersOption) {
    case '1':
      insertValuesAndClearStream("Enter AM: ", am, 8);
      insertValuesAndClearStream("Enter name: ", name, 20);
      insertValuesAndClearStream("Enter surname: ", surname, 20);
      insertValuesAndClearStream("Enter address: ", address, 20);
      insertValuesAndClearStream("Enter phone: ", phone, 11);
      addStudent(am, name, surname, address, phone);
      break;
    case '2':
      displayAllStudents();
      break;
    case '3':
      deleteStudent(arithmosMitrwou);
      break;
    case '4':
      searchAStudent(onoma);
      break;
    case '5':
      editStudent(arithmosMitrwou, am, name, surname, address, phone);
      break;
    case '6':
      clearCMD();
      break;
    case '7':
      saveFile();
      exit(1);
      break;
    default:
      counter ++;
      countWrongUsersInput(counter, attempts);
        }
      }
    }

/**
* Αποθηκεύει τα δεδομένα του προγράμματος σε ένα αρχείο .txt
*/
void saveFile() {
      FILE *outfile;
      bool streamIsClear = true;
      struct foitiths *write;
      outfile = fopen("C:\\foititis.txt", "w");
      write = head;
      if(outfile == NULL) {
        printf("ERROR!");
        exit(1);
      }
      if(write == NULL) {
        printf("Nothing to write!\n");
      }
      while(write != NULL) {
        streamIsClear = false;
        fprintf(outfile,"\n%s\n%s\n%s\n%s\n%s\n",write->am, write->name, write->surname, write->address, write->phone);
        write = write -> next;
      }
      if(streamIsClear == false) {
        printf("The file has been saved\n");
     }
      fclose(outfile);
    }

/**
* Διαβάζει τα δεδομένα από ένα αρχείο .txt και τα μεταφέρει
* στο πρόγραμμα χρησημοποιώντας την συνάρτηση addStudent
*/
void readFile() {
  int i;
    char am[8], name[20], surname[20], address[20], phone[14];
    FILE *infile;
    infile = (fopen("C:\\foititis.txt", "r"));
    if(infile == NULL) {
      printf("File has not been created yet no recorded student\n");
    }
    char line[5];
    while(fgets(line, 5, infile)) {
      strtok(line, "\n");
      for(i = 0; i < strlen(line); i++) {
        if(line[i] == ' ') {
          line[i] = '\n';
          break;
        }
      }
      fgets(am, 8, infile);
      strtok(am, "\n");// Mε την strtok διβάζω την είσοδο του χρήστη μέχρι το '\n'  και το εισάγω σε κάθε έναν πίνακα. Ουσιαστικά αυτή σπάει το string σε tokens με βάση το delimiter που εισάγουμε και με μια for loop εισάγουμε τα δεδομένα μέσα σε έναν πόνακα
      for(i = 0; i < strlen(am); i++) {
        if(am[i] == ' ') {
          am[i] = '\n';
          break;
        }
      }
      fgets(name, 20, infile);
      strtok(name, "\n");
      for(i = 0; i < strlen(name); i++) {
        if(name[i] == ' ') {
          name[i] = '\n';
          break;
        }
      }
      fgets(surname, 20, infile);
      strtok(surname, "\n");
      for(i = 0; i < strlen(surname); i++) {
        if(surname[i] == ' ') {
          surname[i] = '\n';
          break;
        }
      }
      fgets(address, 20, infile);
      strtok(address, "\n");
      for(i = 0; i < strlen(address); i++) {
        if(address[i] == ' ') {
          address[i] = '\n';
          break;
        }
      }
      fgets(phone, 20, infile);
      strtok(phone, "\n");
      for(i = 0; i < strlen(phone); i++) {
        if(phone[i] == ' ') {
          phone[i] = '\n';
          break;
        }
      }

      addStudent(am, name, surname, address, phone);
    }
    fclose(infile);
}
