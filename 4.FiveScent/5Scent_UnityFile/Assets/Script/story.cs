using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class story : MonoBehaviour
{
    public GameObject qa1;
    public Texture2D[] images;  // �̹��� �迭
    private int currentIndex = 0;  // ���� �̹��� �ε���
    public RawImage panel;  // �̹����� ǥ���� UI ���
    int a = 0;

    void Start()
    {
        // �̹��� �迭�� ����ִ� ��� ��� ���
        if (images.Length == 0)
        {
            Debug.LogWarning("Image array is empty!");
        }
        else
        {
            // UI ��� ã��
            panel = panel.GetComponent<RawImage>();

            // �ʱ� ��鿡 ù ��° �̹����� ǥ��
            DisplayImage(currentIndex);
        }
    }

    void Update()
    {
        // �����̽��ٸ� ������ ���� ������� �̵�
        if (Input.GetKeyDown(KeyCode.Space))
        {
            // ���� �ε����� ������Ű�� �迭 ������ �ʰ��ϴ� ��� 0���� �ǵ���
            currentIndex = (currentIndex + 1) % images.Length;
            DisplayImage(currentIndex);
            a++;
            Debug.Log(a);
        }
        if(a== 7)
        {
            SceneManager.LoadScene(2);
        }

        if(images.Length <4 && a == 3)
        {
            UnityEditor.EditorApplication.isPlaying = false;
            Application.Quit();
            
        }

    }

    void DisplayImage(int index)
    {
        // ���� �ε����� �ش��ϴ� �̹����� UI ��ҿ� ����
        panel.texture = images[index];

        Debug.Log("Displaying image: " + index);
    }
}
