import atexit
import time
import argparse

import Adafruit_BluefruitLE
from Adafruit_BluefruitLE.services import UART


parser = argparse.ArgumentParser()
parser.add_argument('--name', required=True, help="The name of the bluetooth device to connect to.")
args = parser.parse_args()

# Get the BLE provider for the current platform.
ble = Adafruit_BluefruitLE.get_provider()

def main():
    
    adapter = ble.get_default_adapter()
    adapter.power_on()
    print('Using adapter: {0}'.format(adapter.name))

    adapter.start_scan()

    atexit.register(adapter.stop_scan)

    device_found = False
    device = None
    
    print('Searching for UART devices...')
    while not device_found:
        found = set(UART.find_devices())
        for d in found:
            print ('Found UART: {0} [{1}]'.format(d.name, d.id))
            if d.name == args.name:
                device = d
                device_found = True
                break
        time.sleep(1)
    
    if device_found:
        print('connecting to: {0} [{1}]'.format(device.name, device.id))
        device.connect()
        try:
            UART.discover(device)
            uart = UART(device)
            uart.write(b'Hello world!\r\n')
            received = uart.read(timeout_sec=60)
            if received is not None:
                print('Received: {0}'.format(received))
            else:
                print('Received no data!')
        finally:
            device.disconnect()
    


ble.initialize()
ble.run_mainloop_with(main)