#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SUBJECTS 20
#define MAX_DEPTS 5
#define MAX_DAYS 6
#define MAX_SLOTS 10

typedef struct {
    char sub[50];
    char teacher[50];
} Subject;

Subject data[MAX_DEPTS][MAX_SUBJECTS];
int n[MAX_DEPTS], deptCount;
char deptName[MAX_DEPTS][50];

char slots[MAX_SLOTS][30];
int isBreak[MAX_SLOTS];

int tt[MAX_DEPTS][MAX_DAYS][MAX_SLOTS];

int deptDays[MAX_DEPTS];
int deptMaxSlots[MAX_DEPTS];

char *dayNames[MAX_DAYS] = {"Mon","Tue","Wed","Thu","Fri","Sat"};

/* ================= INPUT ================= */

void input(){

    printf("\n===== ENTER DETAILS =====\n");

    printf("Enter number of departments: ");
    scanf("%d",&deptCount);
    getchar();

    for(int d=0; d<deptCount; d++){

        printf("\n--- Department %d ---\n", d+1);

        printf("Enter department name: ");
        fgets(deptName[d],50,stdin);
        deptName[d][strcspn(deptName[d],"\n")] = 0;

        int type;
        printf("Select type:\n1. Half Day (5 slots)\n2. Full Day (10 slots)\nEnter choice: ");
        scanf("%d",&type);

        deptMaxSlots[d] = (type==1 ? 5 : 10);

        int sat;
        printf("Include Saturday?\n1. Yes\n0. No\nEnter choice: ");
        scanf("%d",&sat);

        deptDays[d] = (sat==1 ? 6 : 5);

        getchar();

        printf("Enter number of subjects: ");
        scanf("%d",&n[d]);
        getchar();

        for(int i=0;i<n[d];i++){

            printf("\nSubject %d name: ", i+1);
            fgets(data[d][i].sub,50,stdin);
            data[d][i].sub[strcspn(data[d][i].sub,"\n")] = 0;

            printf("Enter teacher name: ");
            fgets(data[d][i].teacher,50,stdin);
            data[d][i].teacher[strcspn(data[d][i].teacher,"\n")] = 0;
        }
    }

    printf("\n✅ Input successfully stored!\n");
}

/* ================= SLOTS ================= */

void setSlots(){

    int h=9,m=0;

    for(int i=0;i<MAX_SLOTS;i++){

        if(i==2 || i==5 || i==8){
            int nh=h, nm=m+40;
            if(nm>=60){ nh+=nm/60; nm%=60; }

            sprintf(slots[i],"%02d:%02d-%02d:%02d",h,m,nh,nm);

            h=nh; m=nm;
            isBreak[i]=1;
        }
        else{
            int nh=h, nm=m+55;
            if(nm>=60){ nh+=nm/60; nm%=60; }

            sprintf(slots[i],"%02d:%02d-%02d:%02d",h,m,nh,nm);

            h=nh; m=nm;
            isBreak[i]=0;
        }
    }

    printf("\nSlots Generated:\n");
    for(int i=0;i<MAX_SLOTS;i++)
        printf("%d. %s\n",i+1,slots[i]);
}

/* ================= GRAPH COLOR CHECK ================= */

int canPlace(int d,int day,int slot,int sub){

    for(int d2=0; d2<deptCount; d2++){
        int s = tt[d2][day][slot];

        if(s != -1){
            if(strcmp(data[d][sub].teacher, data[d2][s].teacher) == 0)
                return 0;
        }
    }
    return 1;
}

/* ================= GREEDY ================= */

int selectGreedy(int d,int day,int slot){

    int best=-1;
    int bestScore=999999;

    for(int i=0;i<n[d];i++){

        if(!canPlace(d,day,slot,i))
            continue;

        int score = rand()%5;

        if(score < bestScore){
            bestScore = score;
            best = i;
        }
    }

    return best;
}

/* ================= BACKTRACK ================= */

int solve(int d,int day,int slot){

    if(day >= deptDays[d]) return 1;

    int nd=day, ns=slot+1;

    if(ns >= deptMaxSlots[d]){
        ns=0;
        nd++;
    }

    if(isBreak[slot])
        return solve(d,nd,ns);

    int g = selectGreedy(d,day,slot);

    if(g != -1){
        tt[d][day][slot]=g;

        if(solve(d,nd,ns))
            return 1;

        tt[d][day][slot]=-1;
    }

    for(int i=0;i<n[d];i++){
        if(canPlace(d,day,slot,i)){
            tt[d][day][slot]=i;

            if(solve(d,nd,ns))
                return 1;

            tt[d][day][slot]=-1;
        }
    }

    return 0;
}

/* ================= GENERATE ================= */

void generate(){

    for(int d=0;d<deptCount;d++)
        for(int i=0;i<MAX_DAYS;i++)
            for(int j=0;j<MAX_SLOTS;j++)
                tt[d][i][j]=-1;

    for(int d=0;d<deptCount;d++)
        solve(d,0,0);

    printf("\n✅ Timetable Generated Successfully!\n");
}

/* ================= SHOW ================= */

void show(){

    for(int d=0;d<deptCount;d++){

        printf("\n=== %s ===\n",deptName[d]);

        printf("| Day ");
        for(int s=0;s<deptMaxSlots[d];s++)
            printf("| %-18s",slots[s]);
        printf("|\n");

        for(int day=0;day<deptDays[d];day++){

            printf("| %-3s ",dayNames[day]);

            for(int s=0;s<deptMaxSlots[d];s++){

                if(isBreak[s] || tt[d][day][s]==-1)
                    printf("| %-18s","---");
                else{
                    int id=tt[d][day][s];

                    char cell[60];
                    sprintf(cell,"%s/%s",data[d][id].sub,data[d][id].teacher);

                    printf("| %-18s",cell);
                }
            }
            printf("|\n");
        }
    }
}

/* ================= MANAGE ================= */

void manage(){

    int d,day,slot;

    printf("\nSelect Dept:\n");
    for(int i=0;i<deptCount;i++)
        printf("%d. %s\n",i+1,deptName[i]);

    scanf("%d",&d); d--;

    printf("\nSelect Day:\n");
    for(int i=0;i<deptDays[d];i++)
        printf("%d. %s\n",i+1,dayNames[i]);

    scanf("%d",&day); day--;

    printf("\nSelect Slot:\n");
    for(int i=0;i<deptMaxSlots[d];i++)
        printf("%d. %s\n",i+1,slots[i]);

    scanf("%d",&slot); slot--;

    printf("\n1 Add  2 Delete: ");
    int ch; scanf("%d",&ch);

    if(ch==1){

        printf("\nSubjects:\n");
        for(int i=0;i<n[d];i++)
            printf("%d. %s / %s\n",i+1,data[d][i].sub,data[d][i].teacher);

        int s;
        scanf("%d",&s); s--;

        tt[d][day][slot]=s;
        printf("Added!\n");
    }
    else{
        tt[d][day][slot]=-1;
        printf("Deleted!\n");
    }
}

/* ================= MAIN ================= */

int main(){

    srand(time(0));

    int ch;

    while(1){

        printf("\n========== MENU ==========\n");
        printf("1. Enter Input Data\n");
        printf("2. Generate Time Slots\n");
        printf("3. Generate Timetable\n");
        printf("4. Display Timetable\n");
        printf("5. Manage Timetable\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&ch);

        switch(ch){
            case 1: input(); break;
            case 2: setSlots(); break;
            case 3: generate(); break;
            case 4: show(); break;
            case 5: manage(); break;
            case 6: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}