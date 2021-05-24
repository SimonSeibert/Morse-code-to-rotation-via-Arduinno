using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePlanchette : MonoBehaviour
{
    public float moveTime = 1f;
    public Transform pos_a, pos_b, pos_c, pos_d, pos_e, pos_f, pos_0, pos_1, pos_2, pos_3, pos_4, pos_5, pos_6, pos_7, pos_8, pos_9;
    // Start is called before the first frame update
    void Start()
    {
        Transform[] pos =
        {
            pos_a, pos_3, pos_b, pos_f, pos_d, pos_e, pos_c, pos_0, pos_1, pos_2, pos_9, pos_4, pos_5, pos_6, pos_7, pos_8
        };
        moveToMultiple(pos);
    }

    // Update is called once per frame
    void Update()
    {

    }

    public void moveTo(Transform pos, float delay)
    {
        LeanTween.move(gameObject, pos, moveTime).setEaseInOutExpo().setDelay(delay);
    }

    public void moveToMultiple(Transform[] positions)
    {
        for (int i = 0; i < positions.Length; i++)
        {
            moveTo(positions[i], i * moveTime);
        }
    }
}
