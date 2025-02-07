import tkinter as tk
import threading
import time
from tkinter import messagebox, Toplevel, Text
from pynput.keyboard import Controller as KeyboardController, Key
from pynput.mouse import Button, Controller as MouseController

class InputSimulatorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Input Simulator")

        self.keyboard_controller = KeyboardController()
        self.mouse_controller = MouseController()

        self.custom_event_entry = tk.Entry(root, width=60)
        self.loop_var = tk.BooleanVar(value=True)
        self.start_button = tk.Button(root, text="Start", command=self.start_simulation)
        self.stop_button = tk.Button(root, text="Stop", command=self.stop_simulation)
        self.status_label = tk.Label(root, text="", fg="red")
        self.help_button = tk.Button(root, text="Help", command=self.show_help)

        self.create_widgets()

        self.simulation_thread = None
        self.running = False
        self.events = []
        self.current_event_index = 0
        self.next_event_time = 0
        self.lock = threading.Lock()

    def create_widgets(self):
        tk.Label(self.root, text="(Use 'enter' for Enter key, 'space' for Space key, 'f1' for F1 key)").grid(row=0, column=0, columnspan=2, padx=10, pady=5)
        self.custom_event_entry.grid(row=1, column=0, columnspan=4, padx=10, pady=5)

        tk.Checkbutton(self.root, text="Loop Events", variable=self.loop_var).grid(row=2, column=0, padx=10, pady=5)

        self.start_button.grid(row=3, column=0, padx=10, pady=10)
        self.stop_button.grid(row=3, column=1, padx=10, pady=10)
        self.help_button.grid(row=3, column=2, padx=10, pady=10)

        self.status_label.grid(row=4, column=0, columnspan=3, padx=10, pady=5)

    def start_simulation(self):
        if self.running:
            messagebox.showwarning("Warning", "Simulation is already running.")
            return

        custom_event_str = self.custom_event_entry.get().strip()

        if not custom_event_str:
            messagebox.showerror("Error", "Please enter a custom event.")
            return

        try:
            events_with_intervals = [event.split(':') for event in custom_event_str.split()]
            self.events = [(event.strip(), int(interval.strip())) for event, interval in events_with_intervals]
        except ValueError:
            messagebox.showerror("Error", "Invalid format. Please use 'event:interval' format.")
            return

        self.current_event_index = 0
        self.next_event_time = time.time() + self.events[0][1]

        self.running = True
        self.simulation_thread = threading.Thread(target=self.run_simulation)
        self.simulation_thread.start()

    def stop_simulation(self):
        with self.lock:
            self.running = False
        if self.simulation_thread and self.simulation_thread.is_alive():
            self.simulation_thread.join()
        self.status_label.config(text="")
        messagebox.showinfo("Info", "Simulation stopped.")

    def run_simulation(self):
        while True:
            with self.lock:
                if not self.running:
                    break

            current_time = time.time()
            remaining_time = self.next_event_time - current_time

            if remaining_time > 0:
                self.status_label.config(text=f"Next event in {remaining_time:.1f} seconds")
                time.sleep(min(0.1, remaining_time))  # Sleep for at most 0.1 seconds or until the next event
            else:
                if self.current_event_index < len(self.events):
                    event, interval = self.events[self.current_event_index]
                    self.execute_event(event)
                    self.current_event_index += 1
                    if self.current_event_index < len(self.events):
                        self.next_event_time = time.time() + self.events[self.current_event_index][1]
                    else:
                        if self.loop_var.get():
                            self.current_event_index = 0
                            self.next_event_time = time.time() + self.events[0][1]
                        else:
                            with self.lock:
                                self.running = False
                            self.status_label.config(text="Simulation completed.")

    def execute_event(self, event):
        if event == "enter":
            self.keyboard_controller.press(Key.enter)
            self.keyboard_controller.release(Key.enter)
        elif event == "space":
            self.keyboard_controller.press(Key.space)
            self.keyboard_controller.release(Key.space)
        elif event == "tab":
            self.keyboard_controller.press(Key.tab)
            self.keyboard_controller.release(Key.tab)
        elif event == "esc":
            self.keyboard_controller.press(Key.esc)
            self.keyboard_controller.release(Key.esc)
        elif event == "backspace":
            self.keyboard_controller.press(Key.backspace)
            self.keyboard_controller.release(Key.backspace)
        elif event == "delete":
            self.keyboard_controller.press(Key.delete)
            self.keyboard_controller.release(Key.delete)
        elif event == "up":
            self.keyboard_controller.press(Key.up)
            self.keyboard_controller.release(Key.up)
        elif event == "down":
            self.keyboard_controller.press(Key.down)
            self.keyboard_controller.release(Key.down)
        elif event == "left":
            self.keyboard_controller.press(Key.left)
            self.keyboard_controller.release(Key.left)
        elif event == "right":
            self.keyboard_controller.press(Key.right)
            self.keyboard_controller.release(Key.right)
        elif event.startswith("f") and len(event) == 2 and event[1].isdigit():
            f_key_number = int(event[1])
            if 1 <= f_key_number <= 12:
                f_key = getattr(Key, f"f{f_key_number}")
                self.keyboard_controller.press(f_key)
                self.keyboard_controller.release(f_key)
        elif event == "left_click":
            self.mouse_controller.click(Button.left, 1)
        elif event == "right_click":
            self.mouse_controller.click(Button.right, 1)
        else:
            self.keyboard_controller.press(event)
            self.keyboard_controller.release(event)

    def show_help(self):
        help_window = Toplevel(self.root)
        help_window.title("Help")
        help_window.geometry("600x400")

        help_text = """
        ### Input Simulator Help

        **Custom Event Format:**
        - Use the format `event:interval` to specify each event and its corresponding interval.
        - Separate multiple events with spaces.
        - Example: `left_click:10 space:5`

        **Supported Events:**
        - **Keyboard Keys:** `enter`, `space`, `tab`, `esc`, `backspace`, `delete`, `up`, `down`, `left`, `right`
        - **Function Keys:** `f1` to `f12`
        - **Mouse Actions:** `left_click`, `right_click`

        **Loop Events:**
        - Check the "Loop Events" checkbox to make the event sequence loop indefinitely.

        **Controls:**
        - Click "Start" to begin the simulation.
        - Click "Stop" to halt the simulation.
        - Click "Help" to view this help information.

        **Usage Examples:**

        1. **Example 1:**
           - **Input:** [ left_click:5 right_click:3 ]
           - **Description:** Left click after 5 seconds, then right click after an additional 3 seconds.

        2. **Example 2:**
           - **Input:** [ enter:2 space:1 tab:2 esc:3 ]
           - **Description:** Press Enter after 2 seconds, press Space after an additional 1 second, press Tab after another 2 seconds, and finally press Esc after 3 more seconds.

        3. **Example 3:**
           - **Input:** [ f1:4 f2:4 left_click:2 ]
           - **Description:** Press F1 after 4 seconds, press F2 after another 4 seconds, and perform a left click after 2 more seconds.

        4. **Example 4:**
           - **Input:** [ a:1 b:1 c:1 ]
           - **Description:** Type 'a' after 1 second, type 'b' after another 1 second, and type 'c' after yet another 1 second.

        5. **Example 5:**
           - **Input:** [ left_click:10 space:5 ]
           - **Description:** Perform a left click after 10 seconds, then press Space after an additional 5 seconds.
           - **Loop Events Checked:** The sequence will repeat indefinitely.
        """

        text_widget = Text(help_window, wrap='word', height=20, width=70)
        text_widget.insert(tk.END, help_text)
        text_widget.config(state=tk.DISABLED)  # read-only
        text_widget.pack(padx=10, pady=10)

if __name__ == "__main__":
    root = tk.Tk()
    app = InputSimulatorApp(root)
    root.mainloop()



