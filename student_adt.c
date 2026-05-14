#include "student_adt.h"


void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

Date getCurrentDate() {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    Date d;
    d.day = tm->tm_mday;
    d.month = tm->tm_mon + 1;
    d.year = tm->tm_year + 1900;
    return d;
}

void calculateAge(const Date* dob, int* years, int* months, int* days) {
    Date today = getCurrentDate();
    *years = today.year - dob->year;
    *months = today.month - dob->month;
    *days = today.day - dob->day;

    if (*days < 0) {
        int prev_month = (today.month == 1) ? 12 : today.month - 1;
        int prev_year = (today.month == 1) ? today.year - 1 : today.year;
        int days_in_month[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
        if ((prev_year % 4 == 0 && prev_year % 100 != 0) || prev_year % 400 == 0)
            days_in_month[2] = 29;
        *days += days_in_month[prev_month];
        (*months)--;
    }
    if (*months < 0) {
        *months += 12;
        (*years)--;
    }
}

void printStudent(const Student* s) {
    int y, m, d;
    calculateAge(&s->dob, &y, &m, &d);
    printf("%s %s | DOB: %02d/%02d/%04d | Varsta: %d ani | Gen: %c | Grupa: %d | Specializare: %s | Adresa: %s\n",
           s->name, s->surname, s->dob.day, s->dob.month, s->dob.year, y, s->gender, s->group_no, s->specialty, s->address);
}

Student createStudent() {
    Student s;
    printf("Nume: "); scanf("%49s", s.name);
    printf("Prenume: "); scanf("%49s", s.surname);
    printf("Data nasterii (zi luna an): "); scanf("%d %d %d", &s.dob.day, &s.dob.month, &s.dob.year);
    printf("Gen (m/f): "); scanf(" %c", &s.gender);
    clearInput();
    printf("Adresa: "); fgets(s.address, 100, stdin); s.address[strcspn(s.address, "\n")] = 0;
    printf("Specializare (IS/SI/IT/ACS): "); fgets(s.specialty, 20, stdin); s.specialty[strcspn(s.specialty, "\n")] = 0;
    printf("Grupa: "); scanf("%d", &s.group_no);
    return s;
}

int compareStudentsByAge(const Student* a, const Student* b) {
    int ay, am, ad, by, bm, bd;
    calculateAge(&a->dob, &ay, &am, &ad);
    calculateAge(&b->dob, &by, &bm, &bd);
    int ageA = ay * 365 + am * 30 + ad;
    int ageB = by * 365 + bm * 30 + bd;
    return ageA - ageB;
}

// ========== STACK ==========
void initStack(Stack* s) { s->top = NULL; }

void pushStack(Stack* s, Student data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = s->top;
    if (s->top) s->top->prev = newNode;
    s->top = newNode;
    printf("✔ Student adaugat in STACK.\n");
}

Student popStack(Stack* s) {
    Student empty = {""};
    if (!s->top) { printf("Stack gol!\n"); return empty; }
    Node* temp = s->top;
    Student data = temp->data;
    s->top = s->top->next;
    if (s->top) s->top->prev = NULL;
    free(temp);
    printf("✔ Student scos din STACK.\n");
    return data;
}

void displayStack(Stack* s) {
    if (!s->top) { printf("Stack gol.\n"); return; }
    printf("\n=== STACK (sus -> jos) ===\n");
    for (Node* cur = s->top; cur; cur = cur->next)
        printStudent(&cur->data);
}

int searchStackByReg(Stack* s, const char* name, const char* surname) {
    int pos = 1;
    for (Node* cur = s->top; cur; cur = cur->next, pos++)
        if (strcmp(cur->data.name, name) == 0 && strcmp(cur->data.surname, surname) == 0)
            return pos;
    return -1;
}

int searchStackByPosition(Stack* s, int pos, Student* out) {
    int idx = 1;
    for (Node* cur = s->top; cur; cur = cur->next, idx++)
        if (idx == pos) { *out = cur->data; return 1; }
    return 0;
}

void deleteStackByPosition(Stack* s, int pos) {
    if (!s->top) { printf("Stack gol.\n"); return; }
    if (pos == 1) { popStack(s); return; }
    int idx = 1;
    Node* cur = s->top;
    while (cur && idx < pos) { cur = cur->next; idx++; }
    if (!cur) { printf("Pozitie invalida.\n"); return; }
    if (cur->prev) cur->prev->next = cur->next;
    if (cur->next) cur->next->prev = cur->prev;
    free(cur);
    printf("✔ Student sters din STACK.\n");
}

// ========== SIMPLE QUEUE ==========
void initQueue(Queue* q) { q->front = q->rear = NULL; }

void enqueueSimple(Queue* q, Student data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = q->rear;
    if (!q->rear) q->front = q->rear = newNode;
    else { q->rear->next = newNode; q->rear = newNode; }
    printf("✔ Student adaugat in SIMPLE QUEUE.\n");
}

Student dequeueSimple(Queue* q) {
    Student empty = {""};
    if (!q->front) { printf("Coada goala!\n"); return empty; }
    Node* temp = q->front;
    Student data = temp->data;
    q->front = q->front->next;
    if (q->front) q->front->prev = NULL;
    else q->rear = NULL;
    free(temp);
    return data;
}

void displayQueue(Queue* q) {
    if (!q->front) { printf("Coada goala.\n"); return; }
    printf("\n=== SIMPLE QUEUE (fata -> spate) ===\n");
    for (Node* cur = q->front; cur; cur = cur->next)
        printStudent(&cur->data);
}

int searchQueueByReg(Queue* q, const char* name, const char* surname) {
    int pos = 1;
    for (Node* cur = q->front; cur; cur = cur->next, pos++)
        if (strcmp(cur->data.name, name) == 0 && strcmp(cur->data.surname, surname) == 0)
            return pos;
    return -1;
}

void deleteQueueByPosition(Queue* q, int pos) {
    if (!q->front) { printf("Coada goala.\n"); return; }
    if (pos == 1) { dequeueSimple(q); return; }
    int idx = 1;
    Node* cur = q->front;
    while (cur && idx < pos) { cur = cur->next; idx++; }
    if (!cur) { printf("Pozitie invalida.\n"); return; }
    if (cur->prev) cur->prev->next = cur->next;
    if (cur->next) cur->next->prev = cur->prev;
    if (cur == q->rear) q->rear = cur->prev;
    free(cur);
    printf("✔ Student sters din COADA.\n");
}

// ========== DEQUE ==========
void insertFrontDeque(Queue* q, Student data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = q->front;
    if (!q->front) q->front = q->rear = newNode;
    else { q->front->prev = newNode; q->front = newNode; }
    printf("✔ Student inserat in fata DEQUE.\n");
}

void insertRearDeque(Queue* q, Student data) { enqueueSimple(q, data); }
Student deleteFrontDeque(Queue* q) { return dequeueSimple(q); }

Student deleteRearDeque(Queue* q) {
    Student empty = {""};
    if (!q->rear) { printf("Deque gol!\n"); return empty; }
    Node* temp = q->rear;
    Student data = temp->data;
    q->rear = q->rear->prev;
    if (q->rear) q->rear->next = NULL;
    else q->front = NULL;
    free(temp);
    return data;
}

void displayDeque(Queue* q) { displayQueue(q); }

// ========== CIRCULAR QUEUE ==========
void enqueueCircular(Queue* q, Student data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    if (!q->front) {
        q->front = q->rear = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->next = q->front;
        newNode->prev = q->rear;
        q->rear->next = newNode;
        q->front->prev = newNode;
        q->rear = newNode;
    }
    printf("✔ Student adaugat in CIRCULAR QUEUE.\n");
}

Student dequeueCircular(Queue* q) {
    Student empty = {""};
    if (!q->front) { printf("Coada circulara goala!\n"); return empty; }
    Node* temp = q->front;
    Student data = temp->data;
    if (q->front == q->rear) q->front = q->rear = NULL;
    else {
        q->front = q->front->next;
        q->front->prev = q->rear;
        q->rear->next = q->front;
    }
    free(temp);
    return data;
}

void displayCircular(Queue* q) {
    if (!q->front) { printf("Coada circulara goala.\n"); return; }
    printf("\n=== CIRCULAR QUEUE ===\n");
    Node* cur = q->front;
    do { printStudent(&cur->data); cur = cur->next; } while (cur != q->front);
}

// ========== PRIORITY QUEUE (dupa varsta) ==========
void enqueuePriority(Queue* q, Student data, int ascending) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    if (!q->front) { q->front = q->rear = newNode; return; }

    int (*better)(const Student*, const Student*) = NULL;
    if (ascending) better = (int(*)(const Student*, const Student*))([](const Student* a, const Student* b) { return compareStudentsByAge(a, b) < 0; });
    else better = (int(*)(const Student*, const Student*))([](const Student* a, const Student* b) { return compareStudentsByAge(a, b) > 0; });

    if (better(&data, &q->front->data)) {
        newNode->next = q->front;
        q->front->prev = newNode;
        q->front = newNode;
        return;
    }
    Node* cur = q->front;
    while (cur->next && !better(&data, &cur->next->data)) cur = cur->next;
    newNode->next = cur->next;
    if (cur->next) cur->next->prev = newNode;
    else q->rear = newNode;
    cur->next = newNode;
    newNode->prev = cur;
}

