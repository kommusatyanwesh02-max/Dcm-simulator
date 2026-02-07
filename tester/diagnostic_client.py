import socket

class DiagnosticClient:
    def __init__(self, ip="127.0.0.1", port=13400):
        self.ip = ip
        self.port = port
        self.sock = None

    def connect(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((self.ip, self.port))
        print(f"[CONNECTED] VECU at {self.ip}:{self.port}")

    def disconnect(self):
        if self.sock:
            self.sock.close()
            self.sock = None
            print("[DISCONNECTED]")

    def send_request(self, hex_string):
        """
        hex_string example: "22 F1 90"
        """
        data = bytes.fromhex(hex_string)
        self.sock.sendall(data)

        response = self.sock.recv(256)
        return response.hex(" ").upper()


if __name__ == "__main__":
    client = DiagnosticClient()
    client.connect()

    while True:
        req = input("UDS REQ> ")
        if req.lower() in ["exit", "quit"]:
            break

        res = client.send_request(req)
        print("UDS RES>", res)

    client.disconnect()
