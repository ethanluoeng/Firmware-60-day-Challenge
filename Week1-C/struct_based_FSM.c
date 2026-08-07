#include <stdio.h>
#include <stdlib.h>

// Every state of a vending machine
typedef enum {
    IDLE,
    HAS_MONEY,
    DISPENSING
} States;

// All possible inputs
typedef enum {
    COIN_INSERTED,
    ITEM_SELECTED,
    ITEM_DISPENSED
} Inputs;

// Action functions - in a real-world system, these functions could actually carry out a task, but they will just print something for now
void ready_to_select(void) { printf("Money recieved - please select an item\n"); }
void no_funds(void) { printf("No funds! Please insert coin before selecting.\n"); }
void dispensing(void) { printf("Item is now dispensing!\n"); }
void transaction_complete(void) { printf("Transaction complete. Please retrieve your item and thanks for shopping with us :)\n"); }
void do_nothing(void) { printf("Don't worry, nothing happened...\n"); }
void malfunction(void) { printf("Something unexpected happened... reporting this to hq.\n"); }

// Transistions struct
typedef struct {
    States cur_state;
    States next_state;
    Inputs input;
    void (*p)(void);       // Pointer to an action function
} transition;

// FSM struct
typedef struct {
    States cur_state;
    transition all_transitions[9];      // Array of all possible transitions that could occur
    int valid_transitions;
} FSM;

// Initialize the FSM
void fsm_init(FSM *fsm, States start_state) 
{
fsm->cur_state = start_state;
}

// Run the FSM with a new input
void fsm_run(FSM *fsm, Inputs input)
{
    // Match the cur_state and input combination with one of the transitions
    // The transition then dictates the action and the next_state
    for (int i = 0; i < fsm->valid_transitions; i++) {
        if (fsm->cur_state == fsm->all_transitions[i].cur_state && input == fsm->all_transitions[i].input) {
            fsm->all_transitions[i].p();
            fsm->cur_state = fsm->all_transitions[i].next_state;
            return;
        }
    }
    printf("ERROR: Invalid input for current state.\n");
}

// Main function to use this FSM
int main(void) 
{
    // Initialize the FSM and all transition combinations stored in the array
    FSM vending_machine;
    vending_machine.all_transitions[0] = (transition){IDLE, HAS_MONEY, COIN_INSERTED, ready_to_select};
    vending_machine.all_transitions[1] = (transition){IDLE, IDLE, ITEM_SELECTED, no_funds};
    vending_machine.all_transitions[2] = (transition){IDLE, IDLE, ITEM_DISPENSED, malfunction};
    vending_machine.all_transitions[3] = (transition){HAS_MONEY, HAS_MONEY, COIN_INSERTED, ready_to_select};
    vending_machine.all_transitions[4] = (transition){HAS_MONEY, DISPENSING, ITEM_SELECTED, dispensing};
    vending_machine.all_transitions[5] = (transition){HAS_MONEY, HAS_MONEY, ITEM_DISPENSED, malfunction};
    vending_machine.all_transitions[6] = (transition){DISPENSING, DISPENSING, COIN_INSERTED, do_nothing};
    vending_machine.all_transitions[7] = (transition){DISPENSING, DISPENSING, ITEM_SELECTED, do_nothing};
    vending_machine.all_transitions[8] = (transition){DISPENSING, IDLE, ITEM_DISPENSED, transaction_complete};
    
    vending_machine.valid_transitions = 9;

    FSM *fsm = &vending_machine;
    fsm_init(fsm, IDLE);

    // Give it inputs
    fsm_run(fsm, COIN_INSERTED);
    fsm_run(fsm, ITEM_SELECTED);
    fsm_run(fsm, ITEM_DISPENSED);      // One clean cycle
    fsm_run(fsm, ITEM_SELECTED);       // No funds!
    fsm_run(fsm, ITEM_DISPENSED);      // No funds and no selection but item dispensed -> malfunction
    fsm_run(fsm, COIN_INSERTED);
    fsm_run(fsm, ITEM_DISPENSED);      // No selection but item dispensed -> malfunction
    fsm_run(fsm, ITEM_SELECTED);
    fsm_run(fsm, COIN_INSERTED);       // Wasted a coin -> nothing happened
    fsm_run(fsm, ITEM_SELECTED);       // Pushing buttons for no reason -> nothing happened
    fsm_run(fsm, ITEM_DISPENSED);      // Another cycle done
    
}