Student dequeuePriority(Queue* q) { return dequeueSimple(q); }
void displayPriority(Queue* q) { displayQueue(q); }

// ========== SALVARE FISIER ==========
void saveToFileTxt(Node* head, const char* path) {
    FILE* f = fopen(path, "w");
    if (!f) { printf("Eroare creare fisier text!\n"); return; }
    for (Node* cur = head; cur; cur = cur->next)
        fprintf(f, "%s|%s|%d|%d|%d|%c|%s|%s|%d\n",
                cur->data.name, cur->data.surname,
                cur->data.dob.day, cur->data.dob.month, cur->data.dob.year,
                cur->data.gender, cur->data.address, cur->data.specialty, cur->data.group_no);
    fclose(f);
    printf("✔ Salvat TEXT: %s\n", path);
}

void saveToFileBin(Node* head, const char* path) {
    FILE* f = fopen(path, "wb");
    if (!f) { printf("Eroare creare fisier binar!\n"); return; }
    for (Node* cur = head; cur; cur = cur->next)
        fwrite(&cur->data, sizeof(Student), 1, f);
    fclose(f);
    printf("✔ Salvat BINAR: %s\n", path);
}

void saveStackToFile(Stack* s) {
    if (!s->top) { printf("Stack gol.\n"); return; }
    char path[256]; int mode;
    printf("Cale fisier: "); clearInput(); fgets(path, 256, stdin); path[strcspn(path, "\n")] = 0;
    printf("1. Text\n2. Binar\nAlegere: "); scanf("%d", &mode);
    if (mode == 1) saveToFileTxt(s->top, path);
    else saveToFileBin(s->top, path);
}

