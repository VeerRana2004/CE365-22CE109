#include <stdio.h>
#include <string.h>

#define MAX_STATES 100
#define MAX_SYMBOLS 100

typedef struct {
    int transitions[MAX_STATES][MAX_SYMBOLS];
    int num_states;
    int num_symbols;
    int start_state;
    int accept_states[MAX_STATES];
    int num_accept_states;
} FiniteAutomata;

int is_accept_state(FiniteAutomata *fa, int state) {
    for (int i = 0; i < fa->num_accept_states; i++) {
        if (fa->accept_states[i] == state) {
            return 1;
        }
    }
    return 0;
}

int validate_string(FiniteAutomata *fa, char *input) {
    int current_state = fa->start_state;
    for (int i = 0; i < strlen(input); i++) {
        int symbol = input[i] - 'a';
        current_state = fa->transitions[current_state][symbol];
    }
    return is_accept_state(fa, current_state);
}

int main() {
    FiniteAutomata fa;
    int num_transitions;
    char input[MAX_SYMBOLS];

    printf("Enter number of states: ");
    scanf("%d", &fa.num_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &fa.num_symbols);

    printf("Enter start state: ");
    scanf("%d", &fa.start_state);

    printf("Enter number of accepting states: ");
    scanf("%d", &fa.num_accept_states);
    printf("Enter accepting states: ");
    for (int i = 0; i < fa.num_accept_states; i++) {
        scanf("%d", &fa.accept_states[i]);
    }

    printf("Enter number of transitions: ");
    scanf("%d", &num_transitions);
    printf("Enter transitions (format: state symbol next_state):\n");
    for (int i = 0; i < num_transitions; i++) {
        int state, next_state;
        char symbol;
        scanf("%d %c %d", &state, &symbol, &next_state);
        fa.transitions[state][symbol - 'a'] = next_state;
    }

    printf("Enter input string: ");
    scanf("%s", input);

    if (validate_string(&fa, input)) {
        printf("Valid String\n");
    } else {
        printf("Invalid String\n");
    }

    return 0;
}

