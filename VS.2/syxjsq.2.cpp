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

// ========== 历史记录文件读写 ==========
void saveHistory(const vector<string>& expr, const vector<string>& res) {
    ofstream out("history.txt");
    if (!out) return;
    for (size_t i = 0; i < expr.size(); ++i) {
        out << expr[i] << "\t" << res[i] << "\n";
    }
    out.close();
}

void loadHistory(vector<string>& expr, vector<string>& res) {
    ifstream in("history.txt");
    if (!in) return;
    expr.clear();
    res.clear();
    string line;
    while (getline(in, line)) {
        size_t pos = line.find('\t');
        if (pos != string::npos) {
            string e = line.substr(0, pos);
            string r = line.substr(pos + 1);
            if (expr.size() < 100) {
                expr.push_back(e);
                res.push_back(r);
            }
        }
    }
    in.close();
}

// ========== 特殊指令检查 ==========
int checkSpecialCommand(const string& input) {
    if (input == "$") return 1;  // 清屏
    if (input == "#") return 2;  // 返回主菜单
    return 0; // 正常输入
}
// =================================

int main(){
    vector<string> historyExpr;
    vector<string> historyResult;
    loadHistory(historyExpr, historyResult);

    while(1){
        cout<<endl<<"------------------------------------------------------------"<<endl;
        cout<<"请输入功能：1.整数计算|2.浮点计算|3.日期推算器|4.清屏|5.退出|6.历史记录:   ";
        cin>>gn;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        while(1){
            if(gn==1){
                cout<<endl<<"----------"<<endl;
                cout<<"请输入：数字 数字 运算符（输入 $=清屏, #=返回主菜单）  "; 
                while(1){ 
                    string input;
                    cin >> input;
                    
                    // 先检查特殊指令
                    int cmd = checkSpecialCommand(input);
                    if (cmd == 1) { system("cls"); continue; }
                    if (cmd == 2) { break; }
                    
                    // 正常计算：把input转成第一个数字
                    stringstream ss(input);
                    int b;
                    ss >> b;
                    if (ss.fail()) {
                        cout<<"输入格式错误，请重新输入：数字 数字 运算符"<<endl;
                        continue;
                    }
                    int c;
                    char d;
                    cin >> c >> d;
                    
                    // ===== 修改：检查运算符是否合法，排除 $ 和 # =====
                    if(d != '+' && d != '-' && d != '*' && d != '/') {
                        // 检查 d 是否是 $ 或 #（防止误判）
                        if(d == '$' || d == '#') {
                            // 这两个在运算符位置输入，说明用户想用特殊功能但放错位置了
                            cout<<"提示：清屏或返回主菜单请单独输入 $ 或 #，不用写其他数字"<<endl;
                            continue;
                        }
                        cout<<"输入的是非法字符，已自动跳转到初始菜单"<<endl;
                        break;
                    }
                    
                    // 合法运算符，执行计算
                    if(d=='+'){
                        cout<<""<<endl;
                        int res = b + c;
                        cout<<"结果："<<res<<endl;
                        historyExpr.push_back(to_string(b) + "+" + to_string(c));
                        historyResult.push_back(to_string(res));
                        if(historyExpr.size() > 100) {
                            historyExpr.erase(historyExpr.begin());
                            historyResult.erase(historyResult.begin());
                        }
                        saveHistory(historyExpr, historyResult);
                    }
                    else if(d=='-'){
                        cout<<""<<endl;
                        int res = b - c;
                        cout<<"结果："<<res<<endl;
                        historyExpr.push_back(to_string(b) + "-" + to_string(c));
                        historyResult.push_back(to_string(res));
                        if(historyExpr.size() > 100) {
                            historyExpr.erase(historyExpr.begin());
                            historyResult.erase(historyResult.begin());
                        }
                        saveHistory(historyExpr, historyResult);
                    }
                    else if(d=='*'){
                        cout<<""<<endl;
                        int res = b * c;
                        cout<<"结果："<<res<<endl;
                        historyExpr.push_back(to_string(b) + "*" + to_string(c));
                        historyResult.push_back(to_string(res));
                        if(historyExpr.size() > 100) {
                            historyExpr.erase(historyExpr.begin());
                            historyResult.erase(historyResult.begin());
                        }
                        saveHistory(historyExpr, historyResult);
                    }
                    else if(d=='/'){
                        cout<<""<<endl;
                        if(c == 0) {
                            cout<<"除数不能为0！"<<endl;
                        } else {
                            int res = b / c;
                            cout<<"结果："<<res<<endl;
                            historyExpr.push_back(to_string(b) + "/" + to_string(c));
                            historyResult.push_back(to_string(res));
                            if(historyExpr.size() > 100) {
                                historyExpr.erase(historyExpr.begin());
                                historyResult.erase(historyResult.begin());
                            }
                            saveHistory(historyExpr, historyResult);
                        }
                    }
                }
                // 如果是因为#跳出来的，break到外层，重新显示主菜单
                break;
            } 
            // ==============================================
            if(gn==2){
                cout<<endl<<"----------"<<endl;
                cout<<"请输入：数字 数字 运算符（输入 $=清屏, #=返回主菜单）  "; 
                while(1){
                    string input;
                    cin >> input;
                    
                    int cmd = checkSpecialCommand(input);
                    if (cmd == 1) { system("cls"); continue; }
                    if (cmd == 2) { break; }
                    
                    stringstream ss(input);
                    double e;
                    ss >> e;
                    if (ss.fail()) {
                        cout<<"输入格式错误，请重新输入：数字 数字 运算符"<<endl;
                        continue;
                    }
                    double f;
                    char g;
                    cin >> f >> g;
                    
                    // ===== 修改：检查运算符是否合法，排除 $ 和 # =====
                    if(g != '+' && g != '-' && g != '*' && g != '/') {
                        if(g == '$' || g == '#') {
                            cout<<"提示：清屏或返回主菜单请单独输入 $ 或 #，不用写其他数字"<<endl;
                            continue;
                        }
                        cout<<"输入的是非法字符，已自动跳转到初始菜单"<<endl;
                        break;
                    }
                    
                    if(g=='+'){
                        cout<<""<<endl;
                        double res = e + f;
                        cout<<fixed<<setprecision(20)<<"结果："<<res<<endl;
                        stringstream ss2;
                        ss2 << fixed << setprecision(6) << e << "+" << f;
                        historyExpr.push_back(ss2.str());
                        stringstream sr;
                        sr << fixed << setprecision(20) << res;
                        historyResult.push_back(sr.str());
                        if(historyExpr.size() > 100) {
                            historyExpr.erase(historyExpr.begin());
                            historyResult.erase(historyResult.begin());
                        }
                        saveHistory(historyExpr, historyResult);
                    }
                    else if(g=='-'){
                        cout<<""<<endl;
                        double res = e - f;
                        cout<<fixed<<setprecision(20)<<"结果："<<res<<endl;
                        stringstream ss2;
                        ss2 << fixed << setprecision(6) << e << "-" << f;
                        historyExpr.push_back(ss2.str());
                        stringstream sr;
                        sr << fixed << setprecision(20) << res;
                        historyResult.push_back(sr.str());
                        if(historyExpr.size() > 100) {
                            historyExpr.erase(historyExpr.begin());
                            historyResult.erase(historyResult.begin());
                        }
                        saveHistory(historyExpr, historyResult);
                    }
                    else if(g=='*'){
                        cout<<""<<endl;
                        double res = e * f;
                        cout<<fixed<<setprecision(20)<<"结果："<<res<<endl;
                        stringstream ss2;
                        ss2 << fixed << setprecision(6) << e << "*" << f;
                        historyExpr.push_back(ss2.str());
                        stringstream sr;
                        sr << fixed << setprecision(20) << res;
                        historyResult.push_back(sr.str());
                        if(historyExpr.size() > 100) {
                            historyExpr.erase(historyExpr.begin());
                            historyResult.erase(historyResult.begin());
                        }
                        saveHistory(historyExpr, historyResult);
                    }
                    else if(g=='/'){
                        cout<<""<<endl;
                        if(f == 0) {
                            cout<<"除数不能为0！"<<endl;
                        } else {
                            double res = e / f;
                            cout<<fixed<<setprecision(20)<<"结果："<<res<<endl;
                            stringstream ss2;
                            ss2 << fixed << setprecision(6) << e << "/" << f;
                            historyExpr.push_back(ss2.str());
                            stringstream sr;
                            sr << fixed << setprecision(20) << res;
                            historyResult.push_back(sr.str());
                            if(historyExpr.size() > 100) {
                                historyExpr.erase(historyExpr.begin());
                                historyResult.erase(historyResult.begin());
                            }
                            saveHistory(historyExpr, historyResult);
                        }
                    }
                }
                break;
            }
            // ==============================================
            if (gn == 3) {
                cout << endl << "----------" << endl;
                cout << "请输入：年 月 日 星期 增加天数（输入 $=清屏, #=返回主菜单）" << endl;
                while (true) {
                    string input;
                    cin >> input;
                    
                    int cmd = checkSpecialCommand(input);
                    if (cmd == 1) { system("cls"); continue; }
                    if (cmd == 2) { break; }
                    
                    stringstream ss(input);
                    int year, month, day, week, addDays;
                    ss >> year >> month >> day >> week >> addDays;
                    
                    // 检查日期推算输入是否合法（包括 $ 和 # 已被上面拦截）
                    if (ss.fail()) {
                        // 检查是不是不小心输了 $ 或 # 但没被拦截（防御性）
                        if (input == "$" || input == "#") {
                            // 已经被上面的 checkSpecialCommand 处理了，这里不会执行到
                            continue;
                        }
                        cout << "输入格式错误，请重新输入：年 月 日 星期 增加天数" << endl;
                        continue;
                    }
                    
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
                        } else {
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
                }
                break;
            }
            // ==============================================
            if(gn==4){
                system("cls");
            }
            if(gn==5){
                int p;
                cout<<"-------------"<<endl;
                cout<<"是否确定退出？ 1.确定|2.返回主菜单： ";
                cin>>p;
                if(p==1){
                    saveHistory(historyExpr, historyResult);
                    cout<<"退出成功"<<endl;
                    return 0;
                }
                if(p==2){system("cls");break;} 
                if(p!=1&&p!=2){
                    // 检查是否输入了 $ 或 #
                    if(p == '$' || p == '#') {
                        cout<<"提示：清屏或返回主菜单请单独输入，但退出确认只能输 1 或 2"<<endl;
                    } else {
                        cout<<"输入的是非法运算符,已自动跳转到初始菜单"<<endl;
                    }
                    break;
                }
            }
            // ========== 历史记录 ==========
            if(gn==6){
                while(1){
                    cout<<"\n-------- 历史记录（输入 $=清屏, #=返回主菜单） --------"<<endl;
                    cout<<"1. 查看所有记录"<<endl;
                    cout<<"2. 清空所有记录"<<endl;
                    cout<<"3. 返回主菜单"<<endl;
                    cout<<"请选择: ";
                    string input;
                    cin >> input;
                    
                    int cmd = checkSpecialCommand(input);
                    if (cmd == 1) { system("cls"); continue; }
                    if (cmd == 2) { break; }
                    
                    stringstream ss(input);
                    int choice;
                    ss >> choice;
                    if (ss.fail()) {
                        // 检查是否输入了 $ 或 #（防御性）
                        if (input == "$" || input == "#") {
                            // 已经被 checkSpecialCommand 处理了
                            continue;
                        }
                        cout<<"输入无效，请输入数字 1/2/3"<<endl;
                        continue;
                    }
                    
                    if(choice == 1){
                        if(historyExpr.empty()){
                            cout<<"暂无历史记录。"<<endl;
                        } else {
                            cout<<"\n---- 记录（最新在前） ----"<<endl;
                            for(int i = historyExpr.size() - 1; i >= 0; i--){
                                cout << "[" << i << "] " << historyExpr[i] << " = " << historyResult[i] << endl;
                            }
                        }
                    }
                    else if(choice == 2){
                        historyExpr.clear();
                        historyResult.clear();
                        saveHistory(historyExpr, historyResult);
                        cout<<"历史记录已清空。"<<endl;
                    }
                    else if(choice == 3){
                        break;
                    }
                    else {
                        cout<<"无效选择，请输入 1/2/3"<<endl;
                    }
                }
                break;
            }
            // =======================================
            break;
        }
    }
    saveHistory(historyExpr, historyResult);
    return 0;
}