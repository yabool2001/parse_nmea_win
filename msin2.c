#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to calculate the checksum of an NMEA sentence
char calculateChecksum(const char *sentence) {
    char checksum = 0;
    for (int i = 1; i < strlen(sentence); i++) {
        checksum ^= sentence[i];
    }
    return checksum;
}

// Function to convert NMEA coordinates to decimal degrees
double nmeaToDecimal(const char *coord, char direction) {
    double degrees, minutes;
    sscanf(coord, "%lf", &degrees);
    minutes = degrees / 100;
    degrees = (int)minutes;
    minutes = minutes - degrees;
    return degrees + minutes / 0.6 * ((direction == 'S' || direction == 'W') ? -1 : 1);
}

int main() {
    char sentence[] = "$GNGLL,5216.7071,N,02048.5512,E,210042.000,A,A*4E";
    char expectedChecksum = 0x4E; // Expected checksum from the example

    // Verify the checksum
    char calculatedChecksum = calculateChecksum(sentence);
    if (calculatedChecksum != expectedChecksum) {
        printf("Checksum verification failed.\n");
        return 1;
    }

    // Split the sentence into tokens using ',' as a delimiter
    char *token = strtok(sentence, ",");
    int fieldCount = 0;
    char *latitude, *longitude;
    char latDirection, lonDirection;

    while (token != NULL) {
        if (fieldCount == 1) {
            latitude = token;
        } else if (fieldCount == 3) {
            longitude = token;
        } else if (fieldCount == 2) {
            latDirection = token[0];
        } else if (fieldCount == 4) {
            lonDirection = token[0];
        }
        token = strtok(NULL, ",");
        fieldCount++;
    }

    // Convert latitude and longitude to decimal degrees
    double latDecimal = nmeaToDecimal(latitude, latDirection);
    double lonDecimal = nmeaToDecimal(longitude, lonDirection);

    printf("Latitude: %.6lf degrees\n", latDecimal);
    printf("Longitude: %.6lf degrees\n", lonDecimal);

    return 0;
}
