using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    private Rigidbody2D rigid;
    private Vector2 vec;
    private Vector3 mousePos;
    public GameObject testObj;

    [Header("�̵� ���� ����")]
    public float speed = 5;

    private void Start()
    {
        rigid = GetComponent<Rigidbody2D>();
        vec = new Vector2();
    }

    private void Update()
    {
        Move();
        Rotation();
    }

    void Move()
    {
        vec.Set(GameManager.instance.pi.xMove * speed, GameManager.instance.pi.yMove * speed);
        rigid.velocity = vec;
    }

    void Rotation()
    {
        mousePos = Camera.main.ScreenToWorldPoint(Input.mousePosition);         // ���콺 �������� ���� ī�޶� �������� �ٲٰ� ���� ���������� ü���� �آZ��
        Vector3 v = transform.position - mousePos;                              // �÷��̾�� ���콺�� ��ġ�� ���� ������ �Ÿ��� ����
        float r = Mathf.Atan2(v.y, v.x) * Mathf.Rad2Deg;                        // AngleAxis�� ���ؼ� ������ ���Ѵ�
        transform.rotation = Quaternion.AngleAxis(r, Vector3.forward);          // ���� ���� ��ŭ z���� ������ �ش�
        testObj.transform.position = mousePos;                                  // Gizmo�� Scene�� ���̰� �ϴ� �� ( ����� �뵵 �ڵ忡�� )
    }
}
