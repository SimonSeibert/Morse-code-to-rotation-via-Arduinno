using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePlanchette : MonoBehaviour
{
    [Tooltip("Time the planchette needs to move between hexa numbers")]
    public float moveTime = 1f;
    [Tooltip("Positions of all hexa numbers")]
    public Transform pos_a, pos_b, pos_c, pos_d, pos_e, pos_f, pos_0, pos_1, pos_2, pos_3, pos_4, pos_5, pos_6, pos_7, pos_8, pos_9;

    private Transform targetTmp; // Current target of the planchette

    void Start()
    {
        targetTmp = transform; //At the beginning the planchette targets itself -> it doesn't move 
        moveToMultiple(messageToPositions("AF042B"));
    }

    void Update()
    {
        // Planchette always moves to it's target in a smooth way
        transform.position = Vector3.Lerp(transform.position, targetTmp.position, (moveTime + 2f) * Time.deltaTime);
    }

    /// <summary>
    /// Moves the planchette to multiple targets
    /// </summary>
    /// <param name="positions"></param>
    public void moveToMultiple(Transform[] positions)
    {
        for (int i = 0; i < positions.Length; i++)
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
