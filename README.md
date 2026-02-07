# DCM Simulator (C++)

A lightweight Diagnostic Communication Manager (DCM) simulator written in C++,
inspired by AUTOSAR architecture and UDS (ISO 14229).

This project is intended for learning, interviews, and experimentation with
automotive diagnostics.

---

## 🚀 Features
- UDS request/response simulation
- Modular DCM architecture
- Console-based transport layer
- Positive and Negative responses (NRC)
- Easily extendable

---

## ✅ Supported UDS Services
| Service | SID |
|------|------|
| Diagnostic Session Control | 0x10 |
| ECU Reset | 0x11 |
| Read Data By Identifier | 0x22 |
| Tester Present | 0x3E |

---

## 🛠 Build Instructions

```bash
mkdir build
cd build
cmake ..
make
