#include "student_adt.h"

int main() {
    Stack st; initStack(&st);
    Queue simple, deque, circular, priority;
    initQueue(&simple); initQueue(&deque);
    initQueue(&circular); initQueue(&priority);

    const char* expFile = "experiment.txt";
    const char* outFile = "output.txt";

    int opt, sub, criterion, order, pos;
    char nameSearch[50], surnameSearch[50];
    Student temp;

    do {
        printf("\n╔══════════════════════════════════════════════════╗\n");
        printf("║        STUDENT REGISTRY MANAGEMENT SYSTEM        ║\n");
        printf("╠══════════════════════════════════════════════════╣\n");
        printf("║  1. STACK (LIFO)                                 ║\n");
        printf("║  2. SIMPLE QUEUE (FIFO)                          ║\n");
        printf("║  3. DOUBLE-ENDED QUEUE (DEQUE)                   ║\n");
        printf("║  4. CIRCULAR QUEUE                               ║\n");
        printf("║  5. PRIORITY QUEUE (dupa varsta)                 ║\n");
        printf("║──────────────────────────────────────────────────║\n");
        printf("║  LAB5 - OPERATII CU FISIERE                      ║\n");
        printf("║  6. Creare experiment.txt (introducere studenti) ║\n");
        printf("║  7. Afisare experiment.txt                       ║\n");
        printf("║  8. Calcul varsta + sortare -> output.txt        ║\n");
        printf("║  9. Prepend output.txt la experiment.txt         ║\n");
        printf("║ 10. Afisare output.txt                           ║\n");
        printf("║──────────────────────────────────────────────────║\n");
        printf("║  0. EXIT                                         ║\n");
        printf("╚══════════════════════════════════════════════════╝\n");
        printf("Alegere: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1: // STACK
                do {
                    printf("\n--- STACK MENU ---\n");
                    printf("1. Push\n2. Pop\n3. Afisare\n4. Cauta dupa nume\n5. Cauta dupa pozitie\n6. Sterge dupa pozitie\n7. Salvare fisier\n0. Back\n");
                    scanf("%d", &sub);
                    if (sub == 1) pushStack(&st, createStudent());
                    else if (sub == 2) popStack(&st);
                    else if (sub == 3) displayStack(&st);
                    else if (sub == 4) {
                        printf("Nume: "); scanf("%49s", nameSearch);
                        printf("Prenume: "); scanf("%49s", surnameSearch);
                        int p = searchStackByReg(&st, nameSearch, surnameSearch);
                        if (p != -1) printf("Gasit la pozitia %d\n", p);
                        else printf("Nu exista.\n");
                    } else if (sub == 5) {
                        printf("Pozitie: "); scanf("%d", &pos);
                        if (searchStackByPosition(&st, pos, &temp))
                            printStudent(&temp);
                        else printf("Pozitie invalida.\n");
                    } else if (sub == 6) {
                        printf("Pozitie de sters: "); scanf("%d", &pos);
                        deleteStackByPosition(&st, pos);
                    } else if (sub == 7) saveStackToFile(&st);
                } while (sub != 0);
                break;

            case 2: // SIMPLE QUEUE
                do {
                    printf("\n--- SIMPLE QUEUE MENU ---\n");
                    printf("1. Enqueue\n2. Dequeue\n3. Afisare\n4. Cauta dupa nume\n5. Sterge dupa pozitie\n6. Salvare fisier\n0. Back\n");
                    scanf("%d", &sub);
                    if (sub == 1) enqueueSimple(&simple, createStudent());
                    else if (sub == 2) dequeueSimple(&simple);
                    else if (sub == 3) displayQueue(&simple);
                    else if (sub == 4) {
                        printf("Nume: "); scanf("%49s", nameSearch);
                        printf("Prenume: "); scanf("%49s", surnameSearch);
                        int p = searchQueueByReg(&simple, nameSearch, surnameSearch);
                        if (p != -1) printf("Gasit la pozitia %d\n", p);
                        else printf("Nu exista.\n");
                    } else if (sub == 5) {
                        printf("Pozitie de sters: "); scanf("%d", &pos);
                        deleteQueueByPosition(&simple, pos);
                    } else if (sub == 6) saveQueueToFile(&simple, "Simple Queue");
                } while (sub != 0);
                break;

            case 3: // DEQUE
                do {
                    printf("\n--- DEQUE MENU ---\n");
                    printf("1. Insert Front\n2. Insert Rear\n3. Delete Front\n4. Delete Rear\n5. Afisare\n6. Salvare fisier\n0. Back\n");
                    scanf("%d", &sub);
                    if (sub == 1) insertFrontDeque(&deque, createStudent());
                    else if (sub == 2) insertRearDeque(&deque, createStudent());
                    else if (sub == 3) deleteFrontDeque(&deque);
                    else if (sub == 4) deleteRearDeque(&deque);
                    else if (sub == 5) displayDeque(&deque);
                    else if (sub == 6) saveQueueToFile(&deque, "Deque");
                } while (sub != 0);
                break;

            case 4: // CIRCULAR QUEUE
                do {
                    printf("\n--- CIRCULAR QUEUE MENU ---\n");
                    printf("1. Enqueue\n2. Dequeue\n3. Afisare\n4. Salvare fisier\n0. Back\n");
                    scanf("%d", &sub);
                    if (sub == 1) enqueueCircular(&circular, createStudent());
                    else if (sub == 2) dequeueCircular(&circular);
                    else if (sub == 3) displayCircular(&circular);
                    else if (sub == 4) saveQueueToFile(&circular, "Circular Queue");
                } while (sub != 0);
                break;

            case 5: // PRIORITY QUEUE
                do {
                    printf("\n--- PRIORITY QUEUE MENU ---\n");
                    printf("1. Enqueue (cu prioritate dupa varsta)\n2. Dequeue\n3. Afisare\n4. Salvare fisier\n0. Back\n");
                    scanf("%d", &sub);
                    if (sub == 1) {
                        printf("Ordine: 1=Ce mai tineri primii, 0=Ce mai batrani primii: ");
                        scanf("%d", &criterion);
                        enqueuePriority(&priority, createStudent(), criterion);
                    } else if (sub == 2) dequeuePriority(&priority);
                    else if (sub == 3) displayPriority(&priority);
                    else if (sub == 4) saveQueueToFile(&priority, "Priority Queue");
                } while (sub != 0);
                break;

            case 6:
                createExperimentFile(expFile);
                break;
            case 7:
                displayFileContent(expFile);
                break;
            case 8:
                calculateAgeAndSort(expFile, outFile);
                break;
            case 9:
                prependFile(expFile, outFile);
                break;
            case 10:
                displayFileContent(outFile);
                break;
            case 0:
                printf("\n🚪 Iesire din program. La revedere!\n");
                break;
            default:
                printf("Optiune invalida!\n");
        }
    } while (opt != 0);

    return 0;
}
