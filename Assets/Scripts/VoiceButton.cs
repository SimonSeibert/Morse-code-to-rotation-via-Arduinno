using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Windows.Speech;

public class VoiceButton : MonoBehaviour
{
    public bool movePlanchetteAfterTalking;
    public MovePlanchette planchette;
    public ArduinoCommunicator arduinoCommunicator;

    private Button b;
    private Text bText;

    private DictationRecognizer dictation;


    void Start()
    {
        b = GetComponent<Button>();
        bText = GetComponentInChildren<Text>();
        b.onClick.AddListener(click);
    }

    /// <summary>
    /// When the button is clicked it the voice recognition is started and the button is not interactable anymore until you said your voice line
    /// </summary>
    private void click()
    {
        startDictator();
        bText.text = "Waiting for your message . . .";
        b.interactable = false;
    }

    /// <summary>
    /// Converts a normal string into a hexadecimal string
    /// </summary>
    /// <param name="message">message to convert to string</param>
    /// <returns></returns>
    private string convertToHex(string message)
    {
        string hexMessage = "";
        char[] messageAsChars = message.ToCharArray();
        for (int i = 0; i < messageAsChars.Length; i++)
        {
            char currentChar = messageAsChars[i];

            if (currentChar == 'A')
            {
                hexMessage += "41_";
            }
            else if (currentChar == 'B')
            {
                hexMessage += "42_";
            }
            else if (currentChar == 'C')
            {
                hexMessage += "43_";
            }
            else if (currentChar == 'D')
            {
                hexMessage += "44_";
            }
            else if (currentChar == 'E')
            {
                hexMessage += "45_";
            }
            else if (currentChar == 'F')
            {
                hexMessage += "46_";
            }
            else if (currentChar == 'G')
            {
                hexMessage += "47_";
            }
            else if (currentChar == 'H')
            {
                hexMessage += "48_";
            }
            else if (currentChar == 'I')
            {
                hexMessage += "49_";
            }
            else if (currentChar == 'J')
            {
                hexMessage += "4A_";
            }
            else if (currentChar == 'K')
            {
                hexMessage += "4B_";
            }
            else if (currentChar == 'L')
            {
                hexMessage += "4C_";
            }
            else if (currentChar == 'M')
            {
                hexMessage += "4D_";
            }
            else if (currentChar == 'N')
            {
                hexMessage += "4E_";
            }
            else if (currentChar == 'O')
            {
                hexMessage += "4F_";
            }
            else if (currentChar == 'P')
            {
                hexMessage += "50_";
            }
            else if (currentChar == 'Q')
            {
                hexMessage += "51_";
            }
            else if (currentChar == 'R')
            {
                hexMessage += "52_";
            }
            else if (currentChar == 'S')
            {
                hexMessage += "53_";
            }
            else if (currentChar == 'T')
            {
                hexMessage += "54_";
            }
            else if (currentChar == 'U')
            {
                hexMessage += "55_";
            }
            else if (currentChar == 'V')
            {
                hexMessage += "56_";
            }
            else if (currentChar == 'W')
            {
                hexMessage += "57_";
            }
            else if (currentChar == 'X')
            {
                hexMessage += "58_";
            }
            else if (currentChar == 'Y')
            {
                hexMessage += "59_";
            }
            else if (currentChar == 'Z')
            {
                hexMessage += "5A_";
            }
            else if (currentChar == '1')
            {
                hexMessage += "31_";
            }
            else if (currentChar == '2')
            {
                hexMessage += "32_";
            }
            else if (currentChar == '3')
            {
                hexMessage += "33_";
            }
            else if (currentChar == '4')
            {
                hexMessage += "34_";
            }
            else if (currentChar == '5')
            {
                hexMessage += "35_";
            }
            else if (currentChar == '6')
            {
                hexMessage += "36_";
            }
            else if (currentChar == '7')
            {
                hexMessage += "37_";
            }
            else if (currentChar == '8')
            {
                hexMessage += "38_";
            }
            else if (currentChar == '9')
            {
                hexMessage += "39_";
            }
            else if (currentChar == '0')
            {
                hexMessage += "30_";
            }
            else if (currentChar == '?')
            {
                hexMessage += "3f_";
            }
            else if (currentChar == ' ')
            {
                hexMessage += "20_";
            }
            else
            {
                Debug.LogWarning("Received a char which can't be converted to hex");
            }
        }
        return hexMessage += ".";
    }

    /// <summary>
    /// Close the voice recognition when the application is closed
    /// </summary>
    private void OnApplicationQuit()
    {
        closeDictator();
    }

    /// <summary>
    /// Gets the result of speech recognition and sends it as hexa to the Arduino
    /// </summary>
    /// <param name="text">Result of text to speech as a string</param>
    /// <param name="confidence">Confidence Level of the result, we don't need that</param>
    private void dictationResult(string _text, ConfidenceLevel confidence)
    {
        //Convert the text to upper case
        string text = _text.ToUpper();
        //Result of the voice recognition
        Debug.Log("Dictation result: " + text);
        //Convert the text into Hexadecimal
        string hexMessage = convertToHex(text);
        //Result of the conversion
        Debug.Log("HexString: " + hexMessage);
        //Send hexa string to Arduino
        //arduinoCommunicator.sendMessageToArdu(hexMessage);
        //Move planchette if it is enabled
        if (movePlanchetteAfterTalking) planchette.moveToMultiple(planchette.messageToPositions(hexMessage));
        //Send message to serial monitor so arduino can rotate
        arduinoCommunicator.sendMessageToArdu(hexMessage);
        //Enable the button again for a new voice message
        enableButton();
    }

    /// <summary>
    /// Closes the voice recognition and enables the button again
    /// </summary>
    private void enableButton()
    {
        closeDictator();
        bText.text = "Speak with the spirit";
        b.interactable = true;
    }

    /// <summary>
    /// Voice recognition can sometimes throw an error which will be logged
    /// </summary>
    /// <param name="error">Error Message</param>
    /// <param name="ignore">This method needs a second int parameter to work, I don't know its use but we don't need it anyway</param>
    private void dictationError(string error, int ignore)
    {
        Debug.LogWarning("Dictation error: " + error);
    }

    /// <summary>
    /// Starts the voice recognition
    /// </summary>
    public void startDictator()
    {
        dictation = new DictationRecognizer();
        //Write the result in the 'dictationResult' string
        dictation.DictationResult += dictationResult;
        //Write errors in the 'dictationError' string
        dictation.DictationError += dictationError;
        //Start the voice recognition
        dictation.Start();
    }

    /// <summary>
    /// Closes the voice recognition
    /// </summary>
    public void closeDictator()
    {
        if (dictation != null)
        {
            //Remove the strings from the result and error
            dictation.DictationResult -= dictationResult;
            dictation.DictationError -= dictationError;
            //When voice recognition is running stop the session
            if (dictation.Status == SpeechSystemStatus.Running)
            {
                dictation.Stop();
            }
            //Stop the resources
            dictation.Dispose();
        }
    }
}
