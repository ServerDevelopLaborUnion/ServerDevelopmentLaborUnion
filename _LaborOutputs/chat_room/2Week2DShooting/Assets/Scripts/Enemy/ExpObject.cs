using UnityEngine;

public class ExpObject : MonoBehaviour
{

    [SerializeField]
    private int hp = 5;

    private void Start()
    {
        
    }

    private void OnEnable()
    {
        hp = 5;
        //���߿� hp�ٰ� ����ٸ� ���⼭�ʱ�ȭ���ش�.
    }

    private void OnCollisionEnter2D(Collision2D other)
    {
        if(other.gameObject.CompareTag("PLAYER")) //�±״� �ӽ÷� ���� ���÷��̾�� �صξ���. ���߿� �ҷ����� �ٲٸ�����.
        {
            hp--;
            if(hp <= 0)
            {
                ExpPoolManager.instance.InsertQueue(gameObject);
                GameManager.instance.playerLevelup.curExp += 10;
            }
        }
        else if(other.gameObject.CompareTag("ENEMY")) //��ġ�� �ٽ� �����ǰ� �س��µ� �Ƹ��� ���߿� �ٲܵ�..?
        {
            ExpPoolManager.instance.InsertQueue(gameObject);
        }
    }

}
