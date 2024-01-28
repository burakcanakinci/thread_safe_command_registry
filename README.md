# Thread-Safe Command Registry

This C++ project implements a thread-safe command registry with the ability to add, remove, and fetch commands. The commands are organized by receiver and include essential information such as command number, receiver, command type, and payload.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building the Project](#building-the-project)
- [Usage](#usage)
  - [Example Usage](#example-usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Thread-safe implementation using `std::mutex`
- Addition, removal, and fetching of commands
- Organization of commands by receiver, receiver command number, and global command number

## Getting Started

### Prerequisites

- C++ compiler (GCC, MinGW, or equivalent)

### Building the Project

1. Clone the repository:

```bash
git clone https://github.com/your-username/command-registry.git
cd command-registry
