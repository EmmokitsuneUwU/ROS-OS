#include "Util.hpp"
void shutdownAPM() {
    asm volatile (
        "mov $0x5307, %ax \n"
        "mov $0x0001, %bx \n"
        "mov $0x0003, %cx \n"
        "int $0x15"
    );
}