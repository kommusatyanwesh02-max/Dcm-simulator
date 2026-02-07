import tkinter as tk
from tkinter import messagebox
from diagnostic_client import DiagnosticClient


class DiagnosticGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("VECU Diagnostic Tool")

        self.client = DiagnosticClient()

        # ----- Connection Frame -----
        conn_frame = tk.Frame(root)
        conn_frame.pack(pady=5)

        tk.Button(conn_frame, text="Connect", width=12,
                  command=self.connect).pack(side=tk.LEFT, padx=5)

        tk.Button(conn_frame, text="Disconnect", width=12,
                  command=self.disconnect).pack(side=tk.LEFT, padx=5)

        # ----- Buttons Frame -----
        btn_frame = tk.Frame(root)
        btn_frame.pack(pady=10)

        tk.Button(btn_frame, text="Read VIN",
                  width=20, command=self.read_vin).grid(row=0, column=0, padx=5, pady=5)

        tk.Button(btn_frame, text="Unlock Security",
                  width=20, command=self.unlock_security).grid(row=0, column=1, padx=5, pady=5)

        tk.Button(btn_frame, text="Read Vehicle Speed",
                  width=20, command=self.read_speed).grid(row=1, column=0, padx=5, pady=5)

        tk.Button(btn_frame, text="ECU Reset",
                  width=20, command=self.ecu_reset).grid(row=1, column=1, padx=5, pady=5)

        # ----- Custom Request -----
        custom_frame = tk.Frame(root)
        custom_frame.pack(pady=10)

        tk.Label(custom_frame, text="Custom UDS Request (hex):").pack()

        self.req_entry = tk.Entry(custom_frame, width=40)
        self.req_entry.pack(pady=5)

        tk.Button(custom_frame, text="Send Request",
                  command=self.send_custom).pack()

        # ----- Response Box -----
        tk.Label(root, text="Response:").pack()

        self.response_text = tk.Text(root, height=8, width=60)
        self.response_text.pack(pady=5)

    # ---------------- Actions ----------------

    def connect(self):
        try:
            self.client.connect()
            self.log("Connected to VECU")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def disconnect(self):
        self.client.disconnect()
        self.log("Disconnected")

    def send_and_log(self, req):
        try:
            res = self.client.send_request(req)
            self.log(f"REQ: {req}")
            self.log(f"RES: {res}")
        except Exception as e:
            messagebox.showerror("Error", str(e))

    def read_vin(self):
        self.send_and_log("22 F1 90")

    def unlock_security(self):
        self.send_and_log("27 01")
        self.send_and_log("27 02 5B")

    def read_speed(self):
        self.send_and_log("22 F1 87")

    def ecu_reset(self):
        self.send_and_log("11 01")

    def send_custom(self):
        req = self.req_entry.get()
        if req.strip():
            self.send_and_log(req)

    def log(self, text):
        self.response_text.insert(tk.END, text + "\n")
        self.response_text.see(tk.END)


if __name__ == "__main__":
    root = tk.Tk()
    app = DiagnosticGUI(root)
    root.mainloop()
