# Philosophers: Eat, Sleep, Think, Repeat" 🍝😴💭🔄

## Project Overview 📄

**Philosophers** is an intriguing project from the 42 curriculum that dives deep into concurrency concepts like threading and mutexes. 
The project simulates a classical problem in computer science known as the **Dining Philosophers Problem**, where several philosophers sit at a table with a bowl of spaghetti 🍝 in the middle. 
The goal is to coordinate their eating and thinking behaviors without letting any philosopher starve. 💀
The philosophers follow these basic rules:
- **Eat, Sleep, Think**: Philosophers will alternate between eating, sleeping, and thinking.
- **Forks** 🍴: Each philosopher must grab two forks (one on the left and one on the right) to eat. If only one fork is available, they cannot eat.
- **Starvation** ⏳: A philosopher dies if they don't eat within a specified time limit.
- **Mutex Protection** 🔒: To avoid race conditions, forks are protected with mutexes so that only one philosopher can use a fork at any given time.

## Technologies Used 💻

<img src="https://cdn.worldvectorlogo.com/logos/c-1.svg" alt="C" width="40" height="40"/>

## How It Works 🛠️

After compiling with `make`, the program is executed with the following parameters:  
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- **number_of_philosophers**: The total number of philosophers sitting at the table (and also the number of forks).
- **time_to_die**: The maximum time (in milliseconds) a philosopher can survive without eating.
- **time_to_eat**: The time it takes for a philosopher to finish eating.
- **time_to_sleep**: The time a philosopher will spend sleeping after eating.
- **[number_of_times_each_philosopher_must_eat]** *(optional)*: If provided, the simulation will stop once all philosophers have eaten at least this many times.

## Challenges Faced 💥

- **Concurrency & Synchronization**: Managing access to shared resources (forks) between multiple threads was a significant challenge. Using mutexes effectively to avoid deadlocks and race conditions required careful design 🧩.
- **Deadlock Prevention**: Ensuring that no philosopher was waiting forever to acquire forks involved strategic ordering and careful use of mutex locks.
- **Precise Timing**: Implementing accurate timeouts for starvation detection while handling multiple threads required using system calls like `gettimeofday` and `usleep` to maintain precision ⏱️.

## What I Learned 🧠

This project was a valuable introduction to **multithreading** and **synchronization** in C, laying the foundation for more advanced projects:
- **Thread Management**: I learned how to create, detach, and join threads using `pthread_create`, `pthread_detach`, and `pthread_join`.
- **Mutexes**: I developed a strong understanding of mutexes and how to use `pthread_mutex_init`, `pthread_mutex_lock`, and `pthread_mutex_unlock` to protect shared resources.
- **Deadlock Handling**: The importance of preventing deadlock by designing efficient algorithms for resource acquisition.
- **Precise Timing & Synchronization**: Using system calls to measure time intervals and manage philosophers' actions accurately.

**Philosophers** taught me a lot about concurrency and synchronization, and I’m excited to carry this knowledge into future projects, especially those involving parallelism and process management! 🚀

