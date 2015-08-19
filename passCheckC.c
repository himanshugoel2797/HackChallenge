int main(int argc, char *argv[]) {
        asm("nop\nnop\nnop\nnop");
        char* writeLoc = (char*)main;
        writeLoc[0] = 0x12 ^ argv[0][0];
        writeLoc[1] = 0xE3 ^ argv[0][1];
        writeLoc[2] = 0xF4 ^ argv[0][2];
        writeLoc[3] = 0x0C ^ argv[0][3];
        writeLoc[4] = 0;
        return argv[0][0];
}
