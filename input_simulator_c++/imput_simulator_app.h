#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

#include <windows.h>

struct Event {
    std::string action;
    int32_t interval;
};

class InputSimulator {
public:
    void start(std::string& input) {
        parseInput(input);
        running = true;
        simulationThread = std::thread(&InputSimulator::runSimulation, this);
    }

    void stop() {
        running = false;
        if (simulationThread.joinable()) {
            simulationThread.join();
        }
    }

private:
    bool running = false;
    std::vector<Event> events;
    std::thread simulationThread;
    std::mutex mtx;

    void parseInput(std::string& input) {
        events.clear();
        size_t pos = 0;
        while ((pos = input.find(' ')) != std::string::npos) {
            std::string eventStr = input.substr(0, pos);
            addEvent(eventStr);
            input.erase(0, pos + 1);
        }
        addEvent(input);
    }

    void addEvent(const std::string& eventStr) {
        size_t colonPos = eventStr.find(':');
        if (colonPos == std::string::npos) {
            std::cerr << "Invalid format for event: " << eventStr << std::endl;
            return;
        }
        std::string action = eventStr.substr(0, colonPos);
        int interval = std::stoi(eventStr.substr(colonPos + 1));
        events.push_back({ action, interval });
    }

    void runSimulation() {
        while (true) {
            std::lock_guard<std::mutex> lock(mtx);
            if (!running) break;

            for (const auto& event : events) {
                if (!running) break;
                executeEvent(event.action);
                std::this_thread::sleep_for(std::chrono::seconds(event.interval));
            }
        }
    }

    void executeEvent(const std::string& action) {
        if (action == "enter") {
            keybd_event(VK_RETURN, 0, 0, 0);
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "space") {
            keybd_event(VK_SPACE, 0, 0, 0);
            keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "tab") {
            keybd_event(VK_TAB, 0, 0, 0);
            keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "esc") {
            keybd_event(VK_ESCAPE, 0, 0, 0);
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "backspace") {
            keybd_event(VK_BACK, 0, 0, 0);
            keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "delete") {
            keybd_event(VK_DELETE, 0, 0, 0);
            keybd_event(VK_DELETE, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "up") {
            keybd_event(VK_UP, 0, 0, 0);
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "down") {
            keybd_event(VK_DOWN, 0, 0, 0);
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "left") {
            keybd_event(VK_LEFT, 0, 0, 0);
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "right") {
            keybd_event(VK_RIGHT, 0, 0, 0);
            keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f1") {
            keybd_event(VK_F1, 0, 0, 0);
            keybd_event(VK_F1, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f2") {
            keybd_event(VK_F2, 0, 0, 0);
            keybd_event(VK_F2, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f3") {
            keybd_event(VK_F3, 0, 0, 0);
            keybd_event(VK_F3, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f4") {
            keybd_event(VK_F4, 0, 0, 0);
            keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f5") {
            keybd_event(VK_F5, 0, 0, 0);
            keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f6") {
            keybd_event(VK_F6, 0, 0, 0);
            keybd_event(VK_F6, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f7") {
            keybd_event(VK_F7, 0, 0, 0);
            keybd_event(VK_F7, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f8") {
            keybd_event(VK_F8, 0, 0, 0);
            keybd_event(VK_F8, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f9") {
            keybd_event(VK_F9, 0, 0, 0);
            keybd_event(VK_F9, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f10") {
            keybd_event(VK_F10, 0, 0, 0);
            keybd_event(VK_F10, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f11") {
            keybd_event(VK_F11, 0, 0, 0);
            keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "f12") {
            keybd_event(VK_F12, 0, 0, 0);
            keybd_event(VK_F12, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (action == "left_click") {
            mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if (action == "right_click") {
            mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
        else {
            INPUT input;
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = VkKeyScanA(action[0]);
            input.ki.wScan = 0;
            input.ki.dwFlags = 0;
            input.ki.time = 0;
            input.ki.dwExtraInfo = 0;
            SendInput(1, &input, sizeof(INPUT));

            input.ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(1, &input, sizeof(INPUT));
        }
    }
};
