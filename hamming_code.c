#include <stdio.h>
#include <string.h>

// ---------- Function to calculate parity ----------
int calcParity(int code[], int n, int parityPos) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (i & parityPos) {
            count ^= code[i];
        }
    }
    return count;
}

// ---------- 10a: 8 data bits + 4 parity bits ----------
void solve10a() {
    int data[13]; // 1-based indexing
    int positions[8] = {3,5,6,7,9,10,11,12}; // data bit positions
    int code[13] = {0}; // store codeword (1-based)
    int input[8] = {1,1,0,0,0,1,0,1}; // given data

    // Fill data bits
    for (int i = 0; i < 8; i++) {
        code[positions[i]] = input[i];
    }

    // Calculate parity bits (p1,p2,p4,p8 at positions 1,2,4,8)
    code[1] = calcParity(code, 12, 1);
    code[2] = calcParity(code, 12, 2);
    code[4] = calcParity(code, 12, 4);
    code[8] = calcParity(code, 12, 8);

    printf("\n10a: 12-bit Hamming Codeword:\n");
    for (int i = 1; i <= 12; i++) printf("%d", code[i]);
    printf("\nCheck bits: P1=%d P2=%d P4=%d P8=%d\n", code[1], code[2], code[4], code[8]);
}

// ---------- 10b: 4 data bits + 3 parity bits ----------
void solve10b() {
    int code[8] = {0}; // 1-based indexing
    int dataPos[4] = {3,5,6,7};
    int input[4] = {1,0,1,0}; // given data bits

    for (int i = 0; i < 4; i++) code[dataPos[i]] = input[i];

    code[1] = calcParity(code, 7, 1);
    code[2] = calcParity(code, 7, 2);
    code[4] = calcParity(code, 7, 4);

    printf("\n10b: 7-bit Hamming Codeword:\n");
    for (int i = 1; i <= 7; i++) printf("%d", code[i]);
    printf("\n");
}

// ---------- 10c: Error detection & correction ----------
void solve10c() {
    int code[12] = {0}; // 1-based indexing
    int received[12] = {0};
    char input[] = "10111100101"; // 11-bit received codeword
    int n = strlen(input);

    for (int i = 1; i <= n; i++) {
        received[i] = input[i-1] - '0';
        code[i] = received[i];
    }

    int p1 = calcParity(code, 11, 1);
    int p2 = calcParity(code, 11, 2);
    int p4 = calcParity(code, 11, 4);
    int p8 = calcParity(code, 11, 8);

    int errorPos = p1*1 + p2*2 + p4*4 + p8*8;

    printf("\n10c: Received Codeword: %s\n", input);
    if (errorPos == 0) {
        printf("No error detected.\n");
    } else {
        printf("Error detected at position %d. Correcting...\n", errorPos);
        code[errorPos] ^= 1; // flip bit
    }

    printf("Corrected Codeword: ");
    for (int i = 1; i <= n; i++) printf("%d", code[i]);
    printf("\n");
}

// ---------- main ----------
int main() {
    solve10a();
    solve10b();
    solve10c();
    return 0;
}
