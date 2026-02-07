import socket

class DoIP:
    PROTOCOL_VERSION = 0x02FD
    PAYLOAD_TYPE_DIAG = 0x8001

    @staticmethod
    def encode(uds_payload: bytes) -> bytes:
        length = len(uds_payload)

        header = (
            DoIP.PROTOCOL_VERSION.to_bytes(2, "big") +
            DoIP.PAYLOAD_TYPE_DIAG.to_bytes(2, "big") +
            length.to_bytes(4, "big")
        )

        return header + uds_payload

    @staticmethod
    def decode(doip_frame: bytes) -> bytes:
        if len(doip_frame) < 8:
            return b""

        payload_length = int.from_bytes(doip_frame[4:8], "big")
        return doip_frame[8:8 + payload_length]


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
        uds_payload = bytes.fromhex(hex_string)

        # Encode DoIP
        doip_frame = DoIP.encode(uds_payload)
        self.sock.sendall(doip_frame)

        # Receive response
        response = self.sock.recv(512)

        # Decode DoIP
        uds_response = DoIP.decode(response)
        return uds_response.hex(" ").upper()

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
