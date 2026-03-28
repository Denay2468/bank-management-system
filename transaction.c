#include "bank.h"

// ── Append a transaction to an account's linked list ────────────────────────
void add_transaction(Account *acc, const char *type, double amount,
                     double balance_after, const char *desc) {
    Transaction *t = (Transaction *)malloc(sizeof(Transaction));
    if (!t) return;

    strncpy(t->type,        type,  19);
    strncpy(t->description, desc,  99);
    t->amount        = amount;
    t->balance_after = balance_after;
    t->next          = NULL;
    get_current_time(t->date);

    // append to end of transaction list
    if (acc->transactions == NULL) {
        acc->transactions = t;
    } else {
        Transaction *cur = acc->transactions;
        while (cur->next) cur = cur->next;
        cur->next = t;
    }
}

// ── Deposit ──────────────────────────────────────────────────────────────────
void deposit(Account *acc, double amount) {
    if (amount <= 0) { printf("  [!] Amount must be positive.\n"); return; }
    acc->balance += amount;
    char desc[100];
    snprintf(desc, 100, "Deposit of $%.2f", amount);
    add_transaction(acc, "DEPOSIT", amount, acc->balance, desc);
    printf("  [+] Deposited $%.2f successfully. New balance: $%.2f\n",
           amount, acc->balance);
}

// ── Withdraw ─────────────────────────────────────────────────────────────────
int withdraw(Account *acc, double amount) {
    if (amount <= 0)           { printf("  [!] Amount must be positive.\n");      return 0; }
    if (amount > acc->balance) { printf("  [!] Insufficient balance.\n");         return 0; }
    acc->balance -= amount;
    char desc[100];
    snprintf(desc, 100, "Withdrawal of $%.2f", amount);
    add_transaction(acc, "WITHDRAW", amount, acc->balance, desc);
    printf("  [+] Withdrew $%.2f successfully. New balance: $%.2f\n",
           amount, acc->balance);
    return 1;
}

// ── Transfer ─────────────────────────────────────────────────────────────────
int transfer(Account *from, Account *to, double amount) {
    if (amount <= 0)            { printf("  [!] Amount must be positive.\n");  return 0; }
    if (amount > from->balance) { printf("  [!] Insufficient balance.\n");     return 0; }
    if (from == to)             { printf("  [!] Cannot transfer to yourself.\n"); return 0; }

    from->balance -= amount;
    to->balance   += amount;

    char desc[100];
    snprintf(desc, 100, "Transfer to %s", to->username);
    add_transaction(from, "TRANSFER_OUT", amount, from->balance, desc);

    snprintf(desc, 100, "Transfer from %s", from->username);
    add_transaction(to, "TRANSFER_IN", amount, to->balance, desc);

    printf("  [+] Transferred $%.2f to %s. Your new balance: $%.2f\n",
           amount, to->name, from->balance);
    return 1;
}

// ── Check balance ─────────────────────────────────────────────────────────────
void check_balance(Account *acc) {
    print_line('-', 40);
    printf("  Account Holder : %s\n", acc->name);
    printf("  Account ID     : %d\n", acc->id);
    printf("  Current Balance: $%.2f\n", acc->balance);
    print_line('-', 40);
}

// ── View transaction history ─────────────────────────────────────────────────
void view_transactions(Account *acc) {
    if (!acc->transactions) {
        printf("  No transactions found.\n");
        return;
    }

    print_line('-', 75);
    printf("  %-16s %-15s %12s %15s\n", "Date", "Type", "Amount", "Balance After");
    print_line('-', 75);

    Transaction *t = acc->transactions;
    while (t) {
        printf("  %-16s %-15s %11.2f %14.2f\n",
               t->date, t->type, t->amount, t->balance_after);
        t = t->next;
    }
    print_line('-', 75);
}
