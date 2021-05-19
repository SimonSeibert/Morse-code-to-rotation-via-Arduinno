using System.IO.Ports;
using UnityEngine;

public class ArduinoCommunicator : MonoBehaviour
{
    public int comPort = 4;
    SerialPort serial;
    string receivedString;

    void Start()
    {
        setup();
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            receiveMessageFromArdu();
        }
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            sendMessageToArdu();
        }
    }

    private void OnApplicationQuit()
    {
        serial.Close();
    }

    void receiveMessageFromArdu()
    {
        receivedString = serial.ReadLine();
        Debug.Log(receivedString);
    }

    void sendMessageToArdu()
    {
        serial.Write("blink\n");
    }

    void setup()
    {
        serial = new SerialPort("COM" + comPort, 19200);

        serial.ReadTimeout = 16;

        if (serial.IsOpen == false)
        {
            serial.Open();
            Debug.Log("opening COM" + comPort + "...");
        }
        else
        {
            Debug.Log("COM" + comPort + " is already open...");
        }

        serial.NewLine = "\n";
        serial.Write("something" + "\n");
    }
}
