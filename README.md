<h1 align="center" style="color:#4CAF50;">
 📡 NMEA GPGGA Sentence Handler
</h1>

<p align="center">
  <em>Processes GPS GPGGA sentences and extracts key navigation data</em>
</p>

## 🌟 Overview

This program processes an **NMEA GPGGA sentence** (Global Positioning System Fix Data) and extracts relevant fields such as:

- UTC time  
- Latitude & longitude  
- GPS quality  
- Altitude  
- Other related data  

It performs **error checking** to ensure the integrity of the data and **converts latitude and longitude** from the `ddmm.mmmm` format to **decimal degrees**.

---

## 🔧 Features

- 🛰️ Extracts and processes key information from a GPGGA sentence  
- 📐 Converts latitude and longitude from `ddmm.mmmm` to decimal degrees  
- ✅ Verifies the validity of extracted data (latitude, longitude, time)  
- 🔢 Handles up to 15 fields in a typical GPGGA sentence  
- ⚠️ Provides detailed error messages if any fields are invalid  
- 🖨️ Prints the extracted information in a readable format  

---

## 🛠️ Requirements

- C Compiler (e.g., GCC) — project built in **Code::Blocks**  
- Standard C libraries:  
  - `stdio.h`  
  - `string.h`  
  - `stdlib.h`  
  - `math.h`  
  - `stdbool.h`  

---

## 🧠 Functionality

### 🛰️ Extracts NMEA GPGGA sentence
The program processes a sample GPGGA sentence, typically received from a GPS module, and splits it into individual fields.

### ⚠️ Error Checking
- Ensures the sentence has **exactly 15 fields**  
- Checks validity of **time, latitude, longitude**  
- Ensures all values are within acceptable ranges  

### 📐 Latitude and Longitude Conversion
- Converts latitude and longitude from **ddmm.mmmm** to **decimal degrees**  
- Makes values easier to use in navigation or mapping applications  

### 🖨️ Prints Data
- Displays all extracted and converted information in a **clear and readable format**  

---

## 🧪 Example Usage

```c
#include <stdio.h>
#include "handleSentence.h"

#define MAX_MESSAGE_LENGTH 256

int main() {
    char sentence[MAX_MESSAGE_LENGTH];

    while (1) {
        printf("Enter a GPGGA sentence: ");
        if (fgets(sentence, MAX_MESSAGE_LENGTH, stdin)) {
            // Remove newline if captured
            sentence[strcspn(sentence, "\n")] = 0;

            // Call handleSentence to parse and display data
            if (!handleSentence(sentence)) {
                printf("Failed to parse GPGGA sentence.\n");
            }
        }
    }

    return 0;
}
