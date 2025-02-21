# 🏛️ Integrated Security System for Museum & Showcase Environments 

## Project Overview
This project is an **Integrated Security System** designed for museum and showcase environments, providing security through **object tagging, proximity detection, and real-time monitoring**. The following repository will be holding the software project components (C Files & Solidworks Models). Future iterations may include automated alerts. The system aims to mitigate **theft, unauthorized access, and display damage**, while also offering valuable data for monitoring and management.

## Features
- **RFID-Based Pedestal Monitoring**
- **Tiered Alert System** with LED Indicators & Alarms
- **Automated Security Responses** (Door Closures, Logs, Alarms)
- **Low-Cost Implementation** using **Arduino Nano Compatible Boards**
- **Integration with Museum Databases** for authentication

## Functional Requirements
### 1. Pedestal Authorization System
- A **photoresistor** detects object presence.
- The object **communicates via RFID** with the pedestal.
- If the RFID tag matches the database, a **green LED** confirms correct placement.
- If removed or mismatched, **warning and alarm sequences** initiate.

### 2. Security Events
Each event corresponds with a different LED and response:
| Event | LED Color | Response |
|---|---|---|
| Correct Placement | Green | Normal Operation |
| Missing Item | Orange | Slow Beep & Warning |
| Incorrect Item | Blue | Long Alarm Beep |
| Unauthorized Item | Red | Fast Alarm, Door Lock |

### 3. Automated Door System
- Remains open with correct placement.
- Closes after item removal if **security escalation** occurs.

## Hardware Components
- **Microcontroller:** ATMega328p (Arduino Nano compatible)
- **RFID Receiver & Transmitter Modules**
- **Photoresistors for Object Detection**
- **LED Indicators** (Green, Orange, Blue, Red)
- **Alarm Speaker**
- **Servo Motor for Door Automation**

## Software Components
- **Embedded C Code** to manage:
  - Authentication
  - Security Protocols
  - Logging System Events
- **Logging & Audit Trail** for museum security personnel

## Installation & Setup
1. Mount **pedestal module** and connect power.
2. Attach RFID tags to **displayed artifacts**.
3. Load **museum database IDs** onto the system.
4. Configure security thresholds and responses.

## Team Members & Roles
- **Alexandre DesAulniers** - Communications Lead & GitHub Management
- **Mason Allain** - Hardware Design Lead
- **Michael Gallant** - Software Design Lead
- **Sadie Fowlow** - Team Member

## Project Timeline
| Milestone | Date |
|---|---|
| Conceptual Design & Planning | February 12, 2025 |
| Hardware Prototyping Begins | March 1, 2025 |
| Functional Prototype Completed | March 17, 2025 |
| Final Testing & Report | April 7, 2025 |

## Future Work
- **Enhance RFID Security Measures** (Encryption & Anti-Tamper Features)
- **Improve False Alarm Mitigation**
- **Develop Remote Monitoring Dashboard**
- **Expand Compatibility with Existing Museum Security Systems**

---
This README provides an overview of the **Integrated Security System** designed for museum security. Contributions and feedback are welcome!

