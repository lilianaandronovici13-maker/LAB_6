#ifndef STUDENT_ADT_H
#define STUDENT_ADT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[50];
    char surname[50];
    Date dob;
    char gender;        // 'm' sau 'f'
    char address[100];
    char specialty[20]; // IS, SI, IT, ACS etc.
    int group_no;
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
    struct Node* prev;
} Node;

// Stack (LIFO)
typedef struct {
    Node* top;
} Stack;

// Queue (FIFO) - baza pentru Simple, Deque, Circular, Priority
typedef struct {
    Node* front;
    Node* rear;
} Queue;

// ========== FUNCȚII UTILITARE ==========
void clearInput(void);
Date getCurrentDate(void);
void calculateAge(const Date* dob, int* years, int* months, int* days);
void printStudent(const Student* s);
Student createStudent(void);
int compareStudentsByAge(const Student* a, const Student* b);

// ========== STACK ==========
void initStack(Stack* s);
void pushStack(Stack* s, Student data);
Student popStack(Stack* s);
void displayStack(Stack* s);
int searchStackByReg(Stack* s, const char* name, const char* surname);
int searchStackByPosition(Stack* s, int pos, Student* out);
void deleteStackByPosition(Stack* s, int pos);

// ========== SIMPLE QUEUE ==========
void initQueue(Queue* q);
void enqueueSimple(Queue* q, Student data);
Student dequeueSimple(Queue* q);
void displayQueue(Queue* q);
int searchQueueByReg(Queue* q, const char* name, const char* surname);
void deleteQueueByPosition(Queue* q, int pos);

// ========== DOUBLE-ENDED QUEUE (DEQUE) ==========
void insertFrontDeque(Queue* q, Student data);
void insertRearDeque(Queue* q, Student data);
Student deleteFrontDeque(Queue* q);
Student deleteRearDeque(Queue* q);
void displayDeque(Queue* q);

// ========== CIRCULAR QUEUE ==========
void enqueueCircular(Queue* q, Student data);
Student dequeueCircular(Queue* q);
void displayCircular(Queue* q);

// ========== PRIORITY QUEUE (după vârstă) ==========
void enqueuePriority(Queue* q, Student data, int ascending); // 1=cei mai tineri primii
Student dequeuePriority(Queue* q);
void displayPriority(Queue* q);

// ========== SALVARE FIȘIER (text + binar) ==========
void saveToFileTxt(Node* head, const char* path);
void saveToFileBin(Node* head, const char* path);
void saveStackToFile(Stack* s);
void saveQueueToFile(Queue* q, const char* structName);

// ========== FUNCȚIILE CERUTE ÎN LAB 5 ==========
int createExperimentFile(const char* filename);  // Funcția 1: creează experiment.txt cu date studenți
void displayFileContent(const char* filename);   // Funcția 3: afișează conținut fișier
void calculateAgeAndSort(const char* inputFile, const char* outputFile); // Funcția 1: calculează vârsta și sortează
void prependFile(const char* destFile, const char* srcFile); // Funcția 2: copiază output.txt la începutul experiment.txt

#endif
