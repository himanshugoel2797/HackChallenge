int main(int argc, char *argv[]) {
        argv[0][0] = (argv[0][0] % argc);
        argv[0][1] = (argv[0][2] % (argv[0][0] + 1));
        argv[0][2] = ~(argv[0][1]-- <= argv[0][0]--);
        argv[0][3] = (~argv[0][2]);
        return argc * ~argv[0][1];
}