void saveQueueToFile(Queue* q, const char* structName) {
    if (!q->front) { printf("%s goala.\n", structName); return; }
    char path[256]; int mode;
    printf("Cale fisier: "); clearInput(); fgets(path, 256, stdin); path[strcspn(path, "\n")] = 0;
    printf("1. Text\n2. Binar\nAlegere: "); scanf("%d", &mode);
    if (mode == 1) saveToFileTxt(q->front, path);
    else saveToFileBin(q->front, path);
}

// ========== FUNCȚIILE CERUTE ÎN LAB 5 ==========
int createExperimentFile(const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) { printf("Eroare creare fisier!\n"); return 0; }
    int n;
    printf("Cati studenti doriti sa introduceti? ");
    scanf("%d", &n);
    fprintf(f, "%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("\n--- Student %d ---\n", i + 1);
        Student s = createStudent();
        fprintf(f, "%s\n%s\n%d %d %d\n%c\n%s\n%s\n%d\n",
                s.name, s.surname, s.dob.day, s.dob.month, s.dob.year,
                s.gender, s.address, s.specialty, s.group_no);
    }
    fclose(f);
    printf("\n✔ Fisierul %s a fost creat cu %d studenti.\n", filename, n);
    return n;
}

void displayFileContent(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) { printf("Eroare deschidere fisier %s!\n", filename); return; }
    printf("\n=== CONTINUTUL FISIERULUI %s ===\n", filename);
    char line[512];
    int line_no = 1;
    while (fgets(line, sizeof(line), f))
        printf("%4d | %s", line_no++, line);
    fclose(f);
}

