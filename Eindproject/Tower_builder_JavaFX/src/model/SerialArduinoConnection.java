package model;

import com.fazecast.jSerialComm.SerialPort;

/**
 * Vincent Verboven
 * 16/05/2023
 */
public class SerialArduinoConnection {

    public static final int ARDUINO_PORT = 0;
    private final SerialPort arduinoPort;

    public SerialArduinoConnection() {
        for (SerialPort port : SerialPort.getCommPorts()) {
            System.out.println(port.toString());
        }
        arduinoPort = SerialPort.getCommPorts()[ARDUINO_PORT];
        boolean result = arduinoPort.openPort();
        System.out.println(result ? "Port opened!" : "Port closed!");
    }

    public byte[] receiveBytes(){
        byte[] newData = new byte[arduinoPort.bytesAvailable()];
        arduinoPort.readBytes(newData, newData.length);
        System.out.print("Receiving data from Arduino:");
        for (byte newDatum : newData) {
            System.out.printf("%c",(char)newDatum);
        }
        System.out.println();
        return newData;
    }

}
