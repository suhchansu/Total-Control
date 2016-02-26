package com.example.totalcontrol;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.SocketException;

import android.util.Log;

public class Socket extends Thread {
	
	public SocketForAccept socketforaccept;  //클라이언트들 수신을 위한 클래스
	private DatagramPacket sender;  //송신을 위한 Datagram
	public int index;  //송신할 PC선정용 인덱스변수
	public int flag;  //flag가 0일때 송신한다.
	public byte[] buff;  //전송용 버퍼
	
	public Socket()  //MainActivity를 제외하고 나머지 클래스들이 socket이 필요할때 호출해야되는 생성자
	{
		socketforaccept=new SocketForAccept();  //수신용 클래스 생성
		Log.i("소켓", "리시브소켓초기화완료");
		socketforaccept.start();  //전송 쓰레스 시작
		Log.i("소켓", "쓰레드 동작중");
		flag=1;  //플래그 1로 초기화해서 전송안되게 만듦
	}
	
	public Socket(int port,int second) throws SocketException   //소켓이 같은 포트로 만들어 질때 호출해야되는 생성자
	{
		socketforaccept=new SocketForAccept(port,1);  //SocketForAccept클래스에게 이전번과 같은 포트로 소켓이 생성된다고 알림
		Log.i("소켓", "리시브소켓생성완료");
	}
	
	public Socket(int port) throws SocketException  //  포트번호가 이전번호랑 다를때나 최초로 socket이 생성될때 호출해야되는 생성자
	{
		socketforaccept=new SocketForAccept(port);  //수신용 socket을 최초로 만듦
		Log.i("소켓", "리시브소켓생성완료");
	}
	public void run()  //송신부 쓰레드
 {
		while (!this.isInterrupted()) {  //flag가 0일때 송신하고  현재 클래스에 어떠한 interrㅕpt가 걸리면 자동으로 멈춘다.
			if (flag == 0) {
				send(buff, index);  //송신함수 호출
				flag = 1;
			}
		}
	}
	public void send(byte[] buff,int index)   //socketforaccept 클래스가 가지고 있는 클라이언트 pc들의 정보를 기반으로 데이터를 송신한다.
	{
		if (socketforaccept.address[index] != null
				&& socketforaccept.portForReceiveSend[index] != 0) {  //socketforaccept에 채워지지 않은 인덱스들을 참조하면 안되므로 방어하기 위한 코드
			sender = new DatagramPacket(buff, buff.length,  //전송할 데이터와 데이터길이
					socketforaccept.address[index],  //클라이언트 pc ip주소
					socketforaccept.portForReceiveSend[index]);  //클라이언트 pc port번호
			try {
				socketforaccept.socket.send(sender);  //전송!!!
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	public void closeSocket()
	{
		this.interrupt();
		socketforaccept.closeSocket();
	}
	
}
