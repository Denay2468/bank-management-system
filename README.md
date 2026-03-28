# Bank Management System — C Programming

## How to Compile & Run

```bash
gcc main.c account.c transaction.c utils.c -o bank
./bank
```
Or on Windows (MinGW):
```bash
gcc main.c account.c transaction.c utils.c -o bank.exe
bank.exe
```

---

## How the Code Works

### Data Structures Used

**1. Account Linked List**
All bank accounts are stored as a singly linked list. Each node is an `Account` struct:
```
[Account: Alice] --> [Account: Bob] --> [Account: Charlie] --> NULL
```
- Adding an account: traverse to the end, append new node → O(n)
- Finding an account by username: traverse from head → O(n)
- Deleting an account: unlink and free node → O(n)

**2. Transaction Linked List (per Account)**
Each account has its own singly linked list of transactions. Every deposit, withdrawal, or transfer appends a new `Transaction` node to that list.
```
[DEPOSIT $1000] --> [WITHDRAW $200] --> [TRANSFER_OUT $50] --> NULL
```

---

## File Structure

| File | Purpose |
|------|---------|
| `bank.h` | All struct definitions and function declarations |
| `account.c` | Create, find, update, delete accounts |
| `transaction.c` | Deposit, withdraw, transfer, view history |
| `utils.c` | Helper functions (time, screen, formatting) |
| `main.c` | Menus and program entry point |

---

## Features

### User Management
- **Create Account** — register with name, username, password, optional initial deposit
- **Update Account** — change name or password after logging in
- **Delete Account** — remove account and free all memory

### Transaction Management
- **Deposit** — add funds to account
- **Withdraw** — remove funds (with insufficient balance check)
- **Transfer** — send money to another user by username
- **Check Balance** — view current balance
- **View Transaction History** — see all past transactions with date, type, amount

---

## Algorithm Explanation

### Linked List Insert (Create Account)
```
1. Allocate new Account node
2. Set all fields (id, name, username, password, balance)
3. If list is empty → set as head
4. Else → traverse to last node → set last->next = new node
```

### Linked List Search (Login / Find User)
```
1. Start at head
2. Compare each node's username with target
3. Return node if match found, else return NULL
```

### Linked List Delete (Delete Account)
```
1. Track current and previous node
2. Traverse until username matches
3. Set previous->next = current->next
4. Free transaction list of the node
5. Free the node itself
```
