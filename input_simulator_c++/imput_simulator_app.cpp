#include "imput_simulator_app.h"

void printHelp();

int32_t main() {
    printHelp();

    InputSimulator simulator;
    std::string input;

    std::cout << "(Use 'enter' for Enter key, 'space' for Space key, 'f1' for F1 key)\n";
    std::getline(std::cin, input);

    std::cout << "Starting simulation...\n";
    simulator.start(input);

    std::cout << "Press Enter to stop the simulation.\n";
    std::cin.ignore();

    std::cout << "Stopping simulation...\n";
    simulator.stop();

    std::cout << "Simulation stopped.\n";
    return 0;
}

void printHelp() {
    std::cout << "### Input Simulator Help\n\n";
    std::cout << "**Custom Event Format:**\n";
    std::cout << "- Use the format `event:interval` to specify each event and its corresponding interval.\n";
    std::cout << "- Separate multiple events with spaces.\n";
    std::cout << "- Example: `left_click:10 space:5`\n\n";

    std::cout << "**Supported Events:**\n";
    std::cout << "- **Keyboard Keys:** `enter`, `space`, `tab`, `esc`, `backspace`, `delete`, `up`, `down`, `left`, `right`\n";
    std::cout << "- **Function Keys:** `f1` to `f12`\n";
    std::cout << "- **Mouse Actions:** `left_click`, `right_click`\n\n";

    std::cout << "**Controls:**\n";
    std::cout << "- Enter a custom event sequence in the prompt.\n";
    std::cout << "- Press Enter to start the simulation.\n";
    std::cout << "- Press Enter again to stop the simulation.\n\n";

    std::cout << "**Usage Examples:**\n\n";

    std::cout << "1. **Example 1:**\n";
    std::cout << "   - **Input:** `left_click:10 right_click:3`\n";
    std::cout << "   - **Description:** Left click after 10 seconds, then right click after an additional 3 seconds, and continue looping.\n\n";

    std::cout << "2. **Example 2:**\n";
    std::cout << "   - **Input:** `enter:2 space:1 tab:2 esc:3`\n";
    std::cout << "   - **Description:** Press Enter after 2 seconds, press Space after an additional 1 second, press Tab after another 2 seconds, and finally press Esc after 3 more seconds, and continue looping.\n\n";

    std::cout << "3. **Example 3:**\n";
    std::cout << "   - **Input:** `f1:4 f2:4 left_click:2`\n";
    std::cout << "   - **Description:** Press F1 after 4 seconds, press F2 after another 4 seconds, and perform a left click after 2 more seconds, and continue looping.\n\n";

    std::cout << "4. **Example 4:**\n";
    std::cout << "   - **Input:** `a:1 b:1 c:1`\n";
    std::cout << "   - **Description:** Type 'a' after 1 second, type 'b' after another 1 second, and type 'c' after yet another 1 second, and continue looping.\n\n";

    std::cout << "5. **Example 5:**\n";
    std::cout << "   - **Input:** `left_click:10 space:5`\n";
    std::cout << "   - **Description:** Perform a left click after 10 seconds, then press Space after an additional 5 seconds, and continue looping.\n";
}