import serial
from datetime import datetime
import csv
import keyboard

current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
csv_name = f'arduino_data_{current_time}.csv'


ser = serial.Serial('COM3', 115200, timeout=1)
columns = ['Sensor1', 'Sensor2', 'Sensor3', 'Sensor4', 'Sensor5', 'Sensor6', 'Sensor7', 'Sensor8', 'Sensor9', 'Sensor10', 'Sensor11', 'Sensor12', 'Sensor13', 'Sensor14', 'Sensor15', 'Sensor16', 'Timestamp', 'Status']
def write_csv(file_path, data, mode='a'):
    with open(file_path, mode, newline='') as file:
        writer = csv.writer(file)
        writer.writerow(data)
    print(data)


write_csv(csv_name, columns, mode='w')


while True:
    line = ser.readline().decode('utf-8').strip()
    data = line.split(',')
    write_csv(csv_name, data)
    # if keyboard.is_pressed('Tab'):  
    #     write_csv(csv_name, ["New Temperature"], mode='a')
    if keyboard.is_pressed('Esc'):                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
        break

