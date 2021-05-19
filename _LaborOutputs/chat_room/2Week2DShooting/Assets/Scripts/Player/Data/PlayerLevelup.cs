using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerLevelup : MonoBehaviour
{
    #region �ӽ� ���� ���Ե� ������

    private const int MAXLEVEL = 10;

    private int   level = 1; // ���� ����
    private float size  = 1; // scale *= size;

    private bool _levelUp = false;
    public  bool IsLevelUp { get { return _levelUp; }
                             set { if (!value) _levelUp = value; } } // ���� �ϳ� ������Ű�� �뵵. �ܺο��� true ������ ����

    public           int[] expData   = new int[MAXLEVEL]; // ���� �䱸 ����ġ
    private readonly int[] reqExpArr = new int[MAXLEVEL]; // ���� ����ϴ� ����ġ Ȯ�� �迭

    public int curExp { get; set; } // ���� ����ġ


    #endregion


    void Start()
    {
        SetRequireExp();
    }

    
    void Update()
    {

#if UNITY_EDITOR
        if (Input.GetKeyDown(KeyCode.Space)) // �׽�Ʈ��
        {
            LevelUp();
        }
#else
        LevelUp();
#endif

    }

    void LevelUp()
    {
        if (level == MAXLEVEL) return;

        if(curExp >= reqExpArr[level])
        {
            _levelUp = true;
            ++level;
            SizeUp();
        }
    }

    void SizeUp()
    {
        size = 1.0f + level / 50.0f; // ���� �����ϰ� ���ĸ�����
        this.gameObject.transform.localScale *= size;
    }

    void SetRequireExp()
    {
        for(int idx = 0; idx < MAXLEVEL; ++idx)
        {
            reqExpArr[idx] = expData[idx];
        }
    }
}
