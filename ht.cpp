/* Started 1/31/2024 */
//HashTable code adapted from https://www.digitalocean.com/community/tutorials/hash-table-in-c-plus-plus#
//TO DO:
//make names string pointers. (check digitalocean for char values?)
#include <iostream>

using namespace std;

struct Student {
  string* firstName;
  string* lastName;
  int id;
  //int* id;
  float gpa;
};

struct LinkedList {
  Student* student;
  //struct LinkedList* next;
  LinkedList* next;
};

struct HashTable {
  Student** list;
  int size;
  int count;
  LinkedList** overflow_buckets;
};


Student* add(int id);
Student* addOne(int id, float gpa);
HashTable* makeHT(int size);
void printTable(HashTable* table);
//void ht_insert(HashTable* table, int* id);
void ht_insert(HashTable* table, int id, Student* student); 
void ht_delete(HashTable* table, int id);
string nameGenerator();
void handle_collision(HashTable* table, long unsigned int index, Student* student);
LinkedList* linkedList_insert(LinkedList* list, Student* student);

string input;
int intput;
float floatput; // these names are getting more creative by the day

int globalID = 1;//global variable, is the id number so that user can add more
int main() {

  cout << "Begin Process" << endl;
  cout << "Type the SIZE of the table:" << endl;
  cin >> intput;

  HashTable *table = makeHT(intput);
  cout << "Table created." << endl;

  while (input != "quit") {
    cout << "Please type 'add', 'delete', 'print', 'addRan', or 'quit' below:" << endl;
    cin >> input;
    if (input == "add") {
      /*string firstname;
	string* ptr1 firstname;
	string lastname;
	string* ptr2 lastname;
      */
      float gpa = 4.00;
      /*cout << "Student's first name:" << endl;
      cin >> firstname;
      cout << "Student's last name:" << endl;
      cin >> lastname;
      */      
      cout << "Student's GPA:" << endl;
      cin >> gpa;
      
      cout << "Making student..." << endl;
      ht_insert(table, globalID, addOne(globalID, gpa));
      cout << "Student made." << endl;
      globalID++;
      continue;
    }
    else if (input == "delete") {
      cout << "Type the ID of the student to delete:" << endl;
      cin >> intput;
      ht_delete(table, intput);
      continue;
    }
    else if (input == "print") {
      printTable(table);
      continue;
    }
    else if (input == "addRan") {
      cout << "How many students would you like to add?" << endl;
      cin >> intput;
      cout << "Generating " << intput << " students..." << endl;
      for (int i = 1; i < intput; i++) {
	Student* student = add(globalID);
	ht_insert(table, globalID, student);
	globalID++;
      }
      cout << "Students generated." << endl;
      continue;
    }
    else if (input == "quit") {
      return 0;
    }
    else {
      continue;
    }
    return 0;
  }


  cout << "thanks lol" << endl;
  return 0;
}
//adds random student
Student* add(int id) {//pass id by reference,
  Student* student = new Student();
  student->id = id;
  //student->firstName = "bob";
  //student->lastName = "joe";
  //student->firstName = nameGenerator();
  //student->lastName = nameGenerator();
  srand((unsigned) time(NULL));
  student->gpa = (rand() % 400)/100;
  return student;
}
Student* addOne(int id, float gpa) {
  Student* student;
  student->id = id;
  //student->firstName = firstname;
  //student->lastName = lastname;
  student->gpa = gpa;
  return student;
}
 void ht_insert(HashTable* table, int id, Student* student) {
   //void ht_insert(HashTable* table, int* id, string firstname, string lastname, float gpa) {
   //Student* student = addOne(id, firstname, lastname, gpa);

  int index = id % table->size;

  Student* current_student = table->list[index];

  if (current_student == NULL) {
    if (table->count == table-> size) {
      cout << "List is full" << endl;
      return;
    }

    table -> list[index] = student;
    table -> count++;
  }
  else {
    handle_collision(table, index, student);
    return;
  
    
  }
}


LinkedList** create_overflow_buckets(HashTable* table) {
  LinkedList** buckets = new LinkedList*[4];
  for (int i = 0; i < table->size; i++) {
    buckets[i] = NULL;
  }

  return buckets;

}

HashTable* makeHT(int size) {

  HashTable* table = new HashTable();
  table->size = size;
  table->count = 0;
  table->list = new Student*[size];

  for (int i = 0; i < table->size; i++) {
    table->list[i] = NULL;
  }

  table->overflow_buckets = create_overflow_buckets(table);
  return table;
}

