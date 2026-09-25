# Hospital Management System

A console-based hospital simulation built in C.

---

## Run

```bash
gcc Hospital.c -o hospital
./hospital
```

---

## Features

- Admit patients — auto-assigns doctor and bed based on disease and ward type
- Discharge patients with an itemised bill (ward stay + medicines)
- View real-time bed availability across all wards
- List all currently admitted patients with full details

---

## Billing

```
Total Bill = (Ward Rate × Stay Duration) + Medicine Cost
```

| Ward Type   | Rate per Day |
|-------------|-------------|
| General     | ₹1,000      |
| Semi-Special| ₹2,000      |
| Special     | ₹3,000      |

---

## Tech

- Language: C
- Concepts: `struct`, arrays, `string.h`, modular functions, input validation
- No external libraries — standard C only

---

## Limitations

- No persistent storage — data resets on exit
- Disease name must match the built-in list exactly (case-sensitive)
- Max 100 patients, 10 beds per ward, CLI only

---

## Future Scope

- File I/O for persistent storage
- Case-insensitive disease search
- Database integration (MySQL)
- GUI or web interface

## Hello

thank you :D
