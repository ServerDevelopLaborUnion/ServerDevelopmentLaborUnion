using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerRPC : MonoBehaviour
{
    private PlayerInput playerInput;
    private PlayerMove playerMove;
    private bool isPlayer = true;

    private Coroutine sendCoroutine;
    private WaitForSeconds ws = new WaitForSeconds(1/60); //고정프레임간격으로 패킷전송

    void Awake()
    {
        playerInput = GetComponent<PlayerInput>();
        playerMove = GetComponent<PlayerMove>();
        
    }

    void Start(){
        if(isPlayer)
            sendCoroutine = StartCoroutine(SendData()); 
    }

    public void SetRemote(){
        playerInput.enabled = false;
        playerMove.enabled = false;
        isPlayer = false; //플레이가 아닌 것으로 설정
        
        if(sendCoroutine != null)
            StopCoroutine(sendCoroutine); //플레이어가 아닐경우 데이터를 받을 필요 없으니 꺼준다.
    }

    public void SetTransform(Vector3 position, Vector3 rotation)
    {
        transform.position = position;
        transform.rotation = Quaternion.Euler(rotation);
    }

    IEnumerator SendData(){
        int myId = GameManager.instance.myId;
        while(true){
            yield return ws;
            TransformVO vo = new TransformVO(myId, transform.position, transform.rotation.eulerAngles);
            string payload = JsonUtility.ToJson(vo);

            DataVO dataVO = new DataVO();
            dataVO.type = "Transform";
            dataVO.payload = payload;
            SocketClient.instance.SendData(JsonUtility.ToJson(dataVO)); //json으로 변경해서 전송
        }
    }
}
