/*********************************************************************
*                SEGGER MICROCONTROLLER SYSTEME GmbH                 *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller Systeme GmbH        *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

***** emWin - Graphical user interface for embedded applications *****
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : App.c
Purpose     : Simple demo drawing "Hello world"
----------------------------------------------------------------------
*/

#include "DIALOG.h"
#include "main.h"

#include <stm32f429i_discovery_gyroscope.h>
#include "../Components/i3g4250d/i3g4250d.h"

/*********************************************************************
*
*       Defines de FrameWinMoranDLG.c para modificar los elementos de la ventana.
*
**********************************************************************
*/
#define ID_FRAMEWIN_0            (GUI_ID_USER + 0x00)
#define ID_TEXT_0            (GUI_ID_USER + 0x01)
#define ID_TEXT_1            (GUI_ID_USER + 0x02)
#define ID_SLIDER_0            (GUI_ID_USER + 0x03)
#define ID_SLIDER_1            (GUI_ID_USER + 0x04)
#define ID_TEXT_2            (GUI_ID_USER + 0x05)
#define ID_TEXT_3            (GUI_ID_USER + 0x06)
#define ID_TEXT_4            (GUI_ID_USER + 0x07)
#define ID_TEXT_5            (GUI_ID_USER + 0x08)
#define ID_TEXT_6            (GUI_ID_USER + 0x0A)
#define ID_TEXT_7            (GUI_ID_USER + 0x0B)
#define ID_TEXT_8            (GUI_ID_USER + 0x0C)
#define ID_TEXT_9            (GUI_ID_USER + 0x0D)
#define ID_TEXT_10            (GUI_ID_USER + 0x0E)

WM_HWIN CreateFrameWinMoran(void);	//Prototipado de la funci�n del Framewin

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void MainTask(void) {
	/* Use memory devices on all windows to avoid flicker */
	WM_SetCreateFlags(WM_CF_MEMDEV);
	CreateFrameWinMoran();
	WM_HWIN hItem;

	// La lectura del giroscopio es velocidad angular en grados sobre segundo.
	float velocidad_angular_XYZ[3] = { 0.0, 0.0, 0.0 };
	// Aqui se almacenara la posicion angular en grados.
	float posicion_angular_XYZ[3] = { 0.0, 0.0, 0.0 };
	// Este es un iterador recorrer los arreglos anteriores.
	int eje = 0;

	while (1) {
		// Delay de 400ms
		GUI_Delay(400);

		// Solo se comenzara a modificar la ventana cuando esta ya sea creada.
		if (seInicializoLaVentana) {
			// Se lee el sensor y se almacena en el arreglo
			BSP_GYRO_GetXYZ(velocidad_angular_XYZ);

			// Integracion de la velocidad angular parar obtener la posicion angular.
			// (se multiplicar por el tiempo transcurrido desde la ultima vez que se paso por aqui)
			// en este caso corresponde al GUI_Delay(400) es decir, 400ms -> 0.4s.
			for (eje = 0; eje < 2; eje++) {
				posicion_angular_XYZ[eje] += (velocidad_angular_XYZ[eje]/1000.0) * 0.4;
			}

			// Se escribe el valor en el slide para el eje X.
			hItem = WM_GetDialogItem(hItem_global, ID_SLIDER_0);
			SLIDER_SetRange(hItem, -180, 180);
			SLIDER_SetValue(hItem, (int)posicion_angular_XYZ[0]);

			// Se escribe el valor en el slide para el eje Y.
			hItem = WM_GetDialogItem(hItem_global, ID_SLIDER_1);
			SLIDER_SetRange(hItem, -180, 180);
			SLIDER_SetValue(hItem, (int)posicion_angular_XYZ[1]);
		}
	}
}

/*************************** End of file ****************************/
