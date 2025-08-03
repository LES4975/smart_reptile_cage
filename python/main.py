from connectBT import BluetoothManager
from connectDB import connect_to_db
from manageDB import *
from parser import parse_sensor_data, print_sensor_data

def main():
    bt = BluetoothManager()
    # main 함수 안에 넣어야 할 코드
    conn = connect_to_db()
    cursor = conn.cursor()
    try:
        bt.connect()
        while True:
            rx_data = bt.receive_data()
            # print(rx_data)
            if rx_data is not None:
                temp, hum, time = parse_sensor_data(rx_data)
                if temp is not None and hum is not None and time is not None:
                    insert_sensor_data(cursor, temp, hum, time)
                    conn.commit()
                    # print_sensor_data(temp, hum, time)

    except KeyboardInterrupt:
        print("🛑 종료됨")

    finally:
        bt.close()
        # service.py에서 cursor와 conn을 close()해야 함
        cursor.close()
        conn.close()

if __name__ == '__main__' :
    main()