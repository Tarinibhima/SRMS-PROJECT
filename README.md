# SRMS Project

**Student Record Management System (SRMS)**

Simple C-based console project that manages student records (add, display, search, update, delete) and supports an automated simulation input to produce reproducible output.

---

## Features

* Login system with role support (admin, teacher, user, student, guest)
* Add / Display / Search / Update / Delete student records
* Uses a plain text `student.txt` file as a simple database
* Supports automated simulations via `simulation.txt` → `srms.exe` input redirection
* `simulation_output.txt` captures the entire program output for evidence/testing

---

## Files in this repository

* `main.c` — source code (C)
* `srms.exe` — compiled executable (local binary; typically excluded from repos)
* `student.txt` — student data file (text)
* `simulation.txt` — automated input script for simulation runs
* `simulation_output.txt` — output captured from simulation runs
* `credentials.txt` — username/password lines used by the login
* `.gitignore` — files to ignore (recommended to add `srms.exe`)

---

## How to compile (Windows with MinGW)

1. Open a terminal in the project folder.
2. Compile the program:

```bash
gcc main.c -o srms.exe
```

(If you use WSL/Linux/macOS, adjust the commands accordingly: `gcc main.c -o srms`.)

---

## How to run (manual)

1. Run the program interactively:

```bash
./srms.exe   # or .\srms.exe on Windows
```

2. Use the menu to add/display/search/update/delete students.

---

## How to run simulation (automated)

To reproduce the automated run (useful for grading or demo):

**Windows (Command Prompt):**

```cmd
srms.exe < simulation.txt > simulation_output.txt
```

**PowerShell (if you prefer):**

```powershell
Get-Content simulation.txt | .\srms.exe | Out-File -FilePath simulation_output.txt -Encoding utf8
```

Notes:

* `simulation.txt` must exactly match the program prompts, including blank lines where the program waits for an Enter key.
* The first two lines of `simulation.txt` must be the username and password (e.g. `admin` and `admin123`) to pass login.

---

## Common troubleshooting

* If the output contains `Login Failed. Exiting...` — check `credentials.txt` and ensure the username/password lines in `simulation.txt` match exactly.
* If simulation output shows duplicated students, clear `student.txt` before running to start fresh:

**Windows (cmd):**

```cmd
type NUL > student.txt
```

**PowerShell:**

```powershell
Set-Content -Path student.txt -Value ''
```

* If `simulation_output.txt` shows weird `NUL` characters, delete the file and regenerate using the correct redirection command in cmd.

---

## Recommended .gitignore

Add the following to `.gitignore` to avoid pushing the compiled binary:

```
srms.exe
*.exe
```

---

## Commit & push (quick commands)

Once you are satisfied with changes, run:

```bash
git add README.md simulation.txt student.txt simulation_output.txt
git commit -m "Add README and update simulation and student files"
git push
```

---

## Screenshots / Demo

You can add a screenshot of `simulation_output.txt` or the running program in the `README` by uploading images to the repository and inserting Markdown image links.

---

## Credits

Created by **Tarinibhima** — SRMS project for lab/assignment purposes.

