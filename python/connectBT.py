# sudo apt install python3-bluez
# or
# 'pip install pybluez' # after set Venv
# or
# pip3 install bluez --break-package-system
# import bluetooth
# from connectBT import BluetoothManager

import bluetooth

class BluetoothManager:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super(BluetoothManager, cls).__new__(cls)
            cls._instance._initialized = False
        return cls._instance

    def __init__(self, fixed_addr="98:DA:60:04:F7:1D"):
        if self._initialized:
            return
        self.fixed_addr = fixed_addr
        self.sock = None
        self._initialized = True

    def find_device(self):
        print("🔍 주변 장치 검색 중...")
        devices = bluetooth.discover_devices(lookup_names=True)
        for addr, name in devices:
            if name and "HC-06" in name:
                print(f"✅ 장치 발견: {name} @ {addr}")
                return addr
        print("❌ 장치 못 찾음")
        return None

    def connect(self):
        try:
            if self.sock is None:
                self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
                self.sock.connect((self.fixed_addr, 1))
                print(f"🔗 연결 성공: {self.fixed_addr}")
            else : return self.sock
        except Exception:
            addr = self.find_device()
            if addr:
                self.sock.connect((addr, 1))
                print(f"🔗 검색 후 연결 성공: {addr}")
            else:
                raise Exception("❌ 블루투스 연결 실패")

    def receive_data(self):
        if not self.sock:
            self.connect()
        try:
            data = self.sock.recv(1024)
        except Exception as e:
            print(e)
        return data.decode('utf-8').strip()
    
    def transmit_data(self, message):
        if not self.sock:
            self.connect()
        self.sock.send(message.encode('utf-8'))
        # print(f"📤 송신됨: {message}")

    def close(self):
        if self.sock:
            self.sock.close()
            print("🔌 블루투스 소켓 종료")

# 테스트용 실행
if __name__ == "__main__":
    bt = BluetoothManager()
    try:
        bt.connect()
        print("📡 수신/송신 테스트 시작 (Ctrl+C로 종료)")
        while True:
            incoming = bt.receive_data()
            print(f"📥 수신: {incoming}")

            # 간단한 자동 응답 예시
            if incoming.lower() == "ping":
                bt.transmit_data("pong")
            elif incoming.lower() == "hello":
                bt.transmit_data("hi from raspberry pi")
    except KeyboardInterrupt:
        print("🛑 종료됨")
    finally:
        bt.close()