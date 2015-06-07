#include "Simulation.h"

#include <windows.h>
#include <tchar.h>

ATOM				RegisterWindowClass( HINSTANCE );
BOOL				InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WindowProc( HWND, UINT, WPARAM, LPARAM );
void				Update( DWORD );

HINSTANCE hInst;										// Текущий экземпляр
TCHAR szWindowTitle[] = _T( "Fishnet Simulation" );		// Текст строки заголовка
TCHAR szWindowClass[] = _T( "FishnetSimulation" );		// Имя класса главного окна

Simulation simulation( 10, 15, 1.0, 5000, 1.0, 5.0, Vector2D( 0, -9.81 ), 0.002 );

const int periodOfTimer = 8;
const double maxPossible_dt = 0.009;
const double slowMotionRatio = 1.0;

int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	MSG msg;

	// Регистрация нового класса окна
	RegisterWindowClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

//
//  ФУНКЦИЯ: RegisterWindowClass(HINSTANCE)
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM RegisterWindowClass( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WindowProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szWindowTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
	   CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WindowProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ: обрабатывает сообщения в главном окне.
//
LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hDC;
	static HPEN hPen;
	static HBRUSH hBrush;
	static int sx, sy;
	const int scale = 25;
	const int r = 3;
	static Node* nodePtr = nullptr;
	Vector2D position1, position2;
	const int numberOfRows = simulation.getNumberOfRows();
	const int numberOfColumns = simulation.getNumberOfColumns();
	POINTS p;

	switch ( message )
	{
	case WM_CREATE:
		SetTimer( hWnd, 1, periodOfTimer, NULL );
		hPen = CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
		hBrush = CreateSolidBrush( RGB( 0, 0, 0 ) );
		break;
	case WM_SIZE:
		sx = LOWORD( lParam );
		sy = HIWORD( lParam );
		break;
	case WM_PAINT:
		hDC = BeginPaint( hWnd, &ps );

        SetGraphicsMode( hDC, GM_ADVANCED );

        XFORM xForm;

        xForm.eM11 = 1.0F;
        xForm.eM12 = 0.0F;
        xForm.eM21 = 0.0F;
        xForm.eM22 = -1.0F;
        xForm.eDx  = 0.0F;
        xForm.eDy  = 0.0F;

        SetWorldTransform( hDC, &xForm );
		SetViewportOrgEx( hDC, sx / 2, sy / 2, NULL );

		SelectObject( hDC, hPen );
		SelectObject( hDC, hBrush );

		for ( int i = 0; i < numberOfRows; ++i )
		{
			for ( int j = 0; j < numberOfColumns; ++j )
			{
				position1 = simulation.getNode( i, j ).getPosition();

				if ( j != numberOfColumns - 1 && i != numberOfRows - 1 )
				{
					position2 = simulation.getNode( i, j + 1 ).getPosition();
					MoveToEx( hDC, position1.getX() * scale, 
						position1.getY() * scale, NULL );
					LineTo( hDC, position2.getX() * scale, 
						position2.getY() * scale );

					position2 = simulation.getNode( i + 1, j ).getPosition();
					MoveToEx( hDC, position1.getX() * scale, 
						position1.getY() * scale, NULL );
					LineTo( hDC, position2.getX() * scale, 
						position2.getY() * scale );
				}
				else if ( i == numberOfRows - 1 && j != numberOfColumns - 1 )
				{
					position2 = simulation.getNode( i, j + 1 ).getPosition();
					MoveToEx( hDC, position1.getX() * scale, 
						position1.getY() * scale, NULL );
					LineTo( hDC, position2.getX() * scale, 
						position2.getY() * scale );
				}
				else if ( j == numberOfColumns - 1 && i != numberOfRows - 1 )
				{
					position2 = simulation.getNode( i + 1, j ).getPosition();
					MoveToEx( hDC, position1.getX() * scale, 
						position1.getY() * scale, NULL );
					LineTo( hDC, position2.getX() * scale, 
						position2.getY() * scale );
				}
					
				Ellipse( hDC, position1.getX() * scale - r, 
					position1.getY() * scale - r, 
					position1.getX() * scale + r, 
					position1.getY() * scale + r );
			}
		}
		EndPaint( hWnd, &ps );
		break;
	case WM_LBUTTONDOWN:
        p = MAKEPOINTS( lParam );

		p.x -= sx / 2;
		p.y = sy - p.y - sy / 2;

		for ( int i = 0; i < simulation.getNumberOfRows(); ++i )
		{
			for ( int j = 0; j < simulation.getNumberOfColumns(); ++j )
			{
				position1 = simulation.getNode( i, j ).getPosition();

				if ( ( p.x > position1.getX() * scale - 4 * r ) && 
					( p.x < position1.getX() * scale + 4 * r ) &&
					( p.y > position1.getY() * scale - 4 * r ) && 
					( p.y < position1.getY() * scale + 4 * r ) )
				{
					if ( !nodePtr )
					{
						nodePtr = &simulation.getNode( i, j );
						nodePtr->fixNode();
					}
					break;
				}
			}
		}
		break;
	case WM_MOUSEMOVE:
		if ( nodePtr )
		{
			p = MAKEPOINTS( lParam );

		    p.x -= sx / 2;
		    p.y = sy - p.y - sy / 2;

			nodePtr->setPosition( Vector2D( ( double ) p.x / scale, 
				( double ) p.y / scale ) );
			InvalidateRect( hWnd, NULL, TRUE );
		}
		break;
	case WM_LBUTTONUP:
        if ( nodePtr )
		{
			nodePtr->releaseNode();
			nodePtr = nullptr;
		}
		break;
	case WM_TIMER:
		Update( periodOfTimer );
		InvalidateRect( hWnd, NULL, TRUE );
		break;
	case WM_DESTROY:
		KillTimer( hWnd, 1 );
		DeleteObject( hPen );
		DeleteObject( hBrush );
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}
	return 0;
}

void Update( DWORD ms )
{
	double dt = ms / 1000.0;

	dt /= slowMotionRatio;

  	int numOfIterations = ( int )( dt / maxPossible_dt ) + 1;
	if ( numOfIterations != 0 )
		dt = dt / numOfIterations;

	simulation.operate( dt );
}