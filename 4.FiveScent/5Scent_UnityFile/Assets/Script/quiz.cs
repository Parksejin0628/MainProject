using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Collections.Generic;
using UnityEngine;

public class WirePuzzleGame : MonoBehaviour
{
    private GameObject start;

    private GameObject end;

    private List<Vector2Int> wireConnections = new List<Vector2Int>();

    // ������ �׸��� �Լ�
    private void DrawWire(Vector2Int position)
    {
        wireConnections.Add(position);
    }

    // ������ ���� �ִ��� Ȯ���ϴ� �Լ�
    private bool IsWireLoopClosed()
    {
        if (wireConnections.Count < 2)
        {
            return false;
        }

        // ���� ������ �� ���� ��
        return wireConnections[0] == wireConnections[wireConnections.Count - 1];
    }

    // ���� ���� ���¸� Ȯ���Ͽ� �¸� ������ �˻��ϴ� �Լ�
    private bool CheckWinCondition()
    {
        // ���� ���� ���¿� ���� ���� ���� ���θ� Ȯ���ϴ� �ڵ带 �ۼ��ؾ� �մϴ�.
        // ���� ���, ��� �׸��� ���� �������� ����Ǿ� �ִ��� �˻��մϴ�.
        // ���� ���¸� ����ϴ� �迭 ���� ����Ͽ� �����մϴ�.

        return false; // �¸� ������ �������� �ʴ� ���
    }

    // ���� �׸��� �� ���� ���� �˻� ����
    private void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Vector2 mousePosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            Vector2Int gridPosition = new Vector2Int(Mathf.RoundToInt(mousePosition.x), Mathf.RoundToInt(mousePosition.y));

            DrawWire(gridPosition);

            if (IsWireLoopClosed())
            {
                if (CheckWinCondition())
                {
                    // ���� �¸� ó��
                    Debug.Log("You Win!");
                }
                else
                {
                    // ������ ��� �����մϴ�.
                }
            }
        }
    }
}