void calculateAgeAndSort(const char* inputFile, const char* outputFile) {
    FILE* in = fopen(inputFile, "r");
    if (!in) { printf("Eroare deschidere %s!\n", inputFile); return; }
    int n;
    fscanf(in, "%d\n", &n);
    Student* students = (Student*)malloc(n * sizeof(Student));
    for (int i = 0; i < n; i++) {
        fgets(students[i].name, 50, in); students[i].name[strcspn(students[i].name, "\n")] = 0;
        fgets(students[i].surname, 50, in); students[i].surname[strcspn(students[i].surname, "\n")] = 0;
        fscanf(in, "%d %d %d\n", &students[i].dob.day, &students[i].dob.month, &students[i].dob.year);
        students[i].gender = fgetc(in); fgetc(in);
        fgets(students[i].address, 100, in); students[i].address[strcspn(students[i].address, "\n")] = 0;
        fgets(students[i].specialty, 20, in); students[i].specialty[strcspn(students[i].specialty, "\n")] = 0;
        fscanf(in, "%d\n", &students[i].group_no);
    }
    fclose(in);

    // Sortare dupa varsta (crescator = cei mai tineri primii)
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (compareStudentsByAge(&students[i], &students[j]) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }

    FILE* out = fopen(outputFile, "w");
    fprintf(out, "%d\n", n);
    for (int i = 0; i < n; i++) {
        int y, m, d;
        calculateAge(&students[i].dob, &y, &m, &d);
        fprintf(out, "%s\n%s\n%d %d %d\n%c\n%s\n%s\n%d\n",
                students[i].name, students[i].surname,
                students[i].dob.day, students[i].dob.month, students[i].dob.year,
                students[i].gender, students[i].address, students[i].specialty, students[i].group_no);
        fprintf(out, "VARSTA: %d ani %d luni %d zile\n", y, m, d);
    }
    fclose(out);
    free(students);
    printf("✔ Varste calculate si sortate in %s\n", outputFile);
}

void prependFile(const char* destFile, const char* srcFile) {
    FILE* src = fopen(srcFile, "r");
    if (!src) { printf("Eroare deschidere %s!\n", srcFile); return; }
    fseek(src, 0, SEEK_END);
    long srcSize = ftell(src);
    rewind(src);
    char* srcContent = (char*)malloc(srcSize + 1);
    fread(srcContent, 1, srcSize, src);
    srcContent[srcSize] = '\0';
    fclose(src);

    FILE* dest = fopen(destFile, "r");
    if (!dest) { printf("Eroare deschidere %s!\n", destFile); free(srcContent); return; }
    fseek(dest, 0, SEEK_END);
    long destSize = ftell(dest);
    rewind(dest);
    char* destContent = (char*)malloc(destSize + 1);
    fread(destContent, 1, destSize, dest);
    destContent[destSize] = '\0';
    fclose(dest);

    FILE* out = fopen(destFile, "w");
    fprintf(out, "=== DATE SORTATE DUPA VARSTA (din %s) ===\n", srcFile);
    fwrite(srcContent, 1, srcSize, out);
    fprintf(out, "\n=== DATE INITIALE ===\n");
    fwrite(destContent, 1, destSize, out);
    fclose(out);

    free(srcContent);
    free(destContent);
    printf("✔ %s a fost prepended la %s\n", srcFile, destFile);
}
