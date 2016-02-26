package com.example.totalcontrol;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import java.util.ArrayList;

import android.util.Log;
import android.widget.Toast;

public class SocketForAccept extends Thread {

	private int port;  //최초 클래스 생성시에만 세팅해주면 됨
	public static DatagramSocket socket;  //클래스간에 공유할수 있도록 static 선언함.
	private DatagramPacket receiver; 
	private DatagramPacket sender;
	private static int addressTop;
	private static int portTop;
	private static int pcNameTop;
	private static int macAddressTop;
	private static int pcSizeXTop;
	private static int pcSizeYTop;
	private static int synchronizeFlagTop;
	public byte[] buff;  //버퍼는 값이 계속 달라지므로 static안함
	
	public static InetAddress[] address;
	public static int[] portForReceiveSend;  //클라이언트들의 port를 저장
	public static String[] pcName;  //클라이언트들의 이름을 저장
	public static String[] macAddress;  //클라이언트들의 mac주소를 저장
	public static int[] pcSizeX;  //클라이언트들의 모니터 수평사이즈를 저장
	public static int[] pcSizeY;  //클라이언트들의 모니터 수직사이즈를 저장
	public static int[] synchronizeFlag;  //MouseKeyboardInputActivity에서 안드로이드 액정사이즈와 클라이언트PC의 모니터 사이즈를 동기화 시켰는지 여부를 판별할때 사용할 필드
	
	
	public SocketForAccept() {   //MainActivity이외의 클래스에서 호출하는 생성자
		buff = new byte[160];
	}

	
	public SocketForAccept(int port,int second) throws SocketException  //MainActibity에서 Launch버튼을 두번이상 눌렸을 때 호출되는 생성자
	{
		this.port = port;
		socket = new DatagramSocket(this.port);
	}
	public SocketForAccept(int port) throws SocketException  {   //이건 최초로 소켓생성할때 사용하는 생성자 port값을 넘겨줘야한다.
		this.port = port;
		socket = new DatagramSocket(this.port);
		
		address=new InetAddress[5];
		pcName=new String[5];
		macAddress=new String[5];
		pcSizeX=new int[5];
		pcSizeY=new int[5];
		synchronizeFlag=new int[5];
		addressTop=0;
		portTop=0;
		pcNameTop=0;
		macAddressTop=0;
		pcSizeXTop=0;
		pcSizeYTop=0;
		synchronizeFlagTop=0;
		portForReceiveSend=new int[5];
		
	}

	public void closeSocket()  //쓰레드,소켓닫는 메소드
	{
		this.interrupt();
		socket.close();
	}
	
	public static ArrayList<String> returnPcNameArrayList()  //pc이름들 리턴하는 메소드
	{
		ArrayList<String> str =new ArrayList<String>();
		
		for(int i=0;i<pcNameTop;i++)
		{
			str.add(pcName[i]);
		}
		return str;
		
	}
	
	public void run()
	{
		while (!this.isInterrupted()) {  //인터럽트가 있으면 멈춘다.
			receiver = new DatagramPacket(buff, buff.length); //수신용 Datagram선언
			try {
				socket.receive(receiver);  //수신받는다.
				int flag = 0;
				for (int i = 0; i < addressTop; i++) {  //이미 address배열에 있는 값인지 조사한다.
					if (address[i] == receiver.getAddress()) {
						flag = 1;
						Log.i("수신", "이미있는값");
						break;
					}
				}
				if (flag == 0) {  //없는값이면 방금 들어온 클라이언트의 정보를 각 정보를 담는 배열들에 담아준다.
					address[addressTop++] = receiver.getAddress();
					portForReceiveSend[portTop++] = receiver.getPort();
					sender= new DatagramPacket(buff, buff.length,receiver.getAddress(),receiver.getPort());
					
					String str=new String(buff);
					String temp;
					pcName[pcNameTop++]=str.split("_")[0];
					macAddress[macAddressTop++]=str.split("_")[1];
					temp=str.split("_")[2];
					
					pcSizeX[pcSizeXTop]=temp.getBytes()[0]*100;
					pcSizeX[pcSizeXTop++]+=temp.getBytes()[1];
					temp=str.split("_")[3];
					
					pcSizeY[pcSizeYTop] = temp.getBytes()[0]*100;
					pcSizeY[pcSizeYTop++] +=temp.getBytes()[1];
					synchronizeFlag[synchronizeFlagTop++]=0;
					socket.send(sender);
					Log.i("수신", String.valueOf(pcNameTop-1)+"수신성공"+","+pcName[pcNameTop-1]+","+macAddress[macAddressTop-1]+","+String.valueOf(pcSizeX[pcSizeXTop-1])+","+String.valueOf(pcSizeY[pcSizeYTop-1]));
				}

			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				Log.i("수신", "수신실패");
			}
		}
	}
	
}