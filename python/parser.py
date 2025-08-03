from datetime import datetime

def parse_sensor_data(data): # 수신된 raw 문자열을 온도, 습도, 시각 데이터로 변환
    try:
        # 오류로 인하여 추가한 항목
        data = data[:9]
        data = data.replace('\x00', '').strip()
        temperature_str, humidity_str = data.split(',')
        temperature = float(temperature_str)
        humidity = float(humidity_str)
        timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        return temperature, humidity, timestamp
    except ValueError as e:
        print(f"❗ 데이터 파싱 실패: {e}")
        return None, None, None

def print_sensor_data(temperature, humidity, timestamp): # 변환된 데이터를 터미널에 출력
    if temperature is not None and humidity is not None and timestamp is not None:
        print(f"🕒 시간: {timestamp}, 🌡️ 온도: {temperature}°C, 💧 습도: {humidity}%")

# 다른 파일에 import하는 방법
# from parser import parse_sensor_dta, print_sensor_data

# main 함수의 while문 안에 넣어야 할 것
# temperature, humidity, timestamp = parse_sensor_data(received)
#  ( -> received는 receive_data(sock) 반환값을 넣을 변수 이름)
# print_sensor_data(temperature, humidity, timestamp)
