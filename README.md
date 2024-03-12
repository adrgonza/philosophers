# Philosophers

Welcome to the Philosophers project! This project focuses on the classic dining philosophers problem and its solution using multithreading and synchronization techniques. By implementing this project, you'll gain a deeper understanding of concurrent programming, thread synchronization, and deadlock avoidance.

## Table of Contents

1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Problem Description](#problem-description)
4. [Solution](#solution)
5. [Building](#building)
6. [Contributing](#contributing)
7. [Credits](#credits)

## Introduction

In this project, you'll implement a simulation of the dining philosophers problem, where a group of philosophers sits at a table with a bowl of spaghetti. Each philosopher spends their time thinking and eating, but they need to share forks placed between them. The challenge is to design a solution that prevents deadlock and starvation while allowing each philosopher to eat without starving.

## Usage

To use the Philosophers program, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/adrgonza/philosophers.git
    ```

2. Build the program:

    ```bash
    make
    ```

3. Run the program with the desired number of philosophers and time to live:

    ```bash
    ./philo <number_of_philosophers> <time_to_live> <time_to_eat> <time_to_sleep> [optional: <number_of_times_each_philosopher_must_eat>]
    ```

4. Watch the simulation as philosophers think, eat, and sleep.

## Problem Description

The dining philosophers problem illustrates the challenges of resource allocation and synchronization in concurrent systems. In this problem, philosophers represent concurrent processes that require shared resources (forks) to complete their tasks (eating). The goal is to design a solution that avoids deadlock (where philosophers hold resources indefinitely) and starvation (where a philosopher may never get access to required resources).

## Solution

The solution to the dining philosophers problem typically involves implementing a form of resource allocation strategy combined with synchronization mechanisms such as mutexes and condition variables. One common solution is the "dining savages" algorithm, where each philosopher attempts to acquire both forks before eating and releases them afterward, ensuring fairness and deadlock avoidance.

## Building

To build the Philosophers program, simply run:

```bash
make
```
## Contributing
Contributions are welcome! If you find any bugs or have suggestions for improvement, please open an issue or submit a pull request on GitHub.

## Credits
This project was created by adrgonza for the philosophers project at 42Madrid.
