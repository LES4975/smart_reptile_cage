def insert_sensor_data(cursor, temperature, humidity, timestamp):
    # 센서 측정 데이터를 measured_value 테이블에 삽입
    sql = "INSERT INTO measured_value (time, temperature, humidity) VALUES (%s, %s, %s)" #insert 쿼리
    values = (timestamp, temperature, humidity)
    cursor.execute(sql, values)

def daily_average_calculation(cursor):
    # measured_value 테이블의 각 데이터를 날짜, 온도 평균, 습도 평균으로써 선택
    select_sql = f"""
    SELECT DATE(time) AS day, AVG(temperature), AVG(humidity)
    FROM measured_value
    GROUP BY day
    """ # 일별로 그룹화
    cursor.execute(select_sql)
    result = cursor.fetchall()
    # 날짜와 평균값을 average_history에 삽입
    insert_sql = """
    INSERT INTO average_history (date, average_temperature, average_humidity)
    VALUES (%s, %s, %s)
    """
    for row in result:
        cursor.execute(insert_sql, row)

def clear_table(cursor): # measured_value에 있는 모든 데이터를 삭제
    sql = f"TRUNCATE TABLE measured_value"
    cursor.execute(sql)

def daily_update(cursor, connection):
    try:
        daily_average_calculation(cursor)
        clear_table(cursor)
        connection.commit()
    except Exception as e: # 만약에...! 에러가 발생헤서 DB 관리가 잘 안 되면!!
        connection.rollback() # 에러 발생 시 롤백
        raise e # 에러를 다시 발생시켜 상위로 전달

def select_sensor_data(cursor):
    # 저장된 데이터를 불러오기 위한 select문
    sql = "SELECT * FROM measured_value"
    cursor.execute(sql)
    return cursor.fetchall()    

def select_setting_data(cursor):
    # 저장된 데이터를 불러오기 위한 select문
    sql = "SELECT * FROM settingtb"
    cursor.execute(sql)
    return cursor.fetchall()   
# 다른 파일에서 import 하는 법
# from manageDB import *