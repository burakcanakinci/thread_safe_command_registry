#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <mutex>

struct Cmd {
    uint32_t global_cmd_num; // unique global command number, sequentially incremented by the issuer at command issue time
    uint32_t receiver_cmd_num; // per receiver command number (set by the issuer at command issue time), not necessarily unique per receiver
    uint32_t receiver; 
    uint32_t cmd_type;
    uint8_t *payload; // ptr to command specific data
    uint16_t payload_size;
};

class CommandRegistry {
private:
    std::mutex mutex_;
    std::unordered_map<uint32_t, std::vector<Cmd>> registry_;
    uint32_t cmd_type_counter_;
    uint32_t initial_receiver_cmd_num_;
    uint32_t initial_receiver_;
public:
    // Constructor with initial values
    CommandRegistry(uint32_t initial_cmd_type,
                    uint32_t initial_receiver_cmd_num,
                    uint32_t initial_receiver)
        : cmd_type_counter_(initial_cmd_type),
          initial_receiver_cmd_num_(initial_receiver_cmd_num),
          initial_receiver_(initial_receiver) {}

    // Add a batch of commands
    void addCommands(const std::vector<Cmd>& commands) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& cmd : commands) {
            auto& receiver_commands = registry_[cmd.receiver];
            auto it = std::lower_bound(receiver_commands.begin(),
                                       receiver_commands.end(),
                                       cmd.receiver_cmd_num,
                                       [](const Cmd& c, uint32_t receiver_cmd_num) {
                                           return c.receiver_cmd_num < receiver_cmd_num;
                                       });

            if (it != receiver_commands.end() &&
                it->receiver_cmd_num == cmd.receiver_cmd_num &&
                it->global_cmd_num < cmd.global_cmd_num) {
                    *it = cmd;  // Replace with the newer command (update)
                    std::cout << "Command " << cmd.receiver_cmd_num << " " << cmd.receiver << " " << cmd.cmd_type << " is updated\n";
            } else {
                receiver_commands.insert(it, cmd);
                std::cout << "Command " << cmd.receiver_cmd_num << " " << cmd.receiver << " " << cmd.cmd_type << " is added\n";
            }
        }
    }

    // Remove a batch of commands
    void removeCommands(uint32_t receiver, uint32_t receiver_cmd_num) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& receiver_commands = registry_[receiver];
        auto it = std::remove_if(receiver_commands.begin(),
                                 receiver_commands.end(),
                                 [receiver_cmd_num](const Cmd& cmd) {
                                     return cmd.receiver_cmd_num == receiver_cmd_num;
                                 });

        receiver_commands.erase(it, receiver_commands.end());
    }

    // Fetch commands for a receiver
    std::vector<Cmd> getCommands(uint32_t receiver, uint32_t start_receiver_cmd_num) {
        std::lock_guard<std::mutex> lock(mutex_);
        auto& receiver_commands = registry_[receiver];
        auto it = std::lower_bound(receiver_commands.begin(),
                                   receiver_commands.end(),
                                   start_receiver_cmd_num,
                                   [](const Cmd& cmd, uint32_t start_cmd_num) {
                                       return cmd.receiver_cmd_num < start_cmd_num;
                                   });

        return std::vector<Cmd>(it, receiver_commands.end());
    }
};


int main() {
    // Example usage
    static uint32_t global_cmd_num = 0;
    CommandRegistry commandRegistry(1, 1, 101);

    char userInput;
    do {
        std::cout << "Do you want to add a command? (y/n): ";
        std::cin >> userInput;

        if (userInput == 'y') {
            Cmd cmd;
            cmd.global_cmd_num = ++global_cmd_num;  // Increment global_cmd_num for each new command
            std::cout << "Enter receiver_cmd_num, receiver, and cmd_type separated by spaces (e.g. 1 101 1): ";
            std::cin >> cmd.receiver_cmd_num >> cmd.receiver >> cmd.cmd_type;
            commandRegistry.addCommands({cmd});
        }
    } while (userInput == 'y');

    // Fetch commands for a receiver
    std::vector<Cmd> fetchedCommands = commandRegistry.getCommands(101, 0);
    for (const auto& cmd : fetchedCommands) {
        std::cout << "Fetched Receiver: " << cmd.receiver << ", CmdNum: " << cmd.receiver_cmd_num << ", CmdType: " << cmd.cmd_type;
        std::cout << " Global CmdNum: " << cmd.global_cmd_num << "\n";
    }

    // Remove commands
    commandRegistry.removeCommands(101, 1);

    return 0;
}