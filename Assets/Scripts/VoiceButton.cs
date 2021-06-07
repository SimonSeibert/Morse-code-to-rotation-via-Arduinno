using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Windows.Speech;

public class VoiceButton : MonoBehaviour
{
    private Button b;
    private Text bText;

    private DictationRecognizer dictation;

    private ArduinoCommunicator arduinoCommunicator;

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
        bText.text = "Waiting for your message...";
        b.interactable = false;
    }

    /// <summary>
    /// Converts a normal string into a hexadecimal string
    /// </summary>
    /// <param name="message">message to convert to string</param>
    /// <returns></returns>
    private string convertToHex(string message)
    {
        // Convert the string into bytes
        byte[] ba = Encoding.Default.GetBytes(message);
        // Converts into a string again but in hexa format
        string hexString = BitConverter.ToString(ba);
        // That result is going to return a string with dashes (-) in it so we need to do this to remove them
        hexString = hexString.Replace("-", "");
        return hexString;
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
    private void dictationResult(string text, ConfidenceLevel confidence)
    {
        //Result of the voice recognition
        Debug.Log("Dictation result: " + text);
        //Convert the text into Hexadecimal
        string hexMessage = convertToHex(text);
        //Result of the conversion
        Debug.Log("HexString: " + hexMessage);
        //Send hexa string to Arduino
        //arduinoCommunicator.sendMessageToArdu(hexMessage);
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
