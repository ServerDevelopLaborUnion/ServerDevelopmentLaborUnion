using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// ���ͷ� �ִ밪���� �� �ø��� �ص�. 
/// �����ڷ� �ִ밪 ���� �� ����
/// </summary>
public class StatCount
{
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="maxValue">���� �ִ밪</param>
    public StatCount(byte maxValue = 5) { MAXVALUE = maxValue; }

    private readonly    byte MAXVALUE       = 5;
    private             byte _damage        = 0;
    private             byte _moveSpeed     = 0;
    private             byte _hpBoost       = 0;
    private             byte _hpRegen       = 0;
    private             byte _atkSpeed      = 0;
    private             byte _bulletSpeed   = 0;



    #region get set

    public byte damage          { get { return _damage; } 
                                  set { if (_damage < MAXVALUE)      { _damage += value; } }}

    public  byte moveSpeed      { get { return _moveSpeed; } 
                                  set { if (_moveSpeed < MAXVALUE)   { _moveSpeed += value; } }}

    public  byte hpBoost        { get { return _hpBoost; } 
                                  set { if (_hpBoost < MAXVALUE)     { _hpBoost += value; } }}

    public  byte hpRegen        { get { return _hpRegen; } 
                                  set { if (_hpRegen < MAXVALUE)     { _hpBoost += value; } }}

    public  byte atkSpeed       { get { return _atkSpeed; } 
                                  set { if (_atkSpeed < MAXVALUE)    { _atkSpeed += value; } }}

    public  byte bulletSpeed    { get { return _bulletSpeed; } 
                                  set { if (_bulletSpeed < MAXVALUE) { _bulletSpeed += value; } }}

    #endregion
};




public class PlayerStat : MonoBehaviour
{
    #region �ӽ� ����

    private StatCount     stat    = new StatCount();
    private PlayerLevelup player  = null;
    private int upgradeCount      = 0;
    

    #endregion



    void Start()
    {
        player = GetComponent(typeof(PlayerLevelup)) as PlayerLevelup; // �ع��� ¥�Ŵ�� �ѹ� �غ��� �;��� 
    }

    void Update()
    {
        AddUpgradeCount();
        StatUp();
    }


    void AddUpgradeCount()
    {
        if(player.IsLevelUp)
        {
            ++upgradeCount;
            player.IsLevelUp = false;
        }
    }

    void StatUp()
    {
        if (upgradeCount < 1) return;
        --upgradeCount;


        // TODO : Ȯ���� �ٲ�� �ϴ� �ڵ���
        // ���� ���߿��� ��ư�� ������ �ϴ�
        // �Ḹ �̰� ���� ������ �ϴ°ǰ�
        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            ++stat.damage;
            Debug.Log($"stat.damage: {stat.damage}");
        }
        else if(Input.GetKeyDown(KeyCode.Alpha2))
        {
            ++stat.atkSpeed;
            Debug.Log($"stat.atkSpeed: {stat.atkSpeed}");
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3))
        {
            ++stat.hpBoost;
            Debug.Log($"stat.hpBoost: {stat.hpBoost}");
        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            ++stat.hpRegen;
            Debug.Log($"stat.hpRegen: {stat.hpRegen}");
        }
        else if (Input.GetKeyDown(KeyCode.Alpha5))
        {
            ++stat.moveSpeed;
            Debug.Log($"stat.moveSpeed: {stat.moveSpeed}");
        }
        else if (Input.GetKeyDown(KeyCode.Alpha6))
        {
            ++stat.bulletSpeed;
            Debug.Log($"stat.bulletSpeed: {stat.bulletSpeed}");
        }

    }
}