void ht_delete(HashTable* table, int id) {
  // Deletes an item from the table.

  int index = id % table->size;
  Student* student = table->list[index];
  LinkedList* head = table->overflow_buckets[index];

  if (student == NULL) {
    return;
  }

  else {
    if (head == NULL && student->id == id) {
      //no chain, item exists
      table->list[index] = NULL;
      table->count--;
      return;
    }
    else if (head != NULL) {
      //chain exists
      if (student->id == id) {
	//delete this student
	LinkedList* node = head;
	head = head->next;
	node->next = NULL;
	table->list[index] = addOne(node->student->id, node->student->gpa);
	table->overflow_buckets[index] = head;
	return;
      }

      LinkedList* curr= head;
      LinkedList* prev = NULL;

      while (curr) {

	if (curr->student->id == id) {

	  if (prev == NULL) {
	    table->overflow_buckets[index] == NULL;
	    return;
	  }
	  else {
	    prev->next = curr-> next;
	    curr->next = NULL;
	    table->overflow_buckets[index] = head;
	    return;
	  }
	}

	curr = curr->next;
	prev = curr;
      }
    }
  }
}

void printTable(HashTable* table) {
  cout << "Student List:" << endl;
  for (int i = 0; i < table->size; i++) {//prints first ones
    if (table->list[i] != NULL) {
      cout << table->list[i]->id << " GPA: " << table->list[i]->gpa << endl;
    }

  }
  for (int i = 0; i < 4; i++) {
    if (table->overflow_buckets[i] != NULL) {
      cout << table->overflow_buckets[i]->student->id << " GPA: " << table->overflow_buckets[i]->student->gpa << endl;
    }
}
  cout << endl << endl;
  cout << "End of List." << endl;
}

void handle_collision(HashTable* table, unsigned long index, Student* student) {

  LinkedList* head = table->overflow_buckets[index];
  
  if (head == NULL) {
    table->overflow_buckets[index] = new LinkedList();
    LinkedList* head = table->overflow_buckets[index];
    table->overflow_buckets[index]->next = NULL;
    table->overflow_buckets[index]->student = student;
    table->overflow_buckets[index] = head;
    return;
  }
  else {
   
    //table->overflow_buckets[index]->next = NULL;
   

    table->overflow_buckets[index] = linkedList_insert(table->overflow_buckets[index], student);
    return;
  }
}

LinkedList* linkedList_insert(LinkedList* list, Student* student) {

  if (list == NULL) {
    LinkedList* head;
    head -> student = student;
    head -> next = NULL;
    list = head;
    return list;
  }
  //else if (list->next == NULL) {
  else {
    LinkedList* node = new LinkedList();
    node->student = student;
    node->next = NULL;
    list->next = node;
    return list;
  }

  LinkedList* temp = list;

  while (temp->next->next) {
    temp = temp -> next;
  }

  LinkedList* node;
  node -> student = student;
  node -> next = NULL;
  temp -> next = node;
  return list;
}

/*
string nameGenerator() {
  srand((unsigned) time(NULL));
  int i = 1+ (rand() % 20);
  if (i == 1) {
    return "Olivia";
  }
  else if (i == 2) {
    return "Noah";
  }
  else if (i == 3) {
    return "Emma";
  }
  else if (i == 4) {
    return "Ameilia";
  }
  else if (i == 5) {
    return "Liam";
  }
  else if (i == 6) {
    return "Oliver";
  }
  else if (i == 7) {
    return "Sophia";
  }
  else if (i == 8) {
    return "Elija";
  }
  else if (i == 9) {
    return "Charlotte";
  }
  else if (i == 10) {
    return "Mateo";
  }
  else if (i == 11) {
    return "Ava";
  }
  else if (i == 12) {
    return "Lucas";
  }
  else if (i == 13) {
    return "Isabella";
  }
  else if (i == 14) {
    return "Levi";
  }
  else if (i == 15) {
    return "Mia";
  }
  else if (i == 16) {
    return "Leo";
  }
  else if (i == 17) {
    return "Luna";
  }
  else if (i == 18) {
    return "Ezra";
  }
  else if (i == 19) {
    return "Luca";
  }
  else if (i == 20) {
    return "Evelyn";
  }
  return "NULL";
}
*/
