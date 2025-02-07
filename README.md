# 🌟 42 Philosophers Project

<div align="center">

![Philosophers](https://img.shields.io/badge/Project-Philosophers-blue?style=for-the-badge&logo=42)
![Language](https://img.shields.io/badge/Language-C-orange?style=for-the-badge&logo=c)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

## 📚 Table of Contents

<details>
<summary>Click to expand</summary>

- [📍 Overview](#overview)
- [✨ Features](#features)
- [🧠 Algorithm Details](#algorithm-details)
- [🚀 Getting Started](#getting-started)
- [🖥️ Usage](#usage)
- [⚙️ Testing](#testing)
- [🤝 Contributing](#contributing)
- [📜 License](#license)

</details>

---

## 📍 Overview

The **Philosophers** project simulates the **Dining Philosophers Problem**, where philosophers (threads) sit around a table and share a limited number of forks. The goal is to develop a **deadlock-free** solution using **C** and **pthread**.

Philosophers alternate between:
- **Thinking** 💭
- **Eating** 🍽️
- **Sleeping** 💤

However, the challenge lies in ensuring no philosopher gets stuck (deadlocks) or starves. This is achieved through synchronized thread management and resource sharing with **mutexes**.

---

## ✨ Features

- 🧑‍💻 **C Implementation**: Written in **C**, using **`pthread`** for managing threads.
- 🔄 **Multithreading & Synchronization**: Avoids deadlocks by using **mutexes** for fork management.
- ⚙️ **Deadlock-Free**: Implemented an even-odd fork locking strategy to prevent deadlocks.
- ⏱️ **Customizable**: Adjust simulation parameters like time to eat, die, and sleep.
- 🚀 **Edge Case Handling**: Specifically handles the case of a single philosopher.
- 🔄 **Retries**: If forks are unavailable, philosophers will retry a set number of times to acquire them.

---

## 🧠 Algorithm Details

### **Fork Management**

The core of this project is ensuring philosophers can **take** and **release** forks without blocking each other indefinitely. Here's how it works:

1. **Philosophers' Actions**: Philosophers will alternate between thinking, eating, and sleeping.
   - **Thinking** 💭: Philosophers think and do not need any forks.
   - **Eating** 🍽️: Philosophers need **two forks** (one for each hand). They must pick them up in the correct order.
   - **Sleeping** 💤: After eating, philosophers sleep and release the forks.
   
2. **Deadlock Prevention**: To avoid deadlocks:
   - **Even-ID Philosophers** pick up the **left fork** first, followed by the **right fork**.
   - **Odd-ID Philosophers** pick up the **right fork** first, followed by the **left fork**.

3. **Retries**: If a philosopher cannot acquire both forks, they retry for a set number of attempts before giving up. This avoids blocking other philosophers from eating.

4. **Single Philosopher**: If there is only one philosopher, they will try to pick up a single fork and die after the `time_to_die` period due to starvation.

5. **Fork Release**: After eating, philosophers **release both forks** to let other philosophers eat.

### **Code Walkthrough**

The code ensures that each philosopher will:
- Lock the forks using mutexes.
- If the philosopher fails to acquire both forks, they will **retry** for a limited time.
- Once eating is done, the philosopher releases the forks.

---

## 🚀 Getting Started

### 📦 Prerequisites

Before running the project, make sure you have the following installed:

- **`gcc`** or any compatible C compiler.
- **`make`** utility to build the project.
- **`pthread`** library (typically bundled with `gcc`).

### 🔧 Installation

1. Clone the repository:

 ```bash
   git clone https://github.com/yourusername/philosophers.git
```
2. Navigate to the project directory and run:

```bash
cd philosophers
make
```
This will compile the project and generate the executable philo.

## 🖥️ Usage

To run the philosopher simulation, use the following command format:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
### Parameters:

- **`number_of_philosophers`**: 
  - The total number of philosophers in the simulation. Each philosopher will sit at a table and alternate between thinking, eating, and sleeping.

- **`time_to_die`**: 
  - The maximum amount of time (in milliseconds) a philosopher can go without eating. If a philosopher doesn't eat within this time, they will die (simulated starvation).

- **`time_to_eat`**: 
  - The time (in milliseconds) it takes for a philosopher to eat once they have acquired both forks.

- **`time_to_sleep`**: 
  - The time (in milliseconds) a philosopher sleeps after eating before thinking again.

- **`number_of_times_each_philosopher_must_eat` (optional)**: 
  - If provided, the simulation will stop after every philosopher has eaten this number of times. If this parameter is omitted, the simulation will run indefinitely until a philosopher dies.
### Example Commands:

1. **One philosopher (edge case)**:

```bash
./philo 1 800 200 200
```
Expected outcome:

There is only 1 philosopher.
They have a time_to_die of 800 ms.
time_to_eat and time_to_sleep are both set to 200 ms.
The philosopher will not be able to eat as there is only one fork available, causing them to die from starvation after 800 ms.

2. **Five philosophers, normal simulation**:

```bash
./philo 5 800 200 200
```
Expected outcome:

There are 5 philosophers.
They will eat and sleep in turns, without any deadlock.
No philosopher will die because they are all getting the chance to eat.

3. **Five philosophers, with number of meals setted**:

```bash
./philo 5 800 200 200 7
```
Expected outcome:

There are 5 philosophers.
Each philosopher will eat a total of 7 times, and the simulation will stop after that.

4. **Four philosophers with limited time to eat and sleep**:
```bash
./philo 4 410 200 200
```
Expected outcome:

There are 4 philosophers, each with a time_to_die of 410 ms.
Philosophers will eat and sleep without anyone dying because the time for each action is sufficient.
5. **Four philosophers with shorter time_to_die and time_to_sleep**:
```bash
./philo 4 310 200 100
```
Expected outcome:

One philosopher will die because the time_to_die is too short to allow all philosophers to complete their cycles of eating and sleeping.

5. **Testing with two philosophers, different time values**:
```bash
./philo 2 1000 500 500
```
Expected outcome:

Two philosophers with different time_to_die, time_to_eat, and time_to_sleep values.
Test for accurate death timing, ensuring no delays beyond a few milliseconds in death.
## ⚙️ Testing

To ensure your simulation is working as expected, here are some **testing guidelines**:

- **Test edge cases** like:
  - One philosopher (they should die due to starvation).
  - A small number of philosophers with reasonable parameters (should run without deadlocks).
  - A larger number of philosophers (up to 200) to test system limits.

- **Test edge cases like**:
  - Very short or long `time_to_die`, `time_to_eat`, and `time_to_sleep` values.
  - Ensure philosophers take turns eating, without stealing forks or dying too early.

### Third-Party Testers

You can also use third-party testers to validate the correctness of your simulation:

- [LazyPhilosophersTester](https://github.com/42School/Philosophers-Tester)
- [Philosphers-42Project-Tester](https://github.com/42School/Philosophers-42Project-Tester)
