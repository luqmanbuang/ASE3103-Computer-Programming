from flask import Flask, jsonify, request
from flask_ngrok import run_with_ngrok
import serial

ser = serial.Serial('COM3', 9600, timeout = 1)

def led_on():
    ser.write(str.encode('1'))
def led_off():
    ser.write(str.encode('0'))

app = Flask(__name__)
run_with_ngrok(app)

@app.route('/on', methods=['GET'])
def on():
    if (request.method == 'GET'):
        return led_on()

@app.route('/off', methods=['GET'])
def off():
    if (request.method == 'GET'):
        return led_off()

if __name__ == "__main__":
    app.run()




