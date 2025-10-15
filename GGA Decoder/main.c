#include <stdio.h>
#include "handleSentence.h"  // Include the function header


#define MAX_MESSAGE_LENGTH 256  //  expected message size is usually 86

int main() {
    char sentence[MAX_MESSAGE_LENGTH];

    while (1) {  // Infinite loop to continue scanning
        printf("Enter a message: ");
        if (fgets(sentence, MAX_MESSAGE_LENGTH, stdin)) {  // Read a line from input
            // Optionally, remove the newline character if fgets captures it
            sentence[strcspn(sentence, "\n")] = 0;

            // Call handleSentence with the scanned message
            handleSentence(sentence);
        }
    }
    return 0;
}
