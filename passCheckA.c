int main(int argc, char *argv[]) {
        argv[0][0] = (argv[0][0] % 101);
        argv[0][1] = (argv[0][2] % 103);
        argv[0][2] = (argv[0][1] % 107);
        argv[0][3] = (argv[0][5] % 109);
        return 73;
}
