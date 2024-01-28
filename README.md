# Thread-Safe Command Registry

This C++ project implements a thread-safe command registry with features to add, remove, and fetch commands. The command registry ensures thread safety using mutexes to handle concurrent access.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building the Project](#building-the-project)
- [Usage](#usage)
- [Example Scenario](#example-scenario)
- [Contributing](#contributing)

## Features

- Thread-safe command registry
- Adding a batch of commands
- Removing a batch of commands
- Fetching commands for a specific receiver

## Getting Started

### Prerequisites

- C++ compiler (GCC, MinGW, or equivalent)

### Building the Project

#### 1. Clone the repository:

```bash
git clone https://github.com/burakcanakinci/thread_safe_command_registry
cd thread_safe_command_registry
```

#### 2. Build the project:

```bash
g++ -o command_registry main.cpp -std=c++11 -pthread
```

### Usage

Run the compiled executable:

```bash
./command_registry
```
Follow the on-screen instructions to add, fetch, and remove commands.
 
## Example Scenario

- Do you want to add a command? (y/n): y
  - Enter receiver_cmd_num, receiver, and cmd_type separated by spaces (e.g. 1 101 1): 1 101 1
  - Command 1 101 1 is added

- Do you want to add a command? (y/n): n

- Fetch commands for receiver 101 starting from command number 0:
  - Fetched Receiver: 101, CmdNum: 1, CmdType: 1, Global CmdNum: 1

- Remove commands for receiver 101 with command number 1:
  - Command 1 101 1 is removed

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.
