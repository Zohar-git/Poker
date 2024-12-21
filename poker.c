#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HAND_SIZE 5

typedef struct {
    char *hand;
} hand;

int hand_amount = 0;
hand *Hands = NULL;
int **Hands_order = NULL;

char **FIVE_KIND = NULL;
char **FOUR_KIND = NULL;
char **FULL_HOUSE = NULL;
char **THREE_KIND = NULL;
char **TWO_PAIR = NULL;
char **ONE_PAIR = NULL;
char **HIGH_CARD = NULL;

int five_kind = 0, four_kind = 0, three_kind = 0, full_house_kind = 0, two_pair_kind = 0, pair_kind = 0, high_card_kind = 0;

int add_hands() {
    hand_amount++;
    Hands = (hand *)realloc(Hands, hand_amount * sizeof(hand));
    Hands[hand_amount - 1].hand = malloc(sizeof(char) * (HAND_SIZE + 1));
    printf("Enter the hand you want to play (Contains 5 characters):\n");
    scanf("%s", Hands[hand_amount - 1].hand);
    if (strcmp(Hands[hand_amount - 1].hand, "0") == 0) {
        return 1;
    }
    return 0;
}

void print_hands() {
    printf("These are the Hands you entered into the system:\n");
    for (int i = 0; i < hand_amount; i++) {
        printf("%s\n", Hands[i].hand);
    }
}

// Create a function to count the frequency of each card in the hand
void Hand_order_inarray() {
    Hands_order = realloc(Hands_order, hand_amount * sizeof(int *));
    for (int i = 0; i < hand_amount; i++) {
        Hands_order[i] = malloc(13 * sizeof(int));  // 13 because there are 13 types of cards (2 through A)
        memset(Hands_order[i], 0, 13 * sizeof(int)); // Initialize all elements to 0

        for (int b = 0; b < HAND_SIZE; b++) {
            char card = Hands[i].hand[b];
            int index = -1;

            // Map card to index (0 to 12 for A, 2, 3, ..., K)
            if (card == 'A') index = 0;
            else if (card == '2') index = 1;
            else if (card == '3') index = 2;
            else if (card == '4') index = 3;
            else if (card == '5') index = 4;
            else if (card == '6') index = 5;
            else if (card == '7') index = 6;
            else if (card == '8') index = 7;
            else if (card == '9') index = 8;
            else if (card == 'T') index = 9;  // Ten
            else if (card == 'J') index = 10; // Jack
            else if (card == 'Q') index = 11; // Queen
            else if (card == 'K') index = 12; // King

            if (index >= 0 && index < 13)
                Hands_order[i][index]++;
        }
    }
}

