*This project has been created as part of the 42 curriculum by <echarmai>.*

# Philosophers

## Description
The **Philosophers** project is a classic concurrency problem based on Edsger Dijkstra's famous "Dining Philosophers" puzzle. The goal is to learn the fundamentals of threading, process synchronization, and shared memory management in C.

The program simulates a group of philosophers sitting at a round table with a bowl of spaghetti in the middle. There are as many forks on the table as there are philosophers. Each philosopher alternates between three states: **eating**, **sleeping**, and **thinking**. To eat, a philosopher must pick up both their left and right forks. 

The main challenge is to prevent **deadlocks**, **starvation**, and **data races** using threads (`pthread`) and mutexes (`pthread_mutex`).

---

## Instructions

### Compilation
The project comes with a `Makefile` that supports standard rules. To compile the executable, run:

```bash
make

```

Additional Rules :

```bash
make clean
make fclean
make re
```

### Execution
Run the program with the folowing arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

`number_of_philosophers`: The number of philosophers (and forks).

`time_to_die (in ms)`: Time a philosopher can survive without eating after their last meal.

`time_to_eat (in ms)`: Time spent eating (requires two forks).

`time_to_sleep (in ms)`: Time spent sleeping.

`number_of_times_each_philosopher_must_eat` (optional): If all philosophers eat at least this many times, the simulation stops.

### Exemple

``` bash
./philo 4 410 200 200
= No one should die.
./philo 1 800 200 100
= One philosopher should die.
./philo 5 800 200 200 7
= Simulation stops when everyone has eaten 7 times.
```

---

## Ressources

### Documents and Videos
Video playlist on multithreading.
* [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5an1Il24I3XAnCAnO3R394cWn-H)

### AI usage
Debugging some parts of the code.

Help to understand a bit more precisely the multiple threads.