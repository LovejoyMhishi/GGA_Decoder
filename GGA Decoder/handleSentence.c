#include <stdio.h>
#include "handleSentence.h"  // Include the header file
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

bool handleSentence(char* sentence) {
    const int MAX_FIELDS = 15;  // Maximum expected fields in GGA sentence
    char* fields[MAX_FIELDS];   // Array to store the sentence fields
    char* token;  // Pointer for storing each extracted field from the NMEA sentence
    int index = 0; // Counter to track the number of fields extracted
    int len = strlen(sentence); // Get the length of the NMEA sentence
    int lat_count = 0; // Variable to track the number of characters before the decimal point in the latitude value.
    int lon_count = 0; // Variable to track the number of characters before the decimal point in the longitude value.
    int time_count = 0;// Variable to track the number of characters before the decimal point in the Time value.

    // Initialize all fields as empty strings
    for (int i = 0; i < MAX_FIELDS; i++){
        fields[i] = NULL;
    }

    // Iterate over the sentence and manually split by commas, considering empty fields
    token = sentence;// Pointer to traverse and extract fields from the NMEA sentence
    while ( token < sentence + len) {
        // Check for the next comma or end of sentence
        char* comma_pos = strchr(token, ',');
        if (comma_pos == NULL) {
            comma_pos = sentence + len;
        }

        // Calculate the length of the field
        int field_len = comma_pos - token;

        // Allocate space for the field and copy it
        char* field = (char*)malloc((field_len + 1) * sizeof(char));
        strncpy(field, token, field_len); // Copy the field into allocated memory
        field[field_len] = '\0'; // Null-terminate the field

        // Store the field
        fields[index] = field;
        index++;

        // Move the token pointer to the next field (after the comma)
        token = comma_pos + 1;

        // Stop when we reach the maximum number of fields or end of sentence
        if (index >= MAX_FIELDS || *token == '\0') {
            break;
        }
    }

    // Extract required values
    char* utc_time = fields[1];            // UTC Time
    char* latitude = fields[2];            // Latitude  ddmm.mmmm
    char* lat_dir = fields[3];             // Latitude Direction (N=north or S=south)
    char* longitude = fields[4];           // Longitudedddmm.mmmm
    char* lon_dir = fields[5];             // Longitude Direction (E=east or W=west)
    char* GPS_quality = fields[6];         // GPS Fix Quality
    char* num_satellites = fields[7];      // Number of Satellites in use
    char* horizontal_dilution = fields[8]; // Horizontal Dilution of Precision (HDOP)
    char* altitude = fields[9];            // Altitude
    char* alt_unit = fields[10];           // Altitude Units (meters)
    char* geoidal_separation = fields[11]; // Geoidal Separation (height of the geoid above/below the WGS84 ellipsoid)
    char* geo_unit = fields[12];           // Geoidal Separation Units (meters)
    char* age_of_differential_data = fields[13]; // Age of Differential GPS data (seconds)
    char* diff_ref_station_id = fields[14]; // Differential Reference Station ID


    /*****************************************************
    ***** ERROR HANDLING FOR AN INVALID GGA SENTENCE *****
    ******************************************************/



     // Check if there are less than 15 fields
    if (index < 15) {
        printf("Error: Invalid GGA Length\n");

        return false;  // Exit the function if there are less than 15 fields
    }

     //Count the number of characters before the decimal point in longitude
    for (int i = 0; utc_time[i] != '.' && utc_time[i] != '\0'; i++) {
        time_count++;
    }

     // Count the number of characters before the decimal point in latitude
    for (int i = 0; latitude[i] != '.' && latitude[i] != '\0'; i++) {
        lat_count++;;
    }

     // Count the number of characters before the decimal point in longitude
    for (int i = 0; longitude[i] != '.' && longitude[i] != '\0'; i++) {
        lon_count++;
    }

     // Error Checking For Time
    if (utc_time == NULL || time_count < 6 || *utc_time == '\0')  {
        printf("Invalid time data.\n");
        return false;  // Exit if latitude data is invalid
    }

     // Error Checking For Lattitude fixed field length
    if (latitude == NULL || lat_count < 4 || *lat_dir == '\0')  {
        printf("Invalid latitude data.\n");
        return false;  // Exit if latitude data is invalid
    }

    // Convert latitude string from ddmm.mmmm to decimal degrees
    double latitude_check = atof(latitude); // Convert string to double
    int lat_degrees = (int)(latitude_check / 100); // Extract degrees
    double lat_minutes = fabs(latitude_check - lat_degrees * 100); // Extract minutes
    double decimal_latitude = lat_degrees + (lat_minutes / 60.0); // Convert to decimal degrees

    // Check if latitude is valid
    if (decimal_latitude < -90.0 || decimal_latitude > 90.0|| (*lat_dir != 'N' && *lat_dir != 'S')) {
        printf("Invalid latitude: %d%c%.6f %s\n", lat_degrees, 248, lat_minutes, lat_dir);
        return false;
    }

    // Error Checking for Longitude fixed field length
    if (longitude == NULL || lon_count< 5|| *lon_dir == '\0') {
    printf("Invalid longitude data.\n");
    return false;  // Exit if longitude data is invalid
    }

    // Convert longitude string from dddmm.mmmm to decimal degrees
    double longitude_check = atof(longitude); // Convert string to double
    int lon_degrees = (int)(longitude_check / 100); // Extract degrees
    double lon_minutes = fabs(longitude_check - lon_degrees * 100); // Extract minutes
    double decimal_longitude = lon_degrees + (lon_minutes / 60.0); // Convert to decimal degrees

    // Check if longitude is valid (must be between -180.0 and 180.0)
    if (decimal_longitude < -180.0 || decimal_longitude > 180.0|| (*lon_dir != 'E' && *lon_dir != 'W')) {
    printf("Invalid longitude: %d%c%.6f %s\n", lon_degrees,248, lon_minutes, lon_dir);
    return false;
    }

    // Convert char* to int using atoi()
    int GPS_quality_int = atoi(GPS_quality);

    // Error Checking For GPS Quality Indicator
    if (GPS_quality_int == 0 || GPS_quality_int > 8) {
    printf("Invalid GPS quality Indicator.\n");
    return false;  // Exit if GPS quality indicator is invalid
    }

    // Print extracted values
    printf("UTC Time: %s\n", utc_time);
    printf("Latitude: %d%c%.6f %s\n", lat_degrees, 248, lat_minutes, lat_dir);
    printf("Longitude: %d%c%.6f %s\n", lon_degrees,248, lon_minutes, lon_dir);
    printf("Fix Quality: %s\n", GPS_quality);
    printf("Satellites Used: %s\n", num_satellites);
    printf("Horizontal Dilution of Precision (HDOP): %s\n", horizontal_dilution);
    printf("Altitude: %s %s\n", altitude, alt_unit);
    printf("Geoidal Separation: %s %s\n", geoidal_separation, geo_unit);
    printf("Age of Differential GPS Data: %s seconds\n", age_of_differential_data);
    printf("Differential Reference Station ID: %s\n\n", diff_ref_station_id);

    return true;
}
