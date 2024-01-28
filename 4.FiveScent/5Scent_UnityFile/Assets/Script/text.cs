using System.Collections.Generic;
using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class storya : MonoBehaviour
{
    public Text ChatText;
    public Text CharacterName;

    public string writerText = "";

    bool isButtonClicked = false;

    void Start()
    {
        StartCoroutine(TextPractice());
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space)) // �����̽��ٸ� ������ �� ��ư Ŭ������ ó��
        {
            isButtonClicked = true;
        }
    }

    IEnumerator NormalChat(string narrator, string narration)
    {
        CharacterName.text = narrator;
        writerText = "";

        for (int a = 0; a < narration.Length; a++)
        {
            writerText += narration[a];
            ChatText.text = writerText;
            yield return null;
        }

        while (true)
        {
            if (isButtonClicked)
            {
                isButtonClicked = false;
                break;
            }
            yield return null;
        }
    }

    IEnumerator TextPractice()
    {
        yield return StartCoroutine(NormalChat("ĳ����1", "�̰��� Ÿ���� ȿ���� ���� ���â�� �����ϴ� ����"));
        yield return StartCoroutine(NormalChat("ĳ����2", "�ȳ��ϼ���, �ݰ����ϴ�."));
    }
}
