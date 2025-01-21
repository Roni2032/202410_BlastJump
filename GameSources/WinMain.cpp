
#include "stdafx.h"
#include "Project.h"

using namespace basecross;


// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

//�萔
const wchar_t* pClassName = L"BlastJump";
const wchar_t* pWndTitle = L"BlastJump";
//�E�B���h�E���[�h�̎��̕��ƍ���
int g_ClientWidth = 1280;
int g_ClientHeight = 800;


//--------------------------------------------------------------------------------------
//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
//--------------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON1);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = pClassName;
	wcex.hIconSm = LoadIcon(wcex.hInstance, (LPCTSTR)IDI_ICON1);
	return RegisterClassEx(&wcex);
}

//--------------------------------------------------------------------------------------
//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//--------------------------------------------------------------------------------------
HWND InitInstance(HINSTANCE hInstance, int nCmdShow, bool isFullScreen, int iClientWidth, int iClientHeight)
{

	HWND hWnd = 0;
	// �E�B���h�E�̍쐬
	if (isFullScreen) {
		// �t���X�N���[��
		//�{�[�_�[���X�E�C���h�E���g�p
		iClientWidth = GetSystemMetrics(SM_CXSCREEN);
		iClientHeight = GetSystemMetrics(SM_CYSCREEN);
		hWnd = CreateWindow(
			pClassName,			// �o�^����Ă���N���X��
			pWndTitle,			// �E�C���h�E��
			WS_POPUP,			// �E�C���h�E�X�^�C���i�|�b�v�A�b�v�E�C���h�E���쐬�j
			0,					// �E�C���h�E�̉������̈ʒu
			0,					// �E�C���h�E�̏c�����̈ʒu
			iClientWidth,		// �t���X�N���[���E�C���h�E�̕�
			iClientHeight,		// �t���X�N���[���E�C���h�E�̍���
			nullptr,				// �e�E�C���h�E�̃n���h���i�Ȃ��j
			nullptr,				// ���j���[��q�E�C���h�E�̃n���h��
			hInstance,			// �A�v���P�[�V�����C���X�^���X�̃n���h��
			nullptr				// �E�C���h�E�̍쐬�f�[�^
		);
		if (!hWnd) {
			//���s����
			MessageBox(nullptr, L"�E�C���h�E�쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
			return 0;   //�G���[�I��
		}
	}
	else {
		//�E�C���h�E�̃T�C�Y����
		RECT rc = { 0, 0, iClientWidth, iClientHeight };
		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		//�E�C���h�E�̍쐬
		hWnd = CreateWindow(
			pClassName,				// �o�^����Ă���N���X��
			pWndTitle,				// �E�C���h�E��
			WS_OVERLAPPEDWINDOW,	// �E�C���h�E�X�^�C���i�I�[�o�[���b�v�E�C���h�E���쐬�j
			CW_USEDEFAULT,			//�ʒu��Windows�ɔC����
			CW_USEDEFAULT,			//�ʒu��Windows�ɔC����
			rc.right - rc.left,		//���w��
			rc.bottom - rc.top,		//�����w��
			nullptr,					// �e�E�C���h�E�̃n���h���i�Ȃ��j
			nullptr,					// ���j���[��q�E�C���h�E�̃n���h��
			hInstance,				// �A�v���P�[�V�����C���X�^���X�̃n���h��
			nullptr					// �E�C���h�E�̍쐬�f�[�^
		);
		if (!hWnd) {
			//���s����
			MessageBox(nullptr, L"�E�C���h�E�쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
			return 0;  //�G���[�I��
		}
	}
	ShowCursor(FALSE);
	//�E�C���h�E�̕\��
	ShowWindow(
		hWnd,       //�擾�����E�C���h�E�̃n���h��
		nCmdShow    //WinMain�ɓn���ꂽ�p�����[�^
	);
	UpdateWindow(hWnd);
	return hWnd;
}

//--------------------------------------------------------------------------------------
//	int MainLoop(HINSTANCE hInstance, HWND hWnd, bool isFullScreen, int iClientWidth, int iClientHeight);
//	�p�r: ���C�����[�v
//--------------------------------------------------------------------------------------
int MainLoop(HINSTANCE hInstance, HWND hWnd, bool isFullScreen, int iClientWidth, int iClientHeight) {
	//�I���R�[�h
	int RetCode = 0;
	//�E�C���h�E���B���b�Z�[�W�{�b�N�X�\���`�F�b�N�Ɏg�p
	WINDOWINFO WinInfo;
	ZeroMemory(&WinInfo, sizeof(WinInfo));
	//��O�����J�n
	try {
		//COM�̏�����
		//�T�E���h�ȂǂŎg�p����
		if (FAILED(::CoInitialize(nullptr))) {
			// ���������s
			throw exception("Com�������Ɏ��s���܂����B");
		}
		////�A�v���P�[�V�����N���X�̍\�z
		App::CreateApp(hInstance, hWnd, isFullScreen, iClientWidth, iClientHeight);
		//�V�[���̍쐬
		//�߂�l��ScenePtr�͔ėp�I�Ɏg����
		auto ScenePtr = App::GetApp()->CreateScene<Scene>();
		//���b�Z�[�W���[�v
		MSG msg = { 0 };
		//�L�[�{�[�h���͗p
		//�����ɐݒ肵���L�[�{�[�h���͂𓾂�
		vector<DWORD> UseKeyVec = {
			VK_PRIOR,VK_NEXT,VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT,VK_SPACE,
			VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_LCONTROL,
			'W','A','S','D','X','B','Z'
		};
		while (WM_QUIT != msg.message) {
			if (!App::GetApp()->ResetInputState(hWnd, UseKeyVec)) {
				//�L�[��Ԃ������Ȃ���΃E�C���h�E���b�Z�[�W�𓾂�
				if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
					//�L�[�{�[�h�ƃ}�E�X��Ԃ����Z�b�g
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			//�X�V�`�揈��
			App::GetApp()->UpdateDraw(1);
		}
		//msg.wParam�ɂ͏I���R�[�h�������Ă���
		RetCode = (int)msg.wParam;
	}
	catch (BaseException& e) {
		if (GetWindowInfo(hWnd, &WinInfo)) {
			//���s���s����
			MessageBox(hWnd, e.what_w().c_str(), L"�G���[", MB_OK);
		}
		else {
			//���s���s����
			MessageBox(nullptr, e.what_w().c_str(), L"�G���[", MB_OK);
		}
		RetCode = 1;
	}
	catch (BaseMBException& e) {
		//�}���`�o�C�g�o�[�W�����̃��b�Z�[�W�{�b�N�X���Ă�
		if (GetWindowInfo(hWnd, &WinInfo)) {
			//���s���s����
			MessageBoxA(hWnd, e.what_m().c_str(), "�G���[", MB_OK);
		}
		else {
			//���s���s����
			MessageBoxA(nullptr, e.what_m().c_str(), "�G���[", MB_OK);
		}
		RetCode = 1;
	}
	catch (exception& e) {
		//STL�G���[
		//�}���`�o�C�g�o�[�W�����̃��b�Z�[�W�{�b�N�X���Ă�
		if (GetWindowInfo(hWnd, &WinInfo)) {
			MessageBoxA(hWnd, e.what(), "�G���[", MB_OK);
		}
		else {
			MessageBoxA(nullptr, e.what(), "�G���[", MB_OK);
		}
		RetCode = 1;
	}
	catch (...) {
		//�����s�����s����
		if (GetWindowInfo(hWnd, &WinInfo)) {
			MessageBox(hWnd, L"�����s���̃G���[�ł�", L"�G���[", MB_OK);
		}
		else {
			MessageBox(nullptr, L"�����s���̃G���[�ł�", L"�G���[", MB_OK);
		}
		RetCode = 1;
	}
	//�A�v���P�[�V�����̍폜
	App::DeleteApp();
	//��O�����I��
	//COM�̃����[�X
	::CoUninitialize();
	return RetCode;
}


//--------------------------------------------------------------------------------------
//	int APIENTRY _tWinMain();
//	�p�r: �G���g���|�C���g
//--------------------------------------------------------------------------------------
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// �f�o�b�O���Adelete����̃`�F�b�N�p
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//���P�[���̐ݒ�
	setlocale(LC_ALL, "JPN");

	// �t���X�N���[���ɂ��邩�ǂ����̔���
	// �R�}���h���C����/f���ݒ肳��Ă�����t���X�N���[���ɂ���
	bool isFullScreen = true;
	wstring wstrcmd = lpCmdLine;
	if (wstrcmd == L"/f" || wstrcmd == L"/F") {
		isFullScreen = true;     // �t���O��true�ɐݒ�
	}

	MyRegisterClass(hInstance);
	// �A�v���P�[�V�����̏����������s���܂�:
	HWND hWnd = InitInstance(hInstance, nCmdShow, isFullScreen, g_ClientWidth, g_ClientHeight);

	if (!hWnd)
	{
		return FALSE;
	}

	return  MainLoop(hInstance, hWnd, isFullScreen, g_ClientWidth, g_ClientHeight);

}

//--------------------------------------------------------------------------------------
//
//  �֐�: MakeWindowModeRectFunc()
//
//  �ړI: �E�C���h�E���[�h�Ɉڍs�����`���쐬����
//
//--------------------------------------------------------------------------------------
void MakeWindowModeRectFunc(RECT& rc) {
	rc = { 0, 0, g_ClientWidth, g_ClientHeight };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	int CXWidth = GetSystemMetrics(SM_CXSCREEN);
	int CYHeight = GetSystemMetrics(SM_CYSCREEN);
	int RCWidth = rc.right - rc.left;
	int RCHeight = rc.bottom - rc.top;
	int OffsetLeft = CXWidth / 2 - RCWidth / 2;
	int OffsetTop = CYHeight / 2 - RCHeight / 2;
	OffsetRect(&rc, OffsetLeft, OffsetTop);
}

//--------------------------------------------------------------------------------------
//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:    ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
//
//--------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		// �L�[�������ꂽ
		switch (wParam) {
		case VK_ESCAPE:
			//�E�C���h�E��j������
			DestroyWindow(hWnd);
			break;
		case VK_RETURN:
			if (GetAsyncKeyState(VK_CONTROL)) {
				//Ctrl+Enter�Ń��[�h�ؑ�
				if (App::AppCheck()) {
					if (App::GetApp()->IsFullScreen()) {
						//�E�C���h�E���[�h�Ɉڍs
						RECT rc;
						MakeWindowModeRectFunc(rc);
						App::GetApp()->SetWindowMode(rc);
					}
					else {
						App::GetApp()->SetFullScreenMode();
					}
				}
			}
			break;
		}
		break;
	case WM_SIZE:
		if (App::AppCheck()) {
			App::GetApp()->OnSize();
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}



