#include <bits/stdc++.h>
using namespace std;

int gn;
// 日期推算器，判断闰年
bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 日期推算器，获取某月天数
int getMonthDays(int year, int month) {
    if (month == 2) {
        return isLeap(year) ? 29 : 28;
    }
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return days[month - 1];
}
int main(){
    while(1){
    	cout<<endl<<"------------------------------------------------------------"<<endl;
    	cout<<"请输入功能：1.整数计算|2.浮点计算|3.日期推算器|4.清屏|5.退出:   ";
    	cin>>gn;
        if (cin.fail()) {
        cin.clear();  // 清除错误标志
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃缓冲区
        continue;
        }
    	while(1){
    		if(gn==1){
		        int b,c;
	            char d;
            	cout<<endl<<"----------"<<endl;
	            cout<<"请输入：数字 数字 运算符  "; 
	            while(1){ 
		            cin>>b>>c>>d;
		            if(d=='+'){cout<<""<<endl;cout<<"结果："<<b+c<<endl;}
	                if(d=='-'){cout<<""<<endl;cout<<"结果："<<b-c<<endl;}
		            if(d=='*'){cout<<""<<endl;cout<<"结果："<<b*c<<endl;}
		            if(d=='/'){cout<<""<<endl;cout<<"结果："<<b/c<<endl;}
		            if(d!='+'&&d!='-'&&d!='*'&&d!='/'){
                        cout<<"输入的是非法字符，已自动跳转到初始菜单"<<endl;
                        break;
                    }
		        }
		    } 
           // ==============================================
		    if(gn==2){
	        	double e,f;
	        	char g;
	            cout<<endl<<"----------"<<endl;
		        cout<<"请输入：数字 数字 运算符  "; 
		        while(1){
		            cin>>e>>f>>g;
		            if(g=='+'){cout<<""<<endl;/**/cout<<fixed<<setprecision(20)<<"结果："<<e+f<<endl;}
	    	        if(g=='-'){cout<<""<<endl;/**/cout<<fixed<<setprecision(20)<<"结果："<<e-f<<endl;}
	    	        if(g=='*'){cout<<""<<endl;/**/cout<<fixed<<setprecision(20)<<"结果："<<e*f<<endl;}
    		        if(g=='/'){cout<<""<<endl;/**/cout<<fixed<<setprecision(20)<<"结果："<<e/f<<endl;}
					 if(g!='+'&&g!='-'&&g!='*'&&g!='/'){
                        cout<<"输入的是非法字符，已自动跳转到初始菜单"<<endl;
                        break;
                    }
		        }
	        }
           // ==============================================
            if (gn == 3) {
                cout << endl << "----------" << endl;
                cout <<""<<endl;cout<< "请输入：年 月 日 星期 增加天数（输入非数字退出，负数表示减少）" << endl;
                while (true) {
                    int year, month, day, week, addDays;
                    cin >> year >> month >> day >> week >> addDays;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "输入非法，返回主菜单" << endl;
                        break;
                    }
                    // 处理增加/减少天数（addDays 可正可负）
                    while (addDays!= 0) {
                        if (addDays > 0) {
                            day++;
                            week++;
                            if (week > 7) week = 1;
                            if (day > getMonthDays(year, month)) {
                                day = 1;
                                month++;
                                if (month > 12) {
                                    month = 1;
                                    year++;
                                }
                            }
                            addDays--;
                        } else { // addDays < 0
                            day--;
                            week--;
                            if (week < 1) week = 7;
                            if (day < 1) {
                                month--;
                                if (month < 1) {
                                    month = 12;
                                    year--;
                                }
                                day = getMonthDays(year, month);
                            }
                            addDays++;
                        }
                    }
                    cout << year << "年" << month << "月" << day << "日 星期" << week << endl;
                    // 继续循环，等待下一次输入
                }
            }
           // ==============================================
	        if(gn==4){system("cls");}
	        if(gn==5){
			    int p;
			    cout<<"-------------"<<endl;
			    cout<<"是否确定退出？ 1.确定|2.返回主菜单： ";
				cin>>p;
				if(p==1){cout<<"退出成功"<<endl;return 0;}
			    if(p==2){system("cls");break;} 
				if(p!=1&&p!=2){cout<<"输入的是非法运算符,已自动跳转到初始菜单"<<endl;break;}
		    } 
		    break;
		}
	}
	return 0;}