using System.Collections;
using System.IO.Ports;
using UnityEngine;

public class ArduinoCommunicator : MonoBehaviour
{
    public int comPort = 4;
    public int baudRate = 19200;
    public MovePlanchette move;

    SerialPort serial;
    string receivedString;

    void Start()
    {
        setup();
    }

    void Update()
    {
        //By pressing "1" you can receive a message from the Arduino
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            receiveMessageFromArdu();
        }
        //By pressing "2" you can send a message from the Arduino
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            sendMessageToArdu("blink\n");
        }
    }

    /// <summary>
    /// Close the serial port so it can be used again by an other application
    /// </summary>
    private void OnApplicationQuit()
    {
        serial.Close();
    }

    /// <summary>
    /// Read from the serial port and log the message
    /// </summary>
    void receiveMessageFromArdu()
    {
        receivedString = serial.ReadLine();
        Debug.Log(receivedString);
    }

    /// <summary>
    /// Write a message in the serial port which the Arduino can read
    /// </summary>
    /// <param name="s">Message you want to send</param>
    void sendMessageToArdu(string s)
    {
        serial.Write(s);
    }

    /// <summary>
    /// Connects to the specified serial port
    /// </summary>
    void setup()
    {
        //Defina a new serial port with the com port and baud rate
        serial = new SerialPort("COM" + comPort, baudRate);

        //Small timeout between read accesses
        serial.ReadTimeout = 16;

        //If the port isn't open -> open it
        if (serial.IsOpen == false)
        {
            serial.Open();
            Debug.Log("opening COM" + comPort + "...");
        }
        else
        {
            Debug.Log("COM" + comPort + " is already open...");
        }

        //I somehow have to write something in the serial port so that the application doesn't crash...
        serial.NewLine = "\n";
        serial.Write("something" + "\n");
    }
}
