using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.GlobalIllumination;

public class MovePlanchette : MonoBehaviour
{
    public new Light light;
    [Tooltip("Speed at which planchette moves to hexa numbers")]
    [Header("Don't change value, doesn't work dynamicly yet")]
    public float moveTime = 2f;
    [Tooltip("Positions of all hexa numbers")]
    public Transform pos_a, pos_b, pos_c, pos_d, pos_e, pos_f, pos_0, pos_1, pos_2, pos_3, pos_4, pos_5, pos_6, pos_7, pos_8, pos_9;

    private Transform targetTmp; // Current target of the planchette

    private bool lightOn = false; //Keeps track if the light should turn on or of
    private float lightStep = 10; //How fast should the light turn on/off

    void Start()
    {
        targetTmp = transform; //At the beginning the planchette targets itself -> it doesn't move 
        //moveToMultiple(messageToPositions("A2F743"));
    }

    void Update()
    {
        // Planchette always moves to it's target in a smooth way
        transform.position = Vector3.Lerp(transform.position, targetTmp.position, (moveTime + 2f) * Time.deltaTime);

        // Change between on/off state of the light smoothly
        if(lightOn)
        {
            light.intensity += lightStep * Time.deltaTime;
        } else {
            light.intensity -= lightStep * Time.deltaTime;
        }
    }

    /// <summary>
    /// Moves the planchette to multiple targets
    /// </summary>
    /// <param name="positions"></param>
    public void moveToMultiple(Transform[] positions)
    {
        //Get number of hexa letters that the planchette has to travel to
        int length = positions.Length;
        //Explanation in "blinkLight" function. Start a bit before first number is reached, blink length-times for 1 second
        StartCoroutine("blinkLight", ((float) .75f, (float) length, (float) .5, (float) 1.5));
        for (int i = 0; i < length; i++)
        {
            // The delay is calculated in a way so the planchette starts moving to the hexa numbers one after another
            StartCoroutine("moveTo", (positions[i], i * moveTime));
        }
    }

    /// <summary>
    /// Moves the planchette to a target after a specified delay
    /// </summary>
    /// <param name="parameter">Transform is the new target, float is the delay after which the movement will start</param>
    /// <returns></returns>
    IEnumerator moveTo((Transform, float) parameter)
    {
        yield return new WaitForSeconds(parameter.Item2); // Waits a specified amount of time before moving
        targetTmp = parameter.Item1;
    }

    /// <summary>
    /// Flashes the light at specific timings with a specific delay and duration. Corutines can only recieve 1 parameter which is why everything is in a tupel
    /// </summary>
    /// <param name="parameter">
    /// 1st float: startDelay
    /// 2nd float: how many times it should blink
    /// 3rd float: Time when light turns on
    /// 4th float: Time when light turns off
    /// </param>
    /// <returns></returns>
    IEnumerator blinkLight((float, float, float, float) parameter)
    {
        //Start delay
        yield return new WaitForSeconds(parameter.Item1);   
        //Iterations = Number of Hexa numbers
        for (int i = 0; i < parameter.Item2; i++)
        {
            lightOn = true;
            yield return new WaitForSeconds(parameter.Item3);
            lightOn = false;
            yield return new WaitForSeconds(parameter.Item4);
        }
    }

    /// <summary>
    /// Gets a message and returns an array which contains the position of each char in the message
    /// </summary>
    /// <param name="message">Message for planchette</param>
    /// <returns></returns>
    public Transform[] messageToPositions(string message)
    {
        //List of positions which will be targeted by the planchette
        List<Transform> positions = new List<Transform>();

        // Go through each item in the received string and add the corresponding position to the list which will later be returned
        foreach (char item in message)
        {
            switch (item)
            {
                case '0':
                    positions.Add(pos_0);
                    break;
                case '1':
                    positions.Add(pos_1);
                    break;
                case '2':
                    positions.Add(pos_2);
                    break;
                case '3':
                    positions.Add(pos_3);
                    break;
                case '4':
                    positions.Add(pos_4);
                    break;
                case '5':
                    positions.Add(pos_5);
                    break;
                case '6':
                    positions.Add(pos_6);
                    break;
                case '7':
                    positions.Add(pos_7);
                    break;
                case '8':
                    positions.Add(pos_8);
                    break;
                case '9':
                    positions.Add(pos_9);
                    break;
                case ('A'):
                case ('a'):
                    positions.Add(pos_a);
                    break;
                case 'B':
                case ('b'):
                    positions.Add(pos_b);
                    break;
                case 'C':
                case ('c'):
                    positions.Add(pos_c);
                    break;
                case 'D':
                case ('d'):
                    positions.Add(pos_d);
                    break;
                case 'E':
                case ('e'):
                    positions.Add(pos_e);
                    break;
                case 'F':
                case ('f'):
                    positions.Add(pos_f);
                    break;
                default:
                    Debug.LogWarning("WARNING: Received a hexa numver which isn't covered in switch case");
                    break;
            }
        }

        // Return the list as an array
        return positions.ToArray();
    }
}
