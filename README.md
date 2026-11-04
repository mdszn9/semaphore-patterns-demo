# Semaphore Patterns, Visualized

An interactive, step-by-step visualization of five classic **POSIX semaphore** programs from Operating Systems.

**Live site:** https://mdszn9.github.io/semaphore-patterns-demo/

## What's inside

Each program runs on a simulated single CPU. The page shows the CPU (the running thread, the line it is executing, its registers, the ready queue, sleeping threads, a history of who ran each step and a count of context switches), one card per thread with its own code and program counter, and each semaphore drawn as a padlock with its value, the threads holding it and the threads blocked on it. Press **Run** to let the scheduler decide, or press a thread's button to schedule it yourself. Every demo also has a broken mode that shows what the semaphore prevents.

| # | Program | Pattern | Broken modes |
|---|---------|---------|--------------|
| 1 | [`serialization.c`](src/serialization.c) | Signaling (A before B), `done = 0` | No semaphore: B pours before A boils |
| 2 | [`rendezvous.c`](src/rendezvous.c) | Two-way signaling, both start at 0 | Wait before signal: deadlock. No semaphores: someone leaves early |
| 3 | [`pingpong.c`](src/pingpong.c) | Strict alternation, `(1, 0)` | `(0, 0)`: deadlock. `(1, 1)`: out-of-turn prints |
| 4 | [`tickets.c`](src/tickets.c) | Mutual exclusion, `mutex = 1` | No mutex: lost updates and overselling. Forgetting `sem_post`: deadlock. Includes a full 100,000-ticket run |
| 5 | [`parking.c`](src/parking.c) | Counting semaphore, `spots = N` | No semaphore: the lot overflows. Spots and cars are adjustable |

## Run locally

It's a single static file with no build step and no dependencies:

```sh
open index.html
```

To compile the C programs on Linux, run `gcc src/tickets.c -o tickets -pthread`. macOS does not support unnamed semaphores (`sem_init`).
