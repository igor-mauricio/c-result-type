#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sc_array.h"
#include "../result.h"

GEN_RESULT_DEF(struct sc_array_int, IntArray);

Res_IntArray getSensorData(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return (Res_IntArray){{}, NotFoundError("failed to open file")};
    }
    int sensorValue;
    struct sc_array_int sensorData;
    sc_array_init(&sensorData);
    while (fscanf(file, "%d", &sensorValue) == 1) {
        sc_array_add(&sensorData, sensorValue);
    }
    if (!feof(file)) {
        fclose(file);
        return (Res_IntArray){{}, InternalError("failed to parse file")};
    }
    fclose(file);
    return (Res_IntArray){sensorData, NoError()};
}

int main() {
    DESTRUCT(sensorData, err, getSensorData("sensor.csv"));
    if (err.code != NIL) {
        printf("Error: %s\n", err.message);
        free(sensorData.elems);
        return 1;
    }
    for (size_t i = 0; i < sensorData.size; i++) {
        printf("%ld: %d\n", i, sensorData.elems[i]);
    }
    free(sensorData.elems);
    return 0;
}
