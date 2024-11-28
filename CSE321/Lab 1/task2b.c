#include <stdio.h>

int main() {
    FILE *in, *out;
    char input_file[] = "input.txt";
    char output_file[] = "output.txt";
    char char1, char2 = ' ';

    in = fopen(input_file, "r");
    out = fopen(output_file, "w");

    while ((char1 = fgetc(in)) != EOF) {
        if (char1 == ' ' && char2 == ' ') {
            continue;
        }
        fputc(char1, out);
        char2 = char1;
    }

    fclose(in);
    fclose(out);

    return 0;
}
