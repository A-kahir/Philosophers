# Philosophers

<p align="center">
  A concurrency and synchronization project written in C, based on the famous Dining Philosophers Problem.
</p>

<p align="center">
  Part of the 42 Network curriculum.
</p>

---

## 📖 About the Project

**Philosophers** is a project from the 42 Network curriculum that introduces the fundamentals of concurrent programming and multithreading.

The project is based on the classic **Dining Philosophers Problem**, where several philosophers sit around a table, alternating between eating, thinking, and sleeping.

Each philosopher needs two forks to eat, but there is only one fork between every pair of philosophers. The challenge is to manage shared resources while avoiding deadlocks, data races, and unexpected behavior.

The main objective is to simulate this situation using threads and synchronization mechanisms while ensuring that the simulation follows the required rules.

## ✨ Features

- Simulation of multiple philosophers.
- Multithreading using POSIX threads (`pthread`).
- Mutexes for protecting shared resources.
- Fork management and synchronization.
- Monitoring philosopher states.
- Death detection when a philosopher exceeds their time limit without eating.
- Simulation termination when a philosopher dies or all philosophers finish eating, when a meal limit is specified.
- Timestamped simulation logs.

## 🧠 Core Concepts

| Concept | Description |
|---|---|
| Threads | Running multiple philosophers concurrently |
| Mutexes | Protecting shared resources |
| Synchronization | Coordinating access to forks |
| Deadlocks | Understanding and preventing resource conflicts |
| Data Races | Avoiding simultaneous unsafe access to shared data |
| Time Management | Tracking eating, sleeping, and thinking durations |

## 🛠️ Technologies Used

- **C** – Main programming language.
- **POSIX Threads (pthread)** – Multithreading.
- **Mutexes** – Thread synchronization.
- **Makefile** – Project compilation.
- **Linux / UNIX** – Development environment.

## 🚀 Installation & Usage

### 1. Clone the repository

```bash
git clone <repository-url>
cd philosophers
```

### 2. Compile the project

```bash
make
```

### 3. Run the simulation

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 5 800 200 200
```

This starts a simulation with:

- 5 philosophers.
- 800 ms before a philosopher dies without eating.
- 200 ms to eat.
- 200 ms to sleep.

### 4. Clean generated files

```bash
make clean
make fclean
make re
```

## 📚 What I Learned

Working on Philosophers helped me develop a deeper understanding of:

- Multithreading and concurrent programming.
- Creating and managing threads using `pthread`.
- Mutexes and synchronization mechanisms.
- Shared resources and critical sections.
- Deadlocks and race conditions.
- Resource management and thread safety.
- Time management in concurrent systems.
- Debugging and handling concurrency-related problems.

## 👤 Author

**Aymane Kahir**

42 Network Student | 1337 Coding School
