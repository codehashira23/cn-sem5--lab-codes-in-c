#include <stdio.h>
#include <string.h>

void xor_bits(char *result, const char *a, const char *b, int len) {
    // XOR two equal-length binary strings a and b, store in result
    for (int i = 0; i < len; i++) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    result[len] = '\0';
}

void mod2_division(char *dividend, const char *divisor, int show_steps, char *remainder) {
    int n = strlen(divisor);
    int len = strlen(dividend);
    int limit = len - n + 1;
    char window[128], result[128];

    if (show_steps) {
        printf("Initial padded dividend: %s (divisor length = %d)\n", dividend, n);
    }

    for (int i = 0; i < limit; i++) {
        strncpy(window, dividend + i, n);
        window[n] = '\0';

        if (show_steps) {
            printf("Position %d: window = %s\n", i, window);
        }

        if (window[0] == '1') {
            if (show_steps) {
                printf("  -> Leading bit = 1, XOR with divisor %s\n", divisor);
            }
            xor_bits(result, window, divisor, n);
            for (int j = 0; j < n; j++) {
                dividend[i + j] = result[j];
            }
            if (show_steps) {
                printf("  -> Result after XOR: %s\n", result);
                printf("  -> New dividend: %s\n", dividend);
            }
        } else {
            if (show_steps) {
                printf("  -> Leading bit = 0, skip XOR\n");
            }
        }
    }

    // Extract last n-1 bits as remainder
    strncpy(remainder, dividend + len - (n - 1), n - 1);
    remainder[n - 1] = '\0';
    if (show_steps) {
        printf("Final remainder (last %d bits): %s\n", n - 1, remainder);
    }
}

void compute_crc(const char *message, const char *divisor) {
    printf("\n============================================================\n");
    printf("Message: %s\n", message);
    printf("Divisor: %s (degree = %lu)\n", divisor, strlen(divisor) - 1);

    int mlen = strlen(message);
    int dlen = strlen(divisor);
    int total_len = mlen + dlen - 1;

    char padded[256];
    char remainder[256];

    // Step 1: Append zeros
    strcpy(padded, message);
    for (int i = 0; i < dlen - 1; i++) strcat(padded, "0");
    printf("\nStep 1: Append %d zeros → %s\n", dlen - 1, padded);

    mod2_division(padded, divisor, 1, remainder);

    // Step 2: Create transmitted message
    char transmitted[256];
    strcpy(transmitted, message);
    strcat(transmitted, remainder);
    printf("\nStep 2: CRC remainder = %s\n", remainder);
    printf("Transmitted message (Message + CRC) = %s\n", transmitted);

    // Verification
    char verify_dividend[256];
    strcpy(verify_dividend, transmitted);
    char verify_rem[256];
    mod2_division(verify_dividend, divisor, 0, verify_rem);

    printf("Verification remainder: %s (should be all zeros)\n", verify_rem);
    printf("============================================================\n");
}

int main() {
    // Problem 1
    compute_crc("1010001101", "110101");

    // Uncomment to run other problems:
    // compute_crc("11001001", "1001");
    // compute_crc("100111001", "1011");
    // compute_crc("01011011", "1011");

    return 0;
}
