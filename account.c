#include "bank.h"

Account *head = NULL;
int next_id = 1;

// ── Create a new account and append to linked list ──────────────────────────
Account *create_account(const char *name, const char *username,
                        const char *password, double initial_deposit) {
    // check for duplicate username
    if (find_by_username(username) != NULL) {
        printf("  [!] Username '%s' already exists.\n", username);
        return NULL;
    }

    Account *new_acc = (Account *)malloc(sizeof(Account));
    if (!new_acc) { printf("  [!] Memory allocation failed.\n"); return NULL; }

    new_acc->id           = next_id++;
    new_acc->balance      = 0.0;
    new_acc->transactions = NULL;
    new_acc->next         = NULL;
    strncpy(new_acc->name,     name,     49);
    strncpy(new_acc->username, username, 29);
    strncpy(new_acc->password, password, 29);

    // append to end of linked list
    if (head == NULL) {
        head = new_acc;
    } else {
        Account *cur = head;
        while (cur->next) cur = cur->next;
        cur->next = new_acc;
    }

    // record initial deposit if any
    if (initial_deposit > 0) {
        deposit(new_acc, initial_deposit);
    }

    return new_acc;
}

// ── Search linked list by username ──────────────────────────────────────────
Account *find_by_username(const char *username) {
    Account *cur = head;
    while (cur) {
        if (strcmp(cur->username, username) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

// ── Search linked list by ID ─────────────────────────────────────────────────
Account *find_by_id(int id) {
    Account *cur = head;
    while (cur) {
        if (cur->id == id) return cur;
        cur = cur->next;
    }
    return NULL;
}

// ── Update account name and/or password ─────────────────────────────────────
void update_account(Account *acc, const char *name, const char *password) {
    if (strlen(name) > 0)     strncpy(acc->name,     name,     49);
    if (strlen(password) > 0) strncpy(acc->password, password, 29);
    printf("  [+] Account updated successfully.\n");
}

// ── Delete an account node from the linked list ─────────────────────────────
void delete_account(const char *username) {
    Account *cur  = head;
    Account *prev = NULL;

    while (cur) {
        if (strcmp(cur->username, username) == 0) {
            // free transaction list
            Transaction *t = cur->transactions;
            while (t) {
                Transaction *tmp = t;
                t = t->next;
                free(tmp);
            }
            // unlink node
            if (prev) prev->next = cur->next;
            else       head      = cur->next;
            free(cur);
            printf("  [+] Account deleted successfully.\n");
            return;
        }
        prev = cur;
        cur  = cur->next;
    }
    printf("  [!] Account not found.\n");
}

// ── Display all accounts (admin view) ────────────────────────────────────────
void display_all_accounts() {
    if (!head) { printf("  No accounts found.\n"); return; }

    print_line('-', 65);
    printf("  %-5s %-20s %-15s %15s\n", "ID", "Name", "Username", "Balance");
    print_line('-', 65);

    Account *cur = head;
    while (cur) {
        printf("  %-5d %-20s %-15s %14.2f\n",
               cur->id, cur->name, cur->username, cur->balance);
        cur = cur->next;
    }
    print_line('-', 65);
}

// ── Login ─────────────────────────────────────────────────────────────────────
Account *login(const char *username, const char *password) {
    Account *acc = find_by_username(username);
    if (acc && strcmp(acc->password, password) == 0) return acc;
    return NULL;
}
