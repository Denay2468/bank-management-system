#ifndef BANK_H
#define BANK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ─── Data Structures ───────────────────────────────────────────────────────

typedef struct Transaction {
    char type[20];         // "DEPOSIT", "WITHDRAW", "TRANSFER_IN", "TRANSFER_OUT"
    double amount;
    double balance_after;
    char description[100];
    char date[30];
    struct Transaction *next;
} Transaction;

typedef struct Account {
    int id;
    char name[50];
    char username[30];
    char password[30];
    double balance;
    Transaction *transactions; // linked list of transactions
    struct Account *next;
} Account;

// ─── Global Variables ──────────────────────────────────────────────────────
extern Account *head;
extern int next_id;

// ─── Function Declarations ─────────────────────────────────────────────────

// account management
Account *create_account(const char *name, const char *username, const char *password, double initial_deposit);
Account *find_by_username(const char *username);
Account *find_by_id(int id);
void update_account(Account *acc, const char *name, const char *password);
void delete_account(const char *username);
void display_all_accounts();

// transaction management
void add_transaction(Account *acc, const char *type, double amount, double balance_after, const char *desc);
void deposit(Account *acc, double amount);
int  withdraw(Account *acc, double amount);
int  transfer(Account *from, Account *to, double amount);
void view_transactions(Account *acc);
void check_balance(Account *acc);

// auth
Account *login(const char *username, const char *password);

// utils
void get_current_time(char *buffer);
void clear_screen();
void print_line(char c, int n);

#endif
