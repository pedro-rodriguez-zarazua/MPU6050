import time
import warnings
import serial
import numpy as np
import sys
from   pythonosc import osc_message_builder
from   pythonosc import udp_client

receiver_ip        = "127.0.0.1"
sc_port            = 57120
processing_port    = 57121
sc_client          = udp_client.SimpleUDPClient(receiver_ip, sc_port)
processing_client  = udp_client.SimpleUDPClient(receiver_ip, processing_port)

synth1   = "/msg1"
_sub_     = 1

arduino = serial.Serial('/dev/tty.usbmodem1421', 115200, timeout=1.0)
arduino.setDTR(False)
time.sleep(1)
arduino.flushInput()
arduino.setDTR(True)

def send_msg(_msg_, _address_):
    msg = osc_message_builder.OscMessageBuilder(address = _address_)
    for i in range(len(_msg_)):
        msg.add_arg(_msg_[i], arg_type='d')
    msg = msg.build()
    sc_client.send(msg)
    processing_client.send(msg)
    return(None)

def read_data(_arduino_, _synth_):
    with _arduino_:
        while True:
            try:
                line = _arduino_.readline()
                if not line:
                    continue
                values = line.decode('ascii', errors='replace').split('\'')
                data = np.fromstring(values[0], sep=',', count = 6)
                print(data)
                send_msg(data, _synth_)
            except ValueError:
                warnings.warn("Line {} didn't parse, skipping".format(line))
            except KeyboardInterrupt:
                print("Exiting")
                break
    return(None)

read_data(arduino, synth1)
