using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class stroya : MonoBehaviour
{
    public Text textUI;
    public string[] texts; // �ؽ�Ʈ �迭

    private int currentIndex; // ���� �ε���

    void Start()
    {
        currentIndex = 0; // �ʱ� �ε��� ����
        UpdateText(); // �ؽ�Ʈ ������Ʈ
    }

    void Update()
    {
        // �����̽��ٸ� ������ ���� �ؽ�Ʈ�� ������Ʈ
        if (Input.GetKeyDown(KeyCode.Space))
        {
            currentIndex++;
            UpdateText();
        }
    }

    // �ؽ�Ʈ ������Ʈ �Լ�
    void UpdateText()
    {
        if (currentIndex < texts.Length)
        {
            textUI.text = texts[currentIndex];
        }
        else
        {
            textUI.text = "End of Texts";
        }
    }
}

