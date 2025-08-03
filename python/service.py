from connectDB import connect_to_db
from manageDB import *
from parser import parse_sensor_data, print_sensor_data
from process import StateController
from connectBT import BluetoothManager
import time

def last_data(cursor):
    data = select_sensor_data(cursor)[-1]
    *_, temp, hum = data
    return temp, hum

def set_data(cursor):
    data = select_setting_data(cursor)[0]
    _, temp, hum = data
    return temp, hum

def service():
    conn = connect_to_db()
    cursor = conn.cursor()
    bt = BluetoothManager()
    temp_ctr = StateController(1)
    hum_ctr = StateController(5)
    bt.connect()
    try:
        while True:
            rx_data = bt.receive_data()
            # print(rx_data)
            if rx_data is not None:
                temp, hum, timestamp = parse_sensor_data(rx_data)
                if temp is not None and hum is not None and timestamp is not None:
                    insert_sensor_data(cursor, temp, hum, timestamp)
                    conn.commit()
                    # print_sensor_data(temp, hum, timestamp)
                    
            temp, hum = last_data(cursor)
            set_temp, set_hum = set_data(cursor)
            # print(temp, hum)
            # print(set_temp, set_hum)

            temp_diff = temp - set_temp
            hum_diff = hum - set_hum

            temp_state = temp_ctr.update_state(temp_diff).value
            hum_state = hum_ctr.update_state(hum_diff).value
            tx_data = f"{temp_state,hum_state}"
            bt.transmit_data(tx_data)
            time.sleep(0.5)

    except KeyboardInterrupt:
        print("🛑 종료됨")

    finally:
        bt.close()
        # service.py에서 cursor와 conn을 close()해야 함
        cursor.close()
        conn.close()


if __name__ == "__main__" :
    service()