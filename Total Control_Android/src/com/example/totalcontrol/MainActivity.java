package com.example.totalcontrol;



import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
public class MainActivity extends Activity implements OnClickListener {

	public Button WolButton;  //wol버튼 동작을 정의한 클래스
	public Button launchButton;  //서버열때 사용하는 Launch버튼의 동작을 정의한 클래스
	public EditText editText;  //포트번호 입력하는 텍스트 에디터
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);  //xml이랑 연동
        
        launchButton =(Button) findViewById(R.id.LaunchButton);  //Lauch 버튼 생성 
        launchButton.setOnClickListener(this);  //버튼클릭할때 일어날 동작과 연결해줌
        WolButton=(Button) findViewById(R.id.WOLButton);  //wol 버튼 생성
        WolButton.setOnClickListener(this);  //버튼 클릭때 일어날 동작과 연결
        
        editText=(EditText)findViewById(R.id.PortEdit);  //덱스트에디터(포트번호받을) 생성
        Log.i("메인 엑티비티", "메인엑티비티 초기화 완료");
    }

	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub
		
		switch(v.getId())
		{
		case R.id.LaunchButton:   //Launch버튼 누를때 동작
			LaunchButton lb=new LaunchButton(this);  //Launch버튼 클릭시에 동작을 정의한 클래스를 생성
			if(lb.checkInputPort()==true)  //checkInputPort메소드는 포트입력이 되었는지 or 서버생성이 성공하였는지 확인하는 메소드
			{
				Intent nextActivity=lb.getNextActivity();  //다음  페이지로 넘어가기 위한 코드
				startActivity(nextActivity);  //액티비티 시작 메소드
				break;
			}
			break;
		case R.id.WOLButton:  //wol버튼 누를때 동작
			Intent nextActivity=new Intent(getApplicationContext(),
					PcSelect.class);  //wol버튼을 누르면 PcSelect액티비티로 넘어간다.
			startActivity(nextActivity);  //액티비티 시작 메소드
			break;
		}
	}
	

}
