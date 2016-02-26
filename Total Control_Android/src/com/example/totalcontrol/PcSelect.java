package com.example.totalcontrol;

import java.io.IOException;
import java.util.ArrayList;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

public class PcSelect extends Activity{
	
	private ArrayList<String> arraylistforlistview;  //SocketForAccept클래스에 있는 PC이름을 얻어오기 위한 ArrayList필드
	private ArrayAdapter<String> adapter;  //listView에 넣어줄 ArrayAdapter
	private ListView listview; //PC이름을 표현할 리스트뷰
	
	
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_pcselect);
		arraylistforlistview = new ArrayList<String>();  //pC이름을 담을 ArrayList를 만든다.				
		arraylistforlistview=SocketForAccept.returnPcNameArrayList();  //PC이름을 담는다.(returnPcNameArrayList()메소드가 pc이름들을 리턴해준다)
		adapter= new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_expandable_list_item_1,arraylistforlistview);  //listView에 넣어주기 위한 Adapter에 PC이름들을 넣어준다.
		listview=(ListView)findViewById(R.id.pcselectLayout);  //xml과 리스트뷰를 연결한다.
		listview.setAdapter(adapter);  //listview에 adapter를 넣는다.
		listview.setChoiceMode(ListView.CHOICE_MODE_SINGLE);  // listview의 모드를 선택한다. CHOICE_MODE_SINGLE은 한번터치를 의미한다.
		
		listview.setOnItemClickListener(new OnItemClickListener() {  //listview를 싱글클릭할때

			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {    //[position은 listview의 몇번재 항목을 터치했는지 나타냄
				// TODO Auto-generated method stub
				try {
					new MagicPacketSend(position);  //클릭된 항목에 대해서 매직패킷클래스를 선언하고 매직패킷을 전송한다.
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		});
		
	}
	

}
