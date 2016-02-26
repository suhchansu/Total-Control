package com.example.totalcontrol;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.SocketException;

import android.app.Activity;
import android.content.Intent;
import android.content.ReceiverCallNotAllowedException;
import android.util.Log;
import android.widget.Toast;

public class LaunchButton extends Activity{
	
	private static int firstSocketCreateFlag;  //소켓을 몇번째 만드는건지 알리는 플래그  0이면 최초로 만듦 ,1이면 처음만드는게 아님
	private static int postSocketPort;  //이전에 소켓생성할때 썼던 포트번호를 저장하고 있음(다음번에 다시 서버를 열때 이전에 포트번호랑 같은지 판단하기 위함)
	private Socket socket;  //서버열기용 소켓클래스
	private MainActivity parent;  //부모클래스(36번줄에 Intent를 생성할때 MainActivity의 context가 필요해서 끌고왔음) 
	private int port;  //소켓생성을 위한 포트번호
	private Intent nextActivity;  //다음 페이지를 저장할 intent
	private boolean checkPort;  //checkInputPort메소드에서 리턴하는 값
	
	
	public LaunchButton(MainActivity parent) {
		this.parent = parent;  //부모클래스(MainActivity)를 저장함.
		checkPort = true;  //세팅은 true로 

		if (firstSocketCreateFlag == 0) {  //최초에는 여기로 들어온다.
			try {
				port = Integer.parseInt(this.parent.editText.getText()
						.toString());  //부모클래스(MainActivity)에서 얻어온 포트를 저장한다.
				socket = new Socket(port);  //얻어온 포트로 소켓생성
				firstSocketCreateFlag = 1;  //다음번엔 이쪽 분기로 안들어오도록 1로 변경한다.
				postSocketPort = port;  //현재포트를 과거포트에 넣는다.
				nextActivity = new Intent(parent.getApplicationContext(),
						MouseKeyboardInputActivity.class);  //이까지 성공하면 부모클래스의 context를 이용해서 MouseKeyboardInputActivity클래스를 다음에 열릴 페이지로 만들어준다.
			} catch (SocketException e) {
				Toast.makeText(parent.getApplicationContext(), "소켓생성실패", 500) 
						.show();  //소켓생성이 실패하면 MainActivity 에서 "소켓생성실패"라는 Toast메세지가 뜬다.
				// socket.closeSocket();
				checkPort = false;//소켓생성실패라는것을 입력한다.
			} catch (Exception e) {
				// e.printStackTrace();
				Toast.makeText(parent.getApplicationContext(), "값을 입력해주세요.",
						500).show();  //포트값이 입력이 안되있으면 "값을 입력해주세요"toast메세지가 뜬다.
				checkPort = false;  //포트입력이 없다는 것을 알리는 플래그를 false로 한다.
			}
			Log.i("첫번째 버튼클래스", "버튼클래스 작업 완료");
		} else {  //launch버튼을 최초로 누른게 아닐때
				try {
					port = Integer.parseInt(this.parent.editText.getText()
							.toString());  //똑같이 포트번호를 저장한다.
					if(port==postSocketPort)  //최초 또는 이전에 MainActivity에서 받아왔던 포트번호랑 같은지 비교한다.
					{
						SocketForAccept.socket.close();  //포트가 같으면 이전에 만들어놨던 소켓을 종료하고
						socket = new Socket(port,1);  //같은 포트로 새로 만든다.(생성자의 인자값이 최초에 소켓을 만들때와 다르다.)
						nextActivity = new Intent(parent.getApplicationContext(),
								MouseKeyboardInputActivity.class);  //다음에 띄울 액티비티를 만들어주고 끝
					
						Log.i("두번째 같은 버튼클래스", "버튼클래스 작업 완료");
					}
					else  //만약에 Launch버튼을 최초로 누른게 아니면서 이전 포트값 현재 포트값이 다른경우
					{
						SocketForAccept.socket.close();   //이전 소켓을 종료한다.
						socket = new Socket(port);  //소켓을 아주 새로 만든다.
						postSocketPort = port;  //현재포트를 과거포트로 만든다.
						nextActivity = new Intent(parent.getApplicationContext(),
								MouseKeyboardInputActivity.class);  //다음에 떠야할 액티비티를 만든다. 끝
						Log.i("두번째 다른 첫번째 버튼클래스", "버튼클래스 작업 완료");
					}
				} catch (SocketException e) {
					Toast.makeText(parent.getApplicationContext(), "소켓생성실패", 500)
							.show();
					// socket.closeSocket();
					checkPort = false;
				} catch (Exception e) {
					// e.printStackTrace();
					Toast.makeText(parent.getApplicationContext(), "값을 입력해주세요.",
							500).show();
					checkPort = false;
				}
		}
	}

	public Intent getNextActivity()  //MainActivity 에서 다음에 띄울 액티비티가 어떤건지 알아가기위해 호출하는 메소드
	{
		return nextActivity;
	}
	
	public boolean checkInputPort()  //서버생성과 포트입력이 성공했는지 확인하기 위해서 MainActivity에서 호출하는 메소드
	{
		return checkPort;
	}
}
