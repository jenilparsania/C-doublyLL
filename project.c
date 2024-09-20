#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//movie struct definition
struct movie {
    struct movie *prev;
    char name[50];
    char director[50];
    int year;
    float rating;
    float price;
    int views;
    int renter;
    char dueDate[15];
    struct movie *next;
    
};

struct movie *NewMovie();
void addMovie(struct movie *start);
void browseMovies(struct movie *start);
void showMovie(struct movie *current);
void changeMovie(struct movie *start);
void editMovie(struct movie *current);
struct movie *deleteMovie(struct movie *start);
void save(struct movie *start, FILE *p_file);
struct movie *load(FILE *p_file);
struct movie *sort(struct movie *start);
void searchMovie(struct movie *start);
float calculateEarnings(struct movie *start);
struct movie *exitProgram(struct movie *start);


void showMainMenu();
void showLoadMenu();

int main () {
    struct movie *start = NULL;
    int choice = 0;
    int ch;
    FILE *p_file;
    float total = 0.00;

    showLoadMenu();
    scanf("%d", &choice);
    while ((ch = getchar()) != '\n' && ch != EOF);

    switch (choice) {
        case 1: start = load(p_file); break;
        default: break;
    }

    choice = 0;
    while (choice != 9)
    {
        showMainMenu();

        scanf("%d", &choice);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        //call function for different options
        switch(choice) 
        {
            case 1:
            if (start == NULL)
            {
                start = NewMovie();
            }
            else
            {
                addMovie(start);
            };
            break;
            case 2: browseMovies(start); break;
            case 3: changeMovie(start); break;
            case 4: start = deleteMovie(start); break;
            case 5: save(start, p_file); break;
            case 6: start = sort(start); break;
            case 7: searchMovie(start); break;
            case 8: total = calculateEarnings(start); printf("\nStore has earned $%.2f\n", total); break;
            case 9: start = exitProgram(start); break;
            default: fputs("\nError. Choice not found.", stdout);
        }
    }

    return 0;
}

struct movie *NewMovie() {
    struct movie *new = NULL;
    int ch;

    new = (struct movie *)malloc(sizeof(struct movie));
    if (new == NULL)
    {
        fputs("\n\nMemory allocation error", stdout);
        exit(1);
    }

    fputs("\n\nEnter Movie Details...", stdout);
    fputs("\nName:", stdout);
    fgets(new->name, 50, stdin);
    new->name[strcspn(new->name, "\n")] = 0; //strip trailing \n
    
        fputs("Director:", stdout);
        fgets(new->director, 50, stdin);
        new->director[strcspn(new->director, "\n")] = 0;

        fputs("Year:", stdout);
        scanf("%d", &new->year);
        while ((ch = getchar()) != '\n' && ch != EOF);

        fputs("Rating:", stdout);
        scanf("%f", &new->rating);
        while ((ch = getchar()) != '\n' && ch != EOF);

        fputs("Price:", stdout);
        scanf("%f", &new->price);
        while ((ch = getchar()) != '\n' && ch != EOF);

        fputs("Number of Rentals:", stdout);
        scanf("%d", &new->views);
        while ((ch = getchar()) != '\n' && ch != EOF);

        fputs("Renter ID:", stdout);
        scanf("%d", &new->renter);
        while ((ch = getchar()) != '\n' && ch != EOF);

        fputs("Due Date:", stdout);
        fgets(new->dueDate, 15, stdin);
        new->dueDate[strcspn(new->dueDate, "\n")] = 0;
    

    new->next = NULL;
    // making the prev pointer as NULL because it is the first pointer
    new->prev = NULL;

    return new;
}

void addMovie(struct movie *start) {
    fputs("\n\nAdding new node...", stdout);

    //scroll to last node
    struct movie *current = start;
    struct movie * new;

    new = NewMovie();
    if(start == NULL){
        new->next = NULL;
        new->prev = NULL;
        start = new;


    }else{
        while(current->next != NULL){
            current = current->next;
        }

        current->next = new;
        new->prev = current;
        new->next = NULL;
        
    }

    printf("Node Inserted\n"); 
}

