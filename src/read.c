#include "../kek.h"

df read_df(char *path, u64 nrow, u64 ncol, char *colspec) {
    FILE *csv = fopen(path, "r");
    vec colnames = {STRING, ncol, malloc(ncol * sizeof colnames.x)};
    vec *var = malloc(ncol * sizeof *var);
    int *coltypes = malloc(strlen(colspec) * sizeof *coltypes);
    for (u64 i = 0; i < strlen(colspec); i++) {
        switch (colspec[i]) {
        case 'i':
            coltypes[i] = INTEGER;
            break;
        case 'u':
            coltypes[i] = UNSIGNED;
            break;
        case 'f':
            coltypes[i] = FLOAT;
            break;
        case 's':
            coltypes[i] = STRING;
            break;
        }
    }
    for (u64 j = 0; j < ncol; j++) {
        var[j] = (vec) {coltypes[j], nrow, malloc(nrow * sizeof var[j].x)};
        s64(colnames)[j] = malloc(64);
        u64 signal = fscanf(csv, "\n%[^,;\t\n],", s64(colnames)[j]);
        if (signal != 1) exit(1);
    }
    for (u64 i = 0; i < nrow; i++) {
        for (u64 j = 0; j < ncol; j++) {
            u64 signal;
            switch(var[j].type) {
            case INTEGER:
                signal = fscanf(csv, "%lli,", &i64(var[j])[i]);
                break;
            case UNSIGNED:
                signal = fscanf(csv, "%llu,", &u64(var[j])[i]);
                break;
            case FLOAT:
                signal = fscanf(csv, "%lf,", &f64(var[j])[i]);
                break;
            case STRING:
                s64(var[j])[i] = malloc(64 * sizeof s64(var[j])[i]);
                signal = fscanf(csv, "\n%[^,;\t\n],", s64(var[j])[i]);
                break;
            }
            if (signal != 1) exit(1);
        }
    }
    fclose(csv);
    return (df) {nrow, ncol, colnames, var};
}
