# 🚗 VECU – Virtual ECU with UDS & DoIP (C++ / Python)

A **PC-based Virtual ECU (VECU)** implementing **UDS diagnostics (ISO 14229)** with a  
**DoIP-style TCP transport (ISO 13400 inspired)** and a **Python diagnostic tool (CLI + GUI)**.

This project evolved from a basic DCM simulator into a **realistic diagnostic VECU**
with ECU application logic, security handling, reset behavior, and an external tester.

---

## 🧠 Project Overview

This repository contains:

- A **C++ Virtual ECU (VECU)**
- A modular **Diagnostic Communication Manager (DCM)**
- **DoIP-style framing over TCP**
- A **Python diagnostic tester (CLI + GUI)**
- ECU application layer with real ECU state

The architecture is inspired by **AUTOSAR layered design** and is suitable for:
- Learning automotive diagnostics
- Interview preparation
- SIL / VECU concept demonstration

---

## 🧱 High-Level Architecture

Python Diagnostic Tool (GUI / CLI)
|
| DoIP over TCP
v
+--------------------------------+
| VECU (C++)                     |
|                                |
| TCP Transport + DoIP           |
| |                              |
| v                              |
| DCM (UDS Dispatcher)           |
| |                              |
| v                              |
| ECU Application Layer          |
| (VIN, Speed, Security, RAM)    |
+--------------------------------+

---

## 🚀 Implemented UDS Services

| Service | SID | Description |
|------|----|-------------|
| Diagnostic Session Control | `0x10` | Session handling |
| ECU Reset | `0x11` | Application-level reset |
| Read Data By Identifier | `0x22` | VIN & Vehicle Speed |
| Security Access | `0x27` | Seed–Key mechanism |
| Tester Present | `0x3E` | Keep-alive |
| Negative Response | `0x7F` | NRC handling |

---

## 🔐 Security Access (0x27)

- Seed–Key based unlocking
- ECU owns security state
- Protected DIDs denied until unlocked
- NRC handling:
  - `0x33` – Security Access Denied
  - `0x35` – Invalid Key

Example:
27 01 → 67 01 5A
27 02 5B → 67 02

---


## 🔁 ECU Reset (0x11)

- Triggers ECU application reset
- Clears runtime data (vehicle speed)
- Locks security again
- Simulates ECU reboot behavior

Example:
11 01 → 51 01

---

## 🧪 Supported Data Identifiers (DIDs)

| DID | Description | Security |
|----|-------------|----------|
| `F190` | VIN | No |
| `F187` | Vehicle Speed | Yes |

---

## 📦 Repository Structure

dcm-simulator/
├── CMakeLists.txt
├── README.md
├── include/
│ ├── Dcm*.h
│ ├── EcuApp.h
│ ├── TcpTransport.h
│ └── DoIP.h
├── src/
│ ├── Dcm*.cpp
│ ├── EcuApp.cpp
│ ├── TcpTransport.cpp
│ └── DoIP.cpp
└── tester/
├── diagnostic_client.py
├── diagnostic_gui.py
└── requirements.txt


---

## 🛠 Build Instructions (VECU)

### Requirements
- CMake ≥ 3.10
- MSVC / GCC / Clang
- Windows or Linux

### Build
```bash
mkdir build
cd build
cmake ..
cmake --build . --config Debug

