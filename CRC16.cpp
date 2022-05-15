#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<algorithm>
#define MAX 100
using namespace std;

//判断是否是2的幂次方
int is2n(string bin)
{
    int count = 0;
    for (int i = 0; i < bin.size(); i++)
    {
        if (bin[i] == '1')
            count++;
    }
    return count == 1 ? 1 : 0;
}
//求数对应的十六进制符号
char hexNumber(int num)
{
    char hex;
    if (num >= 0 && num <= 9)
        return num + '0';
    else
    {
        switch (num)
        {
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default:
            cout << "error" << endl;
            return '#';
        }
    }
}
//将十进制串转成二进制
string dec2Bin(int dec)
{
    string bin = "";
    while (dec)
    {
        int remainer = dec % 2;
        bin.insert(0, to_string(remainer));
        dec = dec / 2;
    }
    return bin;
}

//二进制串转十六进制
string bin2hex(string bin)
{
    string hex = "";//十六进制串

    //前面补0
    int cnt = 0;//补0的个数
    if (bin.size() % 4 != 0)
    {
        cnt = 4 - (bin.size() % 4);
    }

    for (int i = 0; i < cnt; i++)
        bin.insert(0, "0");

    //二进制转十六进制
    for (int i = 0; i < bin.size(); i += 4)
    {
        int sum = 0;

        for (int j = 0; j < 4; j++)
        {
            sum += (bin[i + j] - '0') * pow(2, 3 - j);//注意求的时候从右往左，因此用3-j
            //cout<<i+j<<"\t"<<(bin[i+j]-'0')*pow(2,3-j)<<endl;
        }
        hex.push_back(hexNumber(sum));
    }
    return hex;
}

//两个二进制串做异或
string XOR(string a, string b)
{
    //逆序让两串最低位对齐
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    int i;
    string res;
    for (i = 0; i < a.size() && i < b.size(); i++)
    {
        if (a[i] == b[i])
            res.insert(res.begin(), '0');
        else
            res.insert(res.begin(), '1');
    }
    //剩余的串补上
    if (i < a.size())
    {
        for (; i < a.size(); i++)
            res.insert(res.begin(), a[i]);
    }
    if (i < b.size())
    {
        for (; i < b.size(); i++)
            res.insert(res.begin(), b[i]);
    }
    return res;
}
//CRC模2除,返回余数
string division(string data, string Gx)
{
    string remainder;//余数
    string temp = data.substr(0, Gx.size());
    remainder = XOR(temp, Gx);

    for (int i = Gx.size(); i < data.size(); i++)
    {
        remainder.erase(0, 1);
        remainder.push_back(data[i]);

        //余数第一位是1，则商1,计算下一次余数
        //余数第一位是0，则下一次余数不变
        if (*remainder.begin() == '1')
        {
            remainder = XOR(remainder, Gx);
        }
    }
    //cout<<"remainder : "<<remainder<<endl;

    return remainder;
}

//CRC编码
string CRC(string data, string Gx)
{
    string code;//CRC校验码

    //数据左移
    data.insert(data.end(), Gx.size() - 1, '0');

    /*模2除法*/
    string remainder = division(data, Gx);

    /*data和余数模2加*/
    code = XOR(data, remainder);
    //cout<<"code : "<<code<<endl;

    return code;
}

//检错
int Detect(string code, string Gx)
{
    string remainder = division(code, Gx);

    //余数为0，结果正确
    if (remainder.find('1') == string::npos)
    {
        cout << endl << "****** 校验无误 ******" << endl;
        return 1;
    }
    else
    {
        cout << endl << "****** 校验出错! ******" << endl;
        return 0;
    }
}

int main()
{
    string data;
    string Gx;
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "请选择（ 1:CRC生成 2:CRC校验 0:退出 ）：" << endl;
    int choice;
    while (cin >> choice)
    {
        string res;
        switch (choice)
        {
        case 1:
            cout << "请输入要发送的数据：" << endl;
            cin >> data;
            cout << "请输入生成多项式的系数：" << endl;
            cin >> Gx;
            res = CRC(data, Gx);
            cout << "CRC码(十进制)：" << res << endl;
            cout << "CRC码(十六进制)：" << bin2hex(res) << endl;
            break;
        case 2:
            cout << "请输入收到的CRC码：" << endl;
            cin >> data;
            cout << "请输入生成多项式的系数：" << endl;
            cin >> Gx;
            Detect(data, Gx);
            break;
        case 0:
            return 0;
        default:
            cout << "选择错误" << endl;
        }
        cout << "-----------------------------------------------------------------------" << endl;
        cout << "请选择（ 1:CRC生成 2:CRC校验 0:退出 ）：" << endl;
    }
    return 0;
}


