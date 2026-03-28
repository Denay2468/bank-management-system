#include "bank.h"

// ── Menu helpers ─────────────────────────────────────────────────────────────

void print_header(const char *title) {
    clear_screen();
    print_line('=', 50);
    printf("       BANK MANAGEMENT SYSTEM\n");
    print_line('=', 50);
    printf("  %s\n", title);
    print_line('-', 50);
}

void press_enter() {
    printf("\n  Press Enter to continue...");
    getchar(); getchar();
}

// ── User menu (after login) ───────────────────────────────────────────────────

void user_menu(Account *acc) {
    int choice;
    double amount;
    char username[30];

    while (1) {
        print_header("USER MENU");
        printf("  Logged in as: %s (ID: %d)\n\n", acc->name, acc->id);
        printf("  1. Check Balance\n");
        printf("  2. Deposit Money\n");
        printf("  3. Withdraw Money\n");
        printf("  4. Transfer Money\n");
        printf("  5. View Transaction History\n");
        printf("  6. Update Account Info\n");
        printf("  7. Delete My Account\n");
        printf("  0. Logout\n");
        print_line('-', 50);
        printf("  Choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            print_header("CHECK BALANCE");
            check_balance(acc);
            press_enter();
            break;

        case 2:
            print_header("DEPOSIT MONEY");
            printf("  Enter amount: $");
            scanf("%lf", &amount);
            deposit(acc, amount);
            press_enter();
            break;

        case 3:
            print_header("WITHDRAW MONEY");
            check_balance(acc);
            printf("  Enter amount: $");
            scanf("%lf", &amount);
            withdraw(acc, amount);
            press_enter();
            break;

        case 4: {
            print_header("TRANSFER MONEY");
            check_balance(acc);
            printf("  Enter recipient username: ");
            scanf("%s", username);
            Account *to = find_by_username(username);
            if (!to) {
                printf("  [!] User '%s' not found.\n", username);
            } else {
                printf("  Sending to: %s\n", to->name);
                printf("  Enter amount: $");
                scanf("%lf", &amount);
                transfer(acc, to, amount);
            }
            press_enter();
            break;
        }

        case 5:
            print_header("TRANSACTION HISTORY");
            view_transactions(acc);
            press_enter();
            break;

        case 6: {
            print_header("UPDATE ACCOUNT");
            char new_name[50], new_pass[30];
            printf("  New name (leave blank to keep): ");
            scanf(" %[^\n]", new_name);
            printf("  New password (leave blank to keep): ");
            scanf(" %[^\n]", new_pass);
            update_account(acc, new_name, new_pass);
            press_enter();
            break;
        }

        case 7: {
            print_header("DELETE ACCOUNT");
            char confirm[5];
            printf("  Are you sure? This cannot be undone. (yes/no): ");
            scanf("%s", confirm);
            if (strcmp(confirm, "yes") == 0) {
                delete_account(acc->username);
                printf("  Goodbye!\n");
                press_enter();
                return; // go back to main menu
            } else {
                printf("  Cancelled.\n");
                press_enter();
            }
            break;
        }

        case 0:
            printf("  Logged out.\n");
            press_enter();
            return;

        default:
            printf("  [!] Invalid choice.\n");
            press_enter();
        }
    }
}

// ── Main menu ────────────────────────────────────────────────────────────────

void main_menu() {
    int choice;

    while (1) {
        print_header("MAIN MENU");
        printf("  1. Login\n");
        printf("  2. Create New Account\n");
        printf("  3. View All Accounts\n");
        printf("  0. Exit\n");
        print_line('-', 50);
        printf("  Choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1: {
            print_header("LOGIN");
            char username[30], password[30];
            printf("  Username: "); scanf("%s", username);
            printf("  Password: "); scanf("%s", password);
            Account *acc = login(username, password);
            if (acc) {
                printf("  [+] Welcome back, %s!\n", acc->name);
                press_enter();
                user_menu(acc);
            } else {
                printf("  [!] Invalid username or password.\n");
                press_enter();
            }
            break;
        }

        case 2: {
            print_header("CREATE NEW ACCOUNT");
            char name[50], username[30], password[30];
            double initial;
            printf("  Full Name  : "); scanf(" %[^\n]", name);
            printf("  Username   : "); scanf("%s", username);
            printf("  Password   : "); scanf("%s", password);
            printf("  Initial Deposit ($0 to skip): $"); scanf("%lf", &initial);

            Account *acc = create_account(name, username, password, initial);
            if (acc) {
                printf("  [+] Account created! Your ID is: %d\n", acc->id);
            }
            press_enter();
            break;
        }

        case 3:
            print_header("ALL ACCOUNTS");
            display_all_accounts();
            press_enter();
            break;

        case 0:
            print_header("GOODBYE");
            printf("  Thank you for using Bank Management System!\n\n");
            // free all memory before exit
            Account *cur = head;
            while (cur) {
                Transaction *t = cur->transactions;
                while (t) { Transaction *tmp = t; t = t->next; free(tmp); }
                Account *tmp = cur;
                cur = cur->next;
                free(tmp);
            }
            exit(0);

        default:
            printf("  [!] Invalid choice.\n");
            press_enter();
        }
    }
}

// ── Entry point ───────────────────────────────────────────────────────────────

int main() {
    // seed some demo accounts
    create_account("Alice Johnson", "alice", "alice123", 1000.00);
    create_account("Bob Smith",     "bob",   "bob123",   500.00);

    main_menu();
    return 0;
}
