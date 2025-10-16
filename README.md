<h1 align="center" style="color:#4CAF50;">
 📡 NMEA GPGGA Sentence Handler
</h1>

<p align="center">
  <em>Processes GPS GPGGA sentences and extracts key navigation data</em>
</p>

## 🌟 Overview

This program processes an **NMEA GPGGA sentence** (Global Positioning System Fix Data) from GNSS (Global Navigation Satellite System) data and extracts relevant fields such as:

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
``` 
### Example NMEA Sentence

$GPGGA,202530.00,5109.0262,N,11401.8407,W,5,40,0.5,1097.36,M,-17.00,M,18,TSTR*61


### About NMEA Sentences
The **NMEA (National Marine Electronics Association)** defines communication standards for marine electronic devices, including GNSS (Global Navigation Satellite System) receivers.  
Each GNSS receiver outputs standard messages known as **sentences** that begin with a `$` symbol, followed by an identifier and comma-separated data fields.

Each sentence:
- Starts with `$`  
- Contains comma-separated fields  
- Ends with a two-digit checksum preceded by `*`  
- Is terminated with a carriage return and line feed (`[CR][LF]`)

Example (showing time, position, and fix data):
$GPGGA,134658.00,5106.9792,N,11402.3003,W,2,09,1.0,1048.47,M,-16.27,M,08,AAAA*60

These sentences are output the same way across GNSS receivers, ensuring interoperability and standardized data processing.

---

### 🧾 Field Breakdown

| **Field** | **Structure** | **Description** | **Symbol** | **Example** |
|:------------:|:--------------|:----------------|:-----------|:------------|
| 1 | `$GPGGA` | Log header |  | `$GPGGA` |
| 2 | `utc` | UTC time of position (hhmmss.ss) | `hhmmss.ss` | `202134.00` |
| 3 | `lat` | Latitude (DDmm.mm) | `llll.ll` | `5106.9847` |
| 4 | `lat dir` | Latitude direction (N = North, S = South) | `a` | `N` |
| 5 | `lon` | Longitude (DDDmm.mm) | `yyyyy.yy` | `11402.2986` |
| 6 | `lon dir` | Longitude direction (E = East, W = West) | `a` | `W` |
| 7 | `quality` | GPS quality indicator (see table below) | `x` | `1` |
| 8 | `# sats` | Number of satellites used | `xx` | `10` |
| 9 | `hdop` | Horizontal dilution of precision | `x.x` | `1.0` |
| 10 | `alt` | Altitude above mean sea level | `x.x` | `1062.22` |
| 11 | `a-units` | Units of antenna altitude | `M` | `M` |
| 12 | `undulation` | Geoidal separation (geoid–ellipsoid diff.) | `x.x` | `-16.271` |
| 13 | `u-units` | Units of undulation | `M` | `M` |
| 14 | `age` | Age of differential data (s) | `xx` | *(empty when no differential data is present)* |
| 15 | `stn ID` | Differential base station ID | `xxxx` | *(empty when no differential data is present)* |
| 16 | `*xx` | Checksum | `*hh` | `*48` |
| 17 | `[CR][LF]` | Sentence terminator |  | `[CR][LF]` |

---

### 🛰️ GPS Quality Indicators

| **Indicator** | **Description** |
|:--------------:|:----------------|
| 0 | Fix not available or invalid |
| 1 | Single point fix |
| 2 | Pseudorange differential |
| 4 | RTK fixed ambiguity solution |
| 5 | RTK floating ambiguity solution |
| 6 | Dead reckoning mode |
| 7 | Manual input (fixed position) |
| 8 | Simulator mode |
| 9 | WAAS (SBAS) |

---

For more detailed information about NMEA sentence formats, see the official NMEA specifications or manufacturer documentation.
