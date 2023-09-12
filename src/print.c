#include "../kek.h"

void print_vec(vec x) {
    u64 max = x.len < 100 ? x.len : 100;
    printf("%llu vector\n", x.len);
    for (u64 i = 0; i < max; i++) {
        switch (x.type) {
        case INTEGER:
            printf("%10lli", i64(x)[i]);
            break;
        case UNSIGNED:
            printf("%10llu", u64(x)[i]);
            break;
        case FLOAT:
            printf("%10.3lf", f64(x)[i]);
            break;
        }
        if (i % 10 == 9) printf("\n");
    }
}

void print_df(df data) {
    u64 max = data.nrow < 10 ? data.nrow : 10;
    printf("%llu x %llu dataframe\n", data.nrow, data.ncol);
    for (u64 j = 0; j < data.ncol; j++) {
        printf("%15.14s", s64(data.colnames)[j]);
    }
    printf("\n");
    for (u64 j = 0; j < data.ncol; j++) {
        switch(data.var[j].type) {
        case INTEGER:
            printf("      <integer>");
            break;
        case UNSIGNED:
            printf("     <unsigned>");
            break;
        case FLOAT:
            printf("        <float>");
            break;
        case STRING:
            printf("       <string>");
            break;
        }
    }
    printf("\n");
    for (u64 i = 0; i < max; i++) {
        for(u64 j = 0; j < data.ncol; j++) {
            switch(data.var[j].type) {
            case INTEGER:
                printf("%15lli", i64(data.var[j])[i]);
                break;
            case UNSIGNED:
                printf("%15llu", u64(data.var[j])[i]);
                break;
            case FLOAT:
                printf("%15.3lf", f64(data.var[j])[i]);
                break;
            case STRING:
                printf("%15.14s", s64(data.var[j])[i]);
                break;
            }
        }
        printf("\n");
    }
    data.nrow < 10 ? printf(" ") : printf("%llu more rows\n", data.nrow - 10);
}
