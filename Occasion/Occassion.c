// DoneBy: Guhan M
#include<stdio.h>
#include<string.h>

struct activity {
    float taxi;
    float bf;
    float lunch;
    float dinner;
    float movie;
};

struct friends {
    char name[100];
    float amountSpent;
    struct activity act;
};

void askForActivity(char **activities);
void askForMembers(struct friends *fr, char activityName[], int activityNum);
void printMembers(struct friends *fr, char activityName[]);
void specificActivity(struct friends *fr, int who, int activityNum, float amount);
void printTable(struct friends *fr, float total);
void equalPayment(struct friends *fr, float avg);

int main() {

    //Declaration of objects and variables
    struct friends friend[6];
    char *activities[] = {"TAXI", "BREAKFAST", "LUNCH", "DINNER", "MOVIE"};
    char controller[] = "yes";
    char s[] = "yes";
    int i, select;
    int actCompleted[] = {0, 0, 0, 0, 0};
    float total = 0;

    while(1) {
        printf("Would you like to use default usernames (yes/no)?: ");
        scanf("%s", s);
        if((!strcmp(s, "yes")) || (!strcmp(s, "no"))) break;
    }

    //Initializing a value to the objects
    if(!strcmp(s, "no")) {
        printf("Enter SIX names one by one:\n");
        for (i = 0; i < 6; ++i){            
            printf("Name %d: ", i+1);
            getchar();
            gets(friend[i].name);   
        }
    } else {
        strcpy(friend[0].name, "Anand");
        strcpy(friend[1].name, "Bobby");
        strcpy(friend[2].name, "Dina");
        strcpy(friend[3].name, "Ezhil");
        strcpy(friend[4].name, "Hakim");
        strcpy(friend[5].name, "Henry");
    }
    for(i=0; i<6; i++) {
        friend[i].amountSpent = 0;
        friend[i].act.taxi = 0;
        friend[i].act.bf = 0;
        friend[i].act.lunch = 0;
        friend[i].act.dinner = 0;
        friend[i].act.movie = 0;
    }
    printf("\n\n");
    
    /* Loop untill all activities are completed
       As there are only 5 activities loop can run for maximum five times
    */
    for(i=0; i<5; i++) {
        //Ask the user to select an activity
        askForActivity(activities);
        scanf("%d", &select);
        if(select > 0 && select < 6) {
            if(!actCompleted[select-1]) {
                askForMembers(&friend[0], activities[select-1], select);
                actCompleted[select-1] = 1;
            } else {
                printf("\nThe selected activity %s is already paid...\n", activities[select-1]);
                i--;
                continue;
            }
        } else {
            printf("\nInvalid entry, Enter your selection again\n");
            i--;
            continue;
        }

        //Asking whether user like to continue?
        while(1) {
            if(i<4) {
                printf("\nWould you like to continue selecting ACTIVITIES (yes/no)?: ");
                scanf("%s", controller);
                if(!strcmp(controller,"yes") || !strcmp(controller,"no")) break;
            } else {
                strcpy(controller, "yes");
                break;
            }
        }
        if(!strcmp(controller,"no")) break;
        printf("\n\n");   

    }

    for(i=0; i<6; i++) {
        total += friend[i].amountSpent;
    }

    printTable(&friend[0], total);

    return 0;
}

void askForActivity(char **activities) {
    int i;
    printf("-----Select an Activity-----\n");
    for(i=0; i<5; i++) {
        printf("Press %d for %s\n", i+1, activities[i]);
    }
    printf("\n");
    printf("Enter your selection: ");
}

void printMembers(struct friends *fr, char activityName[]) {
    int i;
    printf("\n-----Select a member who is going to pay for %s-----\n", activityName);
    for(i=0; i<6; i++) {
        printf("Press %d for %s\n", i+1, (fr+i)->name);
    }
    printf("\n");
    printf("Enter your selection: ");
}

void specificActivity(struct friends *fr, int who, int activityNum, float amount) {
    switch(activityNum) {
        case 1:
            (fr+who)->act.taxi += amount;
            break;
        case 2:
            (fr+who)->act.bf += amount;
            break;
        case 3:
            (fr+who)->act.lunch += amount;
            break;
        case 4:
            (fr+who)->act.dinner += amount;
            break;
        case 5:
            (fr+who)->act.movie += amount;
            break;
    }
}

void askForMembers(struct friends *fr, char activityName[], int activityNum) {
    int i, select;
    char controller[] = "yes";
    float temp;
    while(!strcmp(controller, "yes")) {
        printMembers(fr, activityName);
        scanf("%d", &select);
        if(select > 0 && select < 7) {
            printf("\nEnter the amount paid by %s for %s: ", (fr+select-1)->name, activityName);
            scanf("%f", &temp);
            (fr+select-1)->amountSpent += temp;
            specificActivity(fr, select-1, activityNum, temp);
        } else {
            printf("\nInvalid entry, Enter your selection again\n");
            continue;
        }

        //Asking whether user like to continue?
        while(1) {
            printf("\nWould you like to select a member again (yes/no)?: ");
            scanf("%s", controller);
            if(!strcmp(controller,"yes") || !strcmp(controller,"no")) break;
        }
        if(!strcmp(controller,"no")) break;
        printf("\n");
    }
}

void equalPayment(struct friends *fr, float avg) {
    float tot;
    int i;
    for(i=0; i<6; i++) {
        tot = (fr+i)->amountSpent - avg;
        if(tot<0) {
            printf("%s needs to give Rs. %.2f\n", (fr+i)->name, (tot*-1));
        } else if(tot>0) {
            printf("%s needs to get Rs. %.2f\n", (fr+i)->name, (tot));
        } else {
            printf("%s had paid the average amount\n", (fr+i)->name);
        }
    }
}

void printTable(struct friends *fr, float total) {
    int i;
    printf("\nTotal amount spent for Occassion is: %.2f\n", total);
    printf("\n");
    printf("Name\t Taxi\t Breakfast\t Lunch\t    Dinner     Movie\tTotal \n");
    for(i=0; i<6; i++) {
        printf("%s", (fr+i)->name);printf("    ");
        printf(" %.2f", (fr+i)->act.taxi);printf("   ");
        printf(" %.2f ", (fr+i)->act.bf);printf("          ");
        printf(" %.2f ", (fr+i)->act.lunch);printf("    ");
        printf(" %.2f ", (fr+i)->act.dinner);printf("    ");
        printf(" %.2f ", (fr+i)->act.movie);printf("    ");
        printf(" %.2f ", (fr+i)->amountSpent);
        printf("\n");
    }

    printf("\n");
    equalPayment(fr, total/6);
}