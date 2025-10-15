NMEA GPGGA Sentence Handler

Overview
This program processes an NMEA GPGGA sentence (Global Positioning System Fix Data) and extracts relevant fields such as UTC time, latitude, longitude, GPS quality, altitude, and other related data. It performs error checking to ensure the integrity of the data and converts latitude and longitude from the ddmm.mmmm format to decimal degrees.

Features
- Extracts and processes key information from a GPGGA sentence.
- Converts latitude and longitude from the ddmm.mmmm format to decimal degrees.
- Verifies the validity of the extracted data (latitude, longitude).
- Handles up to 15 fields in a typical GPGGA sentence.
- Provides detailed error messages if any fields are invalid.
- Prints the extracted information in a readable format.

Requirements
- C Compiler (e.g., GCC), Project was built in CodeBlocks
- Standard C library functions (stdio.h, string.h, stdlib.h, math.h, stdbool.h)

Functionality

 Extracts and processes NMEA GPGGA sentence:
The program processes a sample GPGGA sentence, which is usually received from a GPS module.

Error Checking:
- The program checks if the number of fields in the sentence is valid (must be exactly 15 fields).
- It also checks the validity of time, latitude and longitude and ensures that they are within the acceptable ranges.

Latitude and Longitude Conversion:
- The latitude and longitude values are extracted from the NMEA sentence and converted from the ddmm.mmmm format to decimal degrees for easier use in applications.

 Prints Data:
- It prints the extracted and converted information in a clear and readable format.
