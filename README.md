*This project has been created as part of the 42 curriculum by lrouchon*

### Description:

Philosophers is an introductory project for multithreading.
A number of philosophers sit around a table with one fork between each pair of them. Each philosopher alternates between eating, sleeping and thinking, and must pick up both the fork on their left and the fork on their right before they can eat.

The goal is to implement this simulation using threads and mutexes while avoiding race conditions and deadlocks, and making sure no philosopher starves to death (dies without eating in time).

### Instructions:

Build the program with the provided Makefile:

```sh
cd philo
make
```

Run it with the following arguments:

```sh
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: the number of philosophers and forks.
- `time_to_die` (ms): time after which a philosopher dies if it hasn't
  started eating since its last meal.
- `time_to_eat` (ms): time it takes for a philosopher to eat.
- `time_to_sleep` (ms): time a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): if provided,
  the simulation stops once every philosopher has eaten at least this
  many times.

Example:

```sh
./philo 5 800 200 200
```

### Resources:

- Resources on multithreading: https://www.geeksforgeeks.org/c/multithreading-in-c/
- Resources on using get_time_of_day(): https://c-for-dummies.com/blog/?p=4236
- Resources on avoiding deadlocks when using mutexes: https://docs.oracle.com/cd/E19455-01/806-5257/6je9h0347/index.html
