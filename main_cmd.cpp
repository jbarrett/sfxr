#include "main.h"

#include <string.h>
#include <stdlib.h>

/* Arbitrary, cogged from <linux/limits.h>, probably fine <_< */
#define PATH_MAX 4096

int usage() {
    fprintf(stderr, "sfxr2wav - Export sfxr files to wav\nUsage: sfxr inputfile [outputfile]\n");
}

int main(int argc, char*argv[]) {
    if (argc < 2) {
        usage();
        exit(-1);
    }

    char *sfxr_file = argv[1];
    char *wav_file = (char*) malloc(sizeof(char *) * (PATH_MAX + 1));

    if (argc > 2) {
        wav_file = argv[2];
    }
    else {
        snprintf(wav_file, PATH_MAX, "%s.wav", sfxr_file);
    }

    if (!strncmp(wav_file, sfxr_file, PATH_MAX)) {
        fprintf(stderr, "Input and output files are same\n%s -> %s\n", sfxr_file, wav_file);
        usage();
        exit(-1);
    }

    if (LoadSettings(sfxr_file) == false) {
        fprintf(stderr, "Cannot read sfxr file %s\n", sfxr_file);
        usage();
        exit(-1);
    }

    if (ExportWAV(wav_file) == false) {
        fprintf(stderr, "Problem writing wav file %s\n", wav_file);
        usage();
        exit(-1);
    }

    printf("%s -> %s\n", sfxr_file, wav_file);
}

