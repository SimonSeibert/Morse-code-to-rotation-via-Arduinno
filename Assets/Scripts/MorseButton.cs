using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class MorseButton : MonoBehaviour, IPointerDownHandler, IPointerUpHandler
{
    private float downTimeStamp = float.MaxValue;
    private float upTimeStamp = float.MaxValue;
    private List<float> pressTimes = new List<float>();
    private List<float> releaseTimes = new List<float>();

    public void OnPointerDown(PointerEventData eventData)
    {
        downTimeStamp = Time.time;
        if (downTimeStamp != float.MaxValue && upTimeStamp != float.MaxValue)
        {
            releaseTimes.Add(downTimeStamp - upTimeStamp);
        }
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        upTimeStamp = Time.time;
        if (downTimeStamp != float.MaxValue && upTimeStamp != float.MaxValue)
        {
            pressTimes.Add(upTimeStamp - downTimeStamp);
        }
    }
}
