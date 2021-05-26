using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePlanchette : MonoBehaviour
{
    public float moveTime = 1f;
    public Transform pos_a, pos_b, pos_c, pos_d, pos_e, pos_f, pos_0, pos_1, pos_2, pos_3, pos_4, pos_5, pos_6, pos_7, pos_8, pos_9;
    private Transform targetTmp;

    void Start()
    {
        targetTmp = transform;
        Transform[] pos =
        {
            pos_a, pos_3, pos_b, pos_f, pos_d, pos_e, pos_c, pos_0, pos_1, pos_2, pos_9, pos_4, pos_5, pos_6, pos_7, pos_8
        };
        moveToMultiple(pos);
    }

    void Update()
    {
        transform.position = Vector3.Lerp(transform.position, targetTmp.position, (moveTime + 2f) * Time.deltaTime);
    }

    public void moveToMultiple(Transform[] positions)
    {
        for (int i = 0; i < positions.Length; i++)
        {
            StartCoroutine("moveTo", (positions[i], i * moveTime));
        }
    }

    IEnumerator moveTo((Transform, float) parameter)
    {
        yield return new WaitForSeconds(parameter.Item2);
        targetTmp = parameter.Item1;
    }
}
