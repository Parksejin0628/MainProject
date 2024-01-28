using UnityEngine;
using UnityEngine.EventSystems;

public class Uidrag2 : MonoBehaviour, IPointerDownHandler, IDragHandler, IPointerUpHandler
{
    public GameObject Stage2end;
    void awake()
    {
        Stage2end.SetActive(false);
    }

    void start()
    {
        Debug.Log("�����");

    }
    void Update()
    {
        if (setcount2 == 1)
        {
            Stage2end.SetActive(true);
            Debug.Log("2132313");
        }
    }
    private static int setcount2 = 0;
    [Header("�̵��� �� UI ���")]
    [SerializeField] private Transform mMoveUiTarget;

    [Header("������ UI ���")]
    [SerializeField] private Transform mMergeUiTarget;

    private Vector2 mOriginPos; // �̵��� ������ ����� ��ġ
    private Vector2 mOriginMousePos; // �̵��� ������ ����� ���콺 ��ġ
    private Vector2 mMovedPos; // �̵��� �Ÿ�

    private CursorLockMode mPrevCursorLockMode; // �̵� ������ Ŀ�� ���

    // ���콺 �巡�� �ߴ�
    private void StopDrag()
    {
        Cursor.lockState = mPrevCursorLockMode;
    }

    // ���콺�� �̰��� Ŭ���Ǿ��ٸ� ���� ��ġ�� ����
    public void OnPointerDown(PointerEventData eventData)
    {
        // Ŀ�� �ɼ��� Confined �����Ͽ� ȭ�� ���� ������ ���ϰ� ��
        mPrevCursorLockMode = Cursor.lockState;
        Cursor.lockState = CursorLockMode.Confined;

        // ��ġ�� ����
        mOriginPos = mMoveUiTarget.position;
        mOriginMousePos = eventData.position;

        // Ʈ�������� ���̾��Ű ��ġ�� �� �Ʒ�(�ֻ��)���� ��ġ
        mMoveUiTarget.SetAsLastSibling();
    }

    // �巡�� �̵�
    public void OnDrag(PointerEventData eventData)
    {
        // �̺�Ʈ�ý����� ��ġ�� ù ���콺 ��ġ�� �� ��Ÿ ���� ���������ϴ� ��ġ��
        mMovedPos = eventData.position - mOriginMousePos;

        // Ʈ�������� ��ġ�� �ʱ� ��ġ + ��Ÿ��
        mMoveUiTarget.position = mOriginPos + mMovedPos;
    }

    // ���콺 Ŭ�� ���� �� �̵��� UI�� ��Ҵ��� Ȯ��
    public void OnPointerUp(PointerEventData eventData)
    {
        // �̵��� UI�� ��Ҵ��� Ȯ��
        if (Vector2.Distance(mMoveUiTarget.position, mMergeUiTarget.position) <= 50f)
        {
            // �̵��� UI�� ��ġ�� �̵�
            mMoveUiTarget.position = mMergeUiTarget.position;

            // ������ UI ��Ҹ� �ٸ� UI ��ҷ� ��ü
            mMoveUiTarget = mMergeUiTarget;

            setcount2++;
            Debug.Log(setcount2);

        }

        StopDrag();
    }
}
