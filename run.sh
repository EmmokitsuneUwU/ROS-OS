export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "Src/ASM/boot.asm" -f bin -o "Binaries/boot.bin"
nasm "Src/ASM/kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"
i386-elf-gcc -g -ffreestanding -m32 -g -I./include -c "Src/C/kernel.cpp" -o "Binaries/kernel.o"
i386-elf-gcc -g -ffreestanding -m32 -g -I./include -c "Src/C/keyboardUtils.cpp" -o "Binaries/keyboardUtils.o"
i386-elf-gcc -g -ffreestanding -m32 -g -I./include -c "Src/C/VGA.cpp" -o "Binaries/VGA.o"
i386-elf-gcc -g -ffreestanding -m32 -g -I./include -c "Src/C/Util.cpp" -o "Binaries/Util.o"
i386-elf-gcc -g -ffreestanding -m32 -g -I./include -c "Src/C/Math.cpp" -o "Binaries/Math.o"
i386-elf-gcc -g -ffreestanding -m32 -g -I./include -c "Src/C/Pong.cpp" -o "Binaries/Pong.o"
nasm "Src/ASM/zeroes.asm" -f bin -o "Binaries/zeroes.bin"

i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" "Binaries/keyboardUtils.o" "Binaries/VGA.o" "Binaries/Util.o" "Binaries/Math.o" "Binaries/Pong.o" --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin"  > "Binaries/OS.bin"

qemu-system-i386 -drive format=raw,file="Binaries/OS.bin",index=0,if=floppy -m 128M -cpu pentium2 -vga std

