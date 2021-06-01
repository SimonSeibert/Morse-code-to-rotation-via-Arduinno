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
        Transform[] pos =
        {
            pos_a, pos_3, pos_b, pos_f, pos_d, pos_e, pos_c, pos_0, pos_1, pos_2, pos_9, pos_4, pos_5, pos_6, pos_7, pos_8
        };
        moveToMultiple(pos);
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
}
