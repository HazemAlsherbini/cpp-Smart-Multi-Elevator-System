# Smart Multi-Elevator Dispatch System 

A console-based C++ application that simulates a smart multi-elevator dispatching system in a building.

## Features
The project architecture is cleanly divided into two major layers: Logic and UI (Screens).

### Core Logic
* **OOP Design:** Implemented Elevators and Requests as distinct classes, managed centrally by a `Dispatcher` class.
* **Flow Control:** Designed an `ElevatorSystem` class that dictates the elevator's flow, movement state, and timing.
* **Capacity Management:** Each elevator has a configurable maximum capacity (handling up to 5 requests simultaneously).
* **Smart Queuing:** Excess requests are safely stored in a pending queue and automatically dispatched when an elevator becomes available.

### User Interface (Screens)
* **Modular UI:** Each screen is encapsulated in its own class, ensuring clean separation from the business logic.
* **Interactive Experience:** A user-friendly CLI that allows users to interact with the system, send requests, and monitor the elevators' real-time movements.

## Technologies Used
* **Language:** C++
* **Concepts:** Object-Oriented Programming (OOP), Memory Management
* **Data Structures:** `std::queue`, `std::vector`, `std::map`, and Arrays
* **Environment:** Console Application / Visual Studio 2026

## How To Run

### Using Visual Studio
1. Clone this repository:
   ```bash
   git clone https://github.com/HazemAlsherbini/cpp-Smart-Multi-Elevator-System.git
   ```
2. Open the `.slnx` or `.vcxproj` file using Visual Studio.
3. Build and run the project (Press `F5`).

### Using Other IDEs / Command Line (e.g., VS Code, MinGW)
1. Clone the repository and open the project folder in your terminal.
2. Ensure you have a C++ compiler installed (e.g., GCC/MinGW).
3. Compile the main file:
   ```bash
   g++ "Smart Multi-Elevator Dispatch System.cpp" -o ElevatorSystem
   ```
4. Run the executable:
   ```bash
   ./ElevatorSystem
   ```

## 👨‍💻 Author
**Hazem Alsherbini**
*Computer Engineering Student*
* [LinkedIn](https://www.linkedin.com/in/hazemalsherbini/)