void browseMovies(struct movie *start) {
    fputs("\n\nBrowsing through entries...\n", stdout);
    char choice;
    choice = 'Y';
    int ch;
    int count = 1;
    char browseInverse = 'n';

    struct movie *current = start;

    puts("Do you want to browse Inversly?(y/n) ");
    browseInverse = fgetc(stdin);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (browseInverse == 'y'){
        puts("browse inverse running");
        struct movie *current = start;

        while(current->next != NULL){

            count++;
            current = current->next;   
        }
        // after this loop , this would make it to the last pointer

        while(current!=start){
        printf("\n\n%d\n",count);
        
        showMovie(current);

        if(current == NULL){
            puts("Starting of database reached");
            break;
        }
        

        current = current->prev;
        count--;
        }

        printf("\n");
        showMovie(current);
        return;
    }

    count = 0;

    while (current != NULL && choice != 'N' && choice != 'n') {
        count++;
        printf("\n\nMovie #%d\n", count);

        showMovie(current);
        // show movie just prints the whole movie node

        current = current->next;
        // just checking if the  prev pointer is working or not 
        // if ((current->prev)!= NULL){
        //     puts("PREV WORKING");
        //     printf("%s\n",current->prev->name);
        // }

        if (current != NULL) {
            fputs("\nBrowse to next entry (Y/N)?", stdout);
            choice = fgetc(stdin);
            while ((ch = getchar()) != '\n' && ch != EOF);
        } else {
            puts("\nEnd Of Database");
            puts("\nEnter 'C' to return to the menu");
            choice = fgetc(stdin);
            while ((ch = getchar()) != '\n' && ch != EOF);
            break;
        }
    }

}


void showMovie(struct movie *current) {
    if (current != NULL) {
        printf("Name: %s\n", current->name);
        printf("Director: %s\n", current->director);
        printf("Year: %d\n", current->year);
        printf("Rating: %.1f\n", current->rating);
        printf("Price: %.2f\n", current->price);
        printf("Number of Rentals: %d\n", current->views);
        printf("Current Renter: %d\n", current->renter);
        printf("Due Date: %s\n", current->dueDate);
        printf("\n");
    } 
}

void changeMovie(struct movie *start) {
    fputs("\n\nModifying entry...", stdout);
    int position, counter = 1;
    int ch;
    struct movie *current = start;

    fputs("\n\nEnter position: ", stdout);
    scanf("%d", &position);
    while ((ch = getchar()) != '\n' && ch != EOF);

    
    while (counter < position && current != NULL)
    {
        counter++;
        current = current->next;
    }

    if (current == NULL) {
        puts("\nError! Out of Bounds:\n");
    } else {
        editMovie(current);
    }

    puts("\nFinished editing...\n");
}

