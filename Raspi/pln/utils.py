import time
from .loggers import Log
from .board_config import BOARD
from .loraSetup import LoRa
import json
import re
import base64


class Utils:
    messages = []
    idLora = "9901"
    idSlaveLora = ["3392972", "1345560", "1344944", "12583644", "1345072"]
    # idSlaveLora = ["1345560"]

    @staticmethod
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            Log.info("Terhubung ke broker MQTT!")
            print("Terhubung ke broker MQTT!")
        else:
            print(f"Gagal terhubung, kode error {rc}")
            Log.info(f"Gagal terhubung, kode error {rc}")

    @staticmethod
    def on_publish(client, userdata, mid):
        # print(f"Data berhasil dikirim dengan id pesan: {mid}")
        Log.info(f"Data berhasil dikirim dengan id pesan: {mid}")

    @staticmethod
    def receive_callback():
        BOARD.receiveLed(True)
        # Log.info()
        # time.sleep(3)

    @staticmethod
    def cek_status_lora():
        status = LoRa.status()
        if status == LoRa.STATUS_CRC_ERR:
            print("CRC error")
            Log.error("CRC error")
        elif status == LoRa.STATUS_HEADER_ERR:
            print("Packet header error")
            Log.error("Packet header error")

    @staticmethod
    def extract_json_string(input_string):
        match = re.search(r'\{.*\}', input_string)
        if match:
            json_str = match.group(0)
            try:
                data = json.loads(json_str)
                return data
            except json.JSONDecodeError:
                print("Invalid Json")
        print("No JSON found")

    @staticmethod
    def encodePayload(data):
        encoded_data = base64.b64encode(data.encode('utf-8'))
        encoded_str = encoded_data.decode('utf-8')
        return encoded_str

    @staticmethod
    def readMessage():
        try:
            piece = ""
            code = LoRa.read()
            packetIndex = LoRa.read()
            totalPackets = LoRa.read()
            while LoRa.available() > 1:
                piece += chr(LoRa.read())
            Utils.messages.append(piece)

            Utils.cek_status_lora()

            if (packetIndex == totalPackets):
                message = "".join(Utils.messages)
                Utils.messages = []
                print(f"message {message}")
                decoded_64 = base64.b64decode(message)
                decode_str = decoded_64.decode()
                return {
                    "packetIndex": packetIndex,
                    "totalPackets": totalPackets,
                    "message": Utils.extract_json_string(decode_str),
                    "rssi": LoRa.packetRssi(),
                    "snr": LoRa.snr()
                }

            return {
                "packetIndex": packetIndex or None,
                "totalPackets": totalPackets or None,
                "message": None,
                "rssi": LoRa.packetRssi() or None,
                "snr": LoRa.snr() or None
            }

        except Exception as e:
            # print(f"An error occurredd : {e}")
            Log.error(f"error getting message Lora : {e}")
