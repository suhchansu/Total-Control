package com.example.totalcontrol;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnGenericMotionListener;
import android.widget.TextView;

@SuppressLint("NewApi")
public class MouseKeyboardInputActivity extends Activity implements
		OnGenericMotionListener, android.view.View.OnKeyListener {

	public View view;
	private Socket socket;
	
	private long posta;
	private long valueLong;
	private float valueFloat;
	private float postValueFloat;
	private int []pressingKey;
	
	private int controlIndex;
	
	private float[] varXY;
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_mousekeyboardinput);
		view = (View) findViewById(R.id.mousekeyboarinputLayout);
		view.setFocusable(true);
		view.setOnGenericMotionListener(this);
		view.setOnKeyListener(this);
		pressingKey=new int[3];
		socket = new Socket();
		socket.start();
		varXY=new float[2];
		synchronizeXY(0);
		Log.i("마우스 키보드 인식 엑티비티", "초기화 완료");
	}
	
	public void synchronizeXY(int index)
	{
		int [] XY=new int[2];
		controlIndex=index;
		if(socket.socketforaccept.pcSizeX[index]!=0 && socket.socketforaccept.pcSizeX!=null && socket.socketforaccept.pcSizeY[index]!=0 && socket.socketforaccept.pcSizeY!=null  && view.getWidth()!=0 && view.getHeight()!=0)
		{
			XY[0]=socket.socketforaccept.pcSizeX[index];
			XY[1]=socket.socketforaccept.pcSizeY[index];
			
			varXY[0]=(socket.socketforaccept.pcSizeX[index]/view.getWidth())+1;
			varXY[1]=(socket.socketforaccept.pcSizeY[index]/view.getHeight())+1;
			if(varXY[0]==0)
			{
				varXY[0]=1;
			}
			if(varXY[1]==0)
			{
				varXY[1]=1;	
			}
		}
		else
		{
			varXY[0]=1;
			varXY[1]=1;		
		}
	}

	// 마우스 이벤트 처리
	@SuppressLint("NewApi")
	@Override
	public boolean onGenericMotion(View v, MotionEvent event) { //마우스 이벤트 (프로토콜 첫번째 인자 0==마우스 1==키보드, 두번째 인자 값전달 셋째 인자 0==좌클릭 1==우클릭 3==휠클릭 4==휠이동  0==마우스 이동 
		// TODO Auto-generated method stub
		if (event.getToolType(0) == MotionEvent.TOOL_TYPE_MOUSE) {
			float x = event.getAxisValue(MotionEvent.AXIS_X);
			float y = event.getAxisValue(MotionEvent.AXIS_Y);
			
			String str;
			int clickFlag = 0;
			
			if(socket.socketforaccept.synchronizeFlag[controlIndex]==0)
			{
				synchronizeXY(controlIndex);
				socket.socketforaccept.synchronizeFlag[controlIndex]=1;
			}
	
			
			switch (event.getButtonState()) {
			case MotionEvent.BUTTON_SECONDARY: // 우클릭
				Log.i("Right Click",
						"(" + String.valueOf(x)+"*"+String.valueOf(varXY[0])+"="+String.valueOf(x*varXY[0]) + "," + String.valueOf(y)+"*"+String.valueOf(varXY[1])+"="+ String.valueOf(y*varXY[1]) + ")"
								+ "Right Click");
				str = "0 " + String.valueOf(x*varXY[0]) + " " + String.valueOf(y*varXY[1]) + " "
						+ "2\0";
				socket.index = controlIndex;
				socket.buff = str.getBytes();
				socket.flag = 0;
				clickFlag = 1;
				break;
			case MotionEvent.BUTTON_TERTIARY: // 휠 클릭
				Log.i("Wheel Click",
						"(" + String.valueOf(x)+"*"+String.valueOf(varXY[0])+"="+String.valueOf(x*varXY[0]) + "," + String.valueOf(y)+"*"+String.valueOf(varXY[1])+"="+ String.valueOf(y*varXY[1]) + ")"
								+"Wheel Click");
				str = "0 " + String.valueOf(x*varXY[0]) + " " + String.valueOf(y*varXY[1]) + " "
						+ "3\0";
				socket.index = controlIndex;
				socket.buff = str.getBytes();
				socket.flag = 0;
				clickFlag = 1;
				break;
			}
			if (clickFlag == 0) {
				if ((valueLong=event.getDownTime())!=posta) {  //좌클릭
					Log.i("Left Click",
							"(" + String.valueOf(x)+"*"+String.valueOf(varXY[0])+"="+String.valueOf(x*varXY[0]) + "," + String.valueOf(y)+"*"+String.valueOf(varXY[1])+"="+ String.valueOf(y*varXY[1]) + ")"
									+ "Left Click");
					str = "0 " + String.valueOf(x*varXY[0]) + " " + String.valueOf(y*varXY[1])
							+ " " + "1\0";
					socket.index = controlIndex;
					socket.buff = str.getBytes();
					socket.flag = 0;
					clickFlag = 1;
					posta=valueLong;
				}
			}
			
			if (clickFlag == 0) {
				if ((valueFloat = event.getAxisValue(MotionEvent.AXIS_VSCROLL)) != 0) {  //상하 휠이동
					Log.i("Wheel move", String.valueOf(valueFloat));
					str = "0 " + String.valueOf(valueFloat) + " 0 " + "4\0";
					socket.index = controlIndex;
					socket.buff = str.getBytes();
					socket.flag = 0;
					clickFlag = 1;
				}
			}

			if (clickFlag == 0) {   //이동
				Log.i("Mouse move", "(" + String.valueOf(x)+"*"+String.valueOf(varXY[0])+"="+String.valueOf(x*varXY[0]) + "," + String.valueOf(y)+"*"+String.valueOf(varXY[1])+"="+ String.valueOf(y*varXY[1]) + ")");
				str = "0 " + String.valueOf(x*varXY[0]) + " " + String.valueOf(y*varXY[1]) + " "
						+ "0\0";
				socket.index = controlIndex;
				socket.buff = str.getBytes();
				socket.flag = 0;
			}

		}
		return false;
	}

	@Override
	public boolean onKey(View v, int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub
		String str;
		int scanCode = event.getScanCode();
		int keycode = keyCode;
		
		if(socket.socketforaccept.synchronizeFlag[controlIndex]==0)
		{
			synchronizeXY(controlIndex);
			socket.socketforaccept.synchronizeFlag[controlIndex]=1;
		}

		if (pressingKey[0] == 1 && pressingKey[1] == 1) {
			if (scanCode == 2 || scanCode == 3 || scanCode == 4
					|| scanCode == 5 || scanCode == 6) {
				synchronizeXY(scanCode-2);
				Log.i("controlConvert", String.valueOf(controlIndex)+"으로 전환");
			}

			else {
				switch (event.getAction()) {
				case KeyEvent.ACTION_DOWN: // 누를때
					Log.i("down",
							String.valueOf(event.getScanCode() + ","
									+ String.valueOf(keycode)));

					switch (scanCode) {
					case 29:
						pressingKey[0] = 1;
						break;
					case 42:
						pressingKey[1] = 1;
						break;
					}

					str = "1 " + String.valueOf(scanCode) + " 1 " + "0\0";
					socket.index = controlIndex;
					socket.buff = str.getBytes();
					socket.flag = 0;
					break;
				case KeyEvent.ACTION_UP: // 땔때
					Log.i("up",
							String.valueOf(event.getScanCode() + ","
									+ String.valueOf(keycode)));

					switch (scanCode) {
					case 29:
						pressingKey[0] = 0;
						break;
					case 42:
						pressingKey[1] = 0;
						break;
					}

					str = "1 " + String.valueOf(scanCode) + " 0 " + "0\0";
					socket.index = controlIndex;
					socket.buff = str.getBytes();
					socket.flag = 0;
					break;

				}
			}
		} else {
			switch (event.getAction()) {
			case KeyEvent.ACTION_DOWN: // 누를때
				Log.i("Keyboard down",
						String.valueOf(event.getScanCode() + ","
								+ String.valueOf(keycode)));

				switch (scanCode) {
				case 29:
					pressingKey[0] = 1;
					break;
				case 42:
					pressingKey[1] = 1;
					break;
				}

				str = "1 " + String.valueOf(scanCode) + " 1 " + "0\0";
				socket.index = controlIndex;
				socket.buff = str.getBytes();
				socket.flag = 0;
				break;
			case KeyEvent.ACTION_UP: // 땔때
				Log.i("Keyboard up",
						String.valueOf(event.getScanCode() + ","
								+ String.valueOf(keycode)));

				switch (scanCode) {
				case 29:
					pressingKey[0] = 0;
					break;
				case 42:
					pressingKey[1] = 0;
					break;
				}

				str = "1 " + String.valueOf(scanCode) + " 0 " + "0\0";
				socket.index = controlIndex;
				socket.buff = str.getBytes();
				socket.flag = 0;
				break;

			}
		}
		return false;
		
	}

}
