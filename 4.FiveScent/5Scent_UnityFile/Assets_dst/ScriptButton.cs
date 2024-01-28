using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;



public class ScriptButton : MonoBehaviour
{
    public GameObject creditPanel;
    // Start is called before the first frame update
    void Start()
    {
        creditPanel.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void startgame()
    {
        SceneManager.LoadScene(1);
    }

    public void exitgame()
    {
        Application.Quit();
        Debug.Log("��������");
    }

    public void CreditShow()
    {
        creditPanel.SetActive(true);
        Debug.Log("Ȱ��ȭ");
    }
    public void CreditClose()
    {
        creditPanel.SetActive(false);
    }
}
