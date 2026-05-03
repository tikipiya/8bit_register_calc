#include <stdio.h>
#include <string.h>
#include <stdint.h>
// 構造体の定義
typedef struct {
    uint8_t regA; // 8bit register A
    uint8_t regB; // 8bit register B
    uint8_t regC; // Carry flag
} CPU;

void display_cpu_state(CPU, cpu);
void print_binary(uint8_t n);
int main() {
    CPU myCpu = {0, 0, 0}; // cpuの初期化
    char command[16];
    char target[16];
    int value;
    printf("---8-bit Register Simulator ---\n");
    printf("Commands: MOV A [val], MOV B [val], ADD A B, EXIT\n\n");
    while (1) {
        display_cpu_state(myCpu); // now state
        printf("\n>>");
        scanf("%s", command);
        if (strcmp(command, "EXIT") == 0) break; // EXIT: program end
        if (strcmp(command, "MOV") == 0) {
            scanf("%s %d", target, &value);
            if (strcmp(target, "A") == 0) {
                myCpu.regA = (uint8_t)value;
            } else if (strcmp(target, "B") == 0) {
                myCpu.regB = (uint8_t)value;
            }
        }
        else if (strcmp(command, "ADD") == 0) {
            scanf("%s %s", target, target);
            if ((int)myCpu.regA + (int)myCpu.regB > 255) {
                myCpu.flagC = 1;
            } else {
                myCpu.flagC = 0;
            }
            myCpu.regA = myCpu.regA + myCpu.regB;
        }
        printf("\033[H\033[J"); // 画面リフレッシュ (エスケープシーケンス)
    }
    return 0;
}
void display_cpu_state(CPU cpu) {
    printf("REGISTER A: \033[1;32m%3d\033[0m [", cpu.regA); // 緑色で数値を表示
    print_binary(cpu.regA);
    printf("]\n");

    printf("REGISTER B: \033[1;36m%3d\033[0m [", cpu.regB); // 水色で数値を表示
    print_binary(cpu.regB);
    printf("]\n");

    printf("CARRY FLAG: %s\n", cpu.flagC ? "\033[1;31m1 (ON)\033[0m" : "0 (OFF)");
}
void print_binary(uint8_t n) {
    for (int i = 7; i>=0; i--) {
        int bit = (n >> i) & 1;
        if (bit == 1) {
            printf("\033[1;33m1\033[0m");
        } else {
            printf("0");
        }
        if (i == 4) printf(" ");
    }
}