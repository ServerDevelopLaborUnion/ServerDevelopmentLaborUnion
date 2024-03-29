using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ChatManager : MonoBehaviour
{
    public static ChatManager instance = null;
    public RectTransform chatContent;
    public GameObject msgPrefab;

    public InputField txtMsg;
    public AudioClip clip;

    GameObject[] zotZemuns;
    private List<ChatDataObject> chatList = new List<ChatDataObject>();

    void Awake(){
        
        instance = this;
        //for (int i = 0; i < transform.GetChild(1).childCount; i++)
        //{
        //    zotZemuns[i] = transform.GetChild(1).GetChild(i).gameObject;
        //}
    }
    
    public void AddMessage(string payload)
    {
        chatList.Add(new ChatDataObject(payload));
    }

    void Update(){
        // 인스턴스를 만드는 작업은 메인 쓰레드에서 이루어져야한다. 소켓 쓰레드에서 생성시 유니티가 생성을 막는다.
        //메시지큐 리스트에 있는 애들을 인스턴시에이트 해준다.
        foreach(ChatDataObject obj in chatList){
            AudioSource a = PoolManager.instance.GetOrCreate();
            a.clip = clip;
            a.Play();
            StartCoroutine(DisableAudio(a));

            GameObject chatMsg = Instantiate(msgPrefab, Vector3.zero, Quaternion.identity) as GameObject;
            ChatMsg chatScript = chatMsg.GetComponent<ChatMsg>();
            if(chatScript != null){
                chatScript.SetData(obj.sender, obj.msg);
            }
            chatMsg.transform.SetParent(chatContent);
        }
        chatList.Clear(); 
    }

    public void SendBtnClick()
    {
        SocketClient.instance.SendData(txtMsg.text);
    }

    IEnumerator DisableAudio(AudioSource a)
    {
        yield return new WaitForSeconds(2f);
        a.gameObject.SetActive(false);
    }
}
