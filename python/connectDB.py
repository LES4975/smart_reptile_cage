import mysql.connector

def connect_to_db(): # 라즈베리파이의 DB에 접속하는 함수
    conn = mysql.connector.connect(
        host="localhost", # 라즈베리파이의 DB에 직접 접속할 것이기 때문에 localhost라고 설정해 두면 됩니다.
        user="root", # 유저 이름
        password="1234", # 비밀번호
        database="tp_dht11_db" # 값을 저장할 DB 이름
    )
    print("✅ MySQL DB 연결 완료")
    return conn

# 다른 파일에서 함수를 import하는 방법
# from connectDB import connect_to_db
#
# main 함수 안에 넣어야 할 코드
# conn = connect_to_db()
# cursor = conn.cursor()

# service.py에서 cursor와 conn을 close()해야 함
# cursor.close()
# conn.close()