void editMovie(struct movie *current) {
    puts("\nYou have selected the following movie:\n");
    char choice = 'N';
    int field = 0;
    int ch;

    printf("Name: %s\n", current->name);
    puts("\nDo you want to edit this record (Y/N)?");
    choice = fgetc(stdin);
    while ((ch = getchar()) != '\n' && ch != EOF);
    
    if (choice == 'Y' || choice == 'y') {

        char choice2 = 'Y';
        int field = 0;

        while (choice2 == 'Y' || choice2 == 'y') {

            puts("\nDo you want to edit this record (Y/N)?");
            puts("Please enter the number corresponding to the field you wish to change: \n");
            puts("1. Name");
            puts("2. Director");
            puts("3. Year");
            puts("4. Rating");
            puts("5. Price");
            puts("6. Number of Rentals");
            puts("7. Renter ID");
            puts("8. Due Date");
            scanf("%d", &field);
            while ((ch = getchar()) != '\n' && ch != EOF);

            switch (field) {
                case 1: 
                    fputs("New Name:", stdout);
                    fgets(current->name, 50, stdin);
                    current->name[strcspn(current->name, "\n")] = 0;
                    break;
                case 2:
                    fputs("New Director:", stdout);
                    fgets(current->director, 50, stdin);
                    current->director[strcspn(current->director, "\n")] = 0;
                    break;
                case 3:
                    fputs("New Year:", stdout);
                    scanf("%d", &current->year);
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    break;
                case 4:
                    fputs("New Rating:", stdout);
                    scanf("%f", &current->rating);
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    break;
                case 5:
                    fputs("New Price:", stdout);
                    scanf("%f", &current->price);
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    break;
                case 6:
                    fputs("Number of Rentals:", stdout);
                    scanf("%d", &current->views);
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    break;
                case 7:
                    fputs("Renter ID:", stdout);
                    scanf("%d", &current->renter);
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    break;
                case 8:
                    fputs("Due Date:", stdout);
                    fgets(current->dueDate, 10, stdin);
                    current->dueDate[strcspn(current->dueDate, "\n")] = 0;
                    break;
            }

            puts("\nDo you want to keep editing this record (Y/N)?");
            choice2 = fgetc(stdin);
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    }

}

struct movie *deleteMovie(struct movie *start) {
    fputs("\n\nDelete entry...", stdout);
    int position, counter = 1;
    int ch;
    struct movie *current = start, *last = start;
    struct movie *next = NULL;

    fputs("\n\nEnter position: ", stdout);
    scanf("%d", &position);
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (current != NULL) {
        next = current->next;
    } 
    
    while (counter < position && current != NULL)
    {
        last = current;
        current = current->next;
        next = current->next;
        counter++;
    }

    if (current == NULL) {
        puts("\nError! Out of Bounds:\n");
    } else {
        
        puts("\nYou have selected the following movie:\n");
        char choice = 'N';
        int field = 0;
        int ch;

        printf("Name: %s\n", current->name);
        puts("\nDo you want to delete this record (Y/N)?");
        choice = fgetc(stdin);
        while ((ch = getchar()) != '\n' && ch != EOF);
        
        if (choice == 'Y' || choice == 'y') {

            if (position == 1) {
                //remove head node, reassign start
                start = next;
            } else if (next == NULL) {
                //remove tail node
                last->next = NULL;
            } else {
                //remove middle node
                last->next = next;
            }
            free(current);

            puts("\nEntry Removed...\n");
        } else {
            puts("\nEntry NOT Removed...\n");
        }

    }

    return start;
}

void save(struct movie *start, FILE *p_file) {
    fputs("\n\nSaving data...", stdout);

    char filename[15] = "database.txt";
    struct movie *current = start;
    int nodes=0;

    while (current != NULL) {
        current = current->next;
        nodes++;
    }

    p_file = fopen(filename, "wb");
    if (p_file == NULL) {
        puts("Error opening file.");
        exit(1);
    }
    fprintf(p_file, "%d", nodes);

    current = start;
    while(current != NULL) {
        fwrite(current, sizeof(struct movie), 1, p_file);
        current = current->next;
    }

    if (&fwrite != 0) {
        puts("\nSave Successful.\n");
    } else {
        puts("\nError saving.\n");
    }
    fclose(p_file);

}

struct movie *load(FILE *p_file) {
    fputs("\n\nLoading data\n", stdout);

    char filename[15] = "database.txt";
    struct movie *current = NULL, *new = NULL, *start = NULL;
    int nodes = 0, counter = 0;

    p_file = fopen(filename, "rb");
    if (p_file == NULL) {
        puts("\nError opening file.");
        exit(1);
    }
    
    fscanf(p_file, "%d", &nodes);

    printf("%d nodes",nodes );
    while (counter < nodes) {
        puts("new node");

        new = (struct movie *)malloc(sizeof(struct movie));
        if (new == NULL) {
            puts("Memory allocation error");
            exit(1);
        }

        if (current != NULL) {
            current->next = new;
        } 
        puts("here");
        current = new;
        if (start == NULL) {
            start = current;
        }

        fread(new, sizeof(struct movie), 1, p_file);
        new->next = NULL;

        counter ++;
    }
    

    fclose(p_file);
   
    return start;
}

struct movie *sort(struct movie *start) {
    fputs("\n\nSorting data", stdout);

    return start;
}

void searchMovie(struct movie *start) {
    fputs("\n\nSearching for movie", stdout);

    struct movie *current = start;

    char name[50];
    int matches = 0;

    puts("\nPlease enter an movie name to search for:");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;
    
    while(current != NULL) {
        if(strstr(current->name, name)) {
            showMovie(current);
            matches++;
        }
        current = current->next;
    }
    printf("There were %d match(es).\n", matches);
}

float calculateEarnings(struct movie *current) {
    fputs("\n\nCalculating for earnings...", stdout);

    float total = 0.00;

    while (current != NULL)
    {
        total += current->price * current->views;
        current = current->next;
    }

    return total;
}

void showMainMenu() {
        puts("\nPlease choose an option:");
        puts("1. Add new entry");
        puts("2. Browse entries");
        puts("3. Modify existing entry ");
        puts("4. Delete entry");
        puts("5. Save entries ");
        puts("6. Sort entries");
        puts("7. Search for entry");
        puts("8. Calcuate total");
        puts("9. Exit");
        puts("10.Browse Inversly from last");
}

void showLoadMenu() {
    puts("\nWould you like to:");
    puts("1. Load a previously saved library database");
    puts("2. Load a new database\n");
}

struct movie *exitProgram(struct movie *start) {
    fputs("\n\nFreeing Memory...", stdout);

    struct movie *current = start;
    struct movie *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    fputs("\nCleanup complete. Exiting...", stdout);
    return start;
}