// Function to sort and classify hands
void sort_hands() {
    for (int c = 0; c < hand_amount; c++) {
        int counts[13] = {0}; // to store the count of each rank (A, 2, 3, ... K)
        int pairs = 0, threes = 0, fours = 0;

        // Count frequencies of each card rank
        for (int i = 0; i < 13; i++) {
            counts[i] = Hands_order[c][i];
            if (counts[i] == 2) pairs++;
            else if (counts[i] == 3) threes++;
            else if (counts[i] == 4) fours++;
            else if (counts[i] == 5) { 
                // Five of a kind
                five_kind++;
                FIVE_KIND = realloc(FIVE_KIND, sizeof(char *) * five_kind);
                FIVE_KIND[five_kind - 1] = malloc(HAND_SIZE + 1);
                strcpy(FIVE_KIND[five_kind - 1], Hands[c].hand);
                break; // No need to check other conditions once it's a five of a kind
            }
        }

        // Classify the hand based on the counts
        if (fours == 1) {
            // Four of a kind
            four_kind++;
            FOUR_KIND = realloc(FOUR_KIND, sizeof(char *) * four_kind);
            FOUR_KIND[four_kind - 1] = malloc(HAND_SIZE + 1);
            strcpy(FOUR_KIND[four_kind - 1], Hands[c].hand);
        }
        else if (threes == 1 && pairs == 1) {
            // Full House
            full_house_kind++;
            FULL_HOUSE = realloc(FULL_HOUSE, sizeof(char *) * full_house_kind);
            FULL_HOUSE[full_house_kind - 1] = malloc(HAND_SIZE + 1);
            strcpy(FULL_HOUSE[full_house_kind - 1], Hands[c].hand);
        }
        else if (pairs == 2) {
            // Two pair
            two_pair_kind++;
            TWO_PAIR = realloc(TWO_PAIR, sizeof(char *) * two_pair_kind);
            TWO_PAIR[two_pair_kind - 1] = malloc(HAND_SIZE + 1);
            strcpy(TWO_PAIR[two_pair_kind - 1], Hands[c].hand);
        }
        else if (pairs == 1) {
            // One pair
            pair_kind++;
            ONE_PAIR = realloc(ONE_PAIR, sizeof(char *) * pair_kind);
            ONE_PAIR[pair_kind - 1] = malloc(HAND_SIZE + 1);
            strcpy(ONE_PAIR[pair_kind - 1], Hands[c].hand);
        }
        else if (threes == 1) {
            // Three of a kind
            three_kind++;
            THREE_KIND = realloc(THREE_KIND, sizeof(char *) * three_kind);
            THREE_KIND[three_kind - 1] = malloc(HAND_SIZE + 1);
            strcpy(THREE_KIND[three_kind - 1], Hands[c].hand);
        }

        // **High Card** condition: No pairs, no threes, no four of a kind, etc.
        if (pair_kind == 0 && three_kind == 0 && five_kind == 0 && four_kind == 0 && full_house_kind == 0 && two_pair_kind == 0 && three_kind == 0) {
            high_card_kind++;
            HIGH_CARD = realloc(HIGH_CARD, sizeof(char *) * high_card_kind);
            HIGH_CARD[high_card_kind - 1] = malloc(HAND_SIZE + 1);
            strcpy(HIGH_CARD[high_card_kind - 1], Hands[c].hand);
        }
    }
}

// Function to print sorted hands
void print_sorted_hands() {
    if (five_kind != 0) {
        printf("FIVE KIND: \n");
        for (int i = 0; i < five_kind; i++) {
            printf("%s\n", FIVE_KIND[i]);
        }
    }
    if (four_kind != 0) {
        printf("FOUR KIND:\n");
        for (int i = 0; i < four_kind; i++) {
            printf("%s\n", FOUR_KIND[i]);
        }
    }
    if (full_house_kind != 0) {
        printf("FULL HOUSE:\n");
        for (int i = 0; i < full_house_kind; i++) {
            printf("%s\n", FULL_HOUSE[i]);
        }
    }
    if (three_kind != 0) {
        printf("THREE KIND:\n");
        for (int i = 0; i < three_kind; i++) {
            printf("%s\n", THREE_KIND[i]);
        }
    }
    if (two_pair_kind != 0) {
        printf("TWO PAIR:\n");
        for (int i = 0; i < two_pair_kind; i++) {
            printf("%s\n", TWO_PAIR[i]);
        }
    }
    if (pair_kind != 0) {
        printf("ONE PAIR:\n");
        for (int i = 0; i < pair_kind; i++) {
            printf("%s\n", ONE_PAIR[i]);
        }
    }
    if (high_card_kind != 0) {
        printf("HIGH CARD:\n");
        for (int i = 0; i < high_card_kind; i++) {
            printf("%s\n", HIGH_CARD[i]);
        }
    }
}

int main() {
    int y = 0;
    printf("Welcome to Camel Cards!\n");
    printf("When you want to stop adding hands, type '0'.\n");

    while (1) {
        y = add_hands();
        if (y == 1) {
            break;
        }
    }

    print_hands();
    Hand_order_inarray();
    sort_hands();
    print_sorted_hands();

    return 0;
}
