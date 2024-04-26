#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Expense {
    char category[50];
    float amount;
};

// Function to add an expense entry
void addExpense(struct Expense *expenses, int *count) {
    printf("Enter expense category: ");
    scanf("%s", expenses[*count].category);

    printf("Enter expense amount: ");
    scanf("%f", &expenses[*count].amount);

    (*count)++;
}

// Function to display all expenses
void displayExpenses(struct Expense *expenses, int count) {
    printf("\nExpense Report:\n");
    for (int i = 0; i < count; ++i) {
        printf("%s: $%.2f\n", expenses[i].category, expenses[i].amount);
    }
}

// Function to calculate and display total expenses
void displayTotalExpense(struct Expense *expenses, int count) {
    float total = 0;
    for (int i = 0; i < count; ++i) {
        total += expenses[i].amount;
    }
    printf("\nTotal Expense: $%.2f\n", total);
}

// Function to save expenses to a file
void saveExpenses(struct Expense *expenses, int count) {
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s %.2f\n", expenses[i].category, expenses[i].amount);
    }

    fclose(file);
}

// Function to load expenses from a file
int loadExpenses(struct Expense *expenses) {
    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL) {
        printf("No expenses found.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s %f", expenses[count].category, &expenses[count].amount) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

int main() {
    struct Expense expenses[100]; // Assuming a maximum of 100 expenses
    int count = 0;

    // Load existing expenses from file
    count = loadExpenses(expenses);

    int choice;
    do {
        printf("\nExpense Tracker Menu:\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. View Total Expense\n");
        printf("4. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense(expenses, &count);
                break;
            case 2:
                displayExpenses(expenses, count);
                break;
            case 3:
                displayTotalExpense(expenses, count);
                break;
            case 4:
                saveExpenses(expenses, count);
                printf("Expenses saved. Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);

    return 0;
}
