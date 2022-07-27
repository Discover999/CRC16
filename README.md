## CRC的编程实现

<br>

**一、实验内容**

1.设计CRC校验算法（生产多项式为CRC-16：
$$
x16+x15+x2+1
$$
）；

2.运用VC++或者C++的编程环境实现CRC校验；



<br>

**二、实验原理**

**1.  ** **模2除（按位除）**

模2除做法与算术除法类似，但每一位除（减）的结果不影响其它位，即不向上一位借位。所以实际上就是异或。然后再移位移位做下一位的模2减。

步骤如下：

> **a、**用除数对被除数最高几位做模2减，没有借位。

> **b、**除数右移一位，若余数最高位为1，商为1，并对余数做模2减。若余数最高位为0，商为0，除数继续右移一位。

> **c、**一直做到余数的位数小于除数时，该余数就是最终余数。

<br>

**2. ** **循环冗余校验码（CRC）的基本原理**

在K位信息码后再拼接R位的校验码，整个编码长度为N位，因此，这种编码又叫（N，K）码。

对于一个给定的（N，K）码，可以证明存在一个最高次幂为N-K=R的多项式G(x)。

根据G(x)可以生成K位信息的校验码，而G(x)叫做这个CRC码的生成多项式。

校验码的具体生成过程为：

> 假设发送信息用信息多项式C(x)表示，将C(x)左移R位，则可表示成C(x)*2R，这样C(x)的右边就会空出R位，这就是校验码的位置。通过C(x)*2R除以生成多项式G(x)得到的余数就是校验码。

<br>

**3. CRC** **码的生成步骤**

**a、**将x的最高幂次为R的生成多项式G(x)转换成对应的R+1位二进制数。

**b、**将信息码左移R位，相当与对应的信息多项式C(x)*2R

**c、**用生成多项式（二进制数）对信息码做模2除，得到R位的余数。

**d、**将余数拼到信息码左移后空出的位置，得到完整的CRC码。

<br>

**三、实验环境：**

![Visual Studio 2022](https://img.shields.io/badge/IDE-Visual%20Studio%202022-blue)

![C++](https://img.shields.io/badge/Language-C%2B%2B-green)



<br>

**四、实验步骤**

​	举例，设 k 为数据组比特数，待传送报文数据M = ***101001*** （k = 6），CRC则是在数据M后添加 n 位的冗余码后构成 k + n 位完整的CRC发送出去。n 位冗余码需进行模2运算得出，设生成多项式
$$
P(x) = X^3 + X^2 + 1
$$
 , 则除数P = 1101，生成多项式最高位为3，则n = 3 ，因此进行模2运算时需要在数据位后添加n位，即被除数M`= ***101001000***.

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image002.jpg)

经模2运算得余数为**001**，将运算的CRC附到原报文后面即为新发送的报文数据**101001_001**，完整报文数据M``= **101001001**。

利用C++ 程序运算得结果十进制CRC 码：***101001001***，计算无误。

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image004.jpg)

其核心算法即作XOR运算，从高位开始，每次进行一次XOR 的到的值后，去掉最高位加入下一位，每加一次进行一次XOR运算。

第一次XOR运算，得到0111，去掉最高位0，加入下一位0, 得1110 ，这样最高位是1,所以下个商是1；

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image006.jpg)

第二次XOR运算，得0011，去掉最高位0，加入下一位1，得0111 ，因不能满足下一次运算所以下一个商为0，第三次XOR重新计算得0111，去掉最高位0，加入下一位0，得1110进行第四次XOR；

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image008.jpg)![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image010.jpg)

第四次XOR计算得0011，去掉最高位0，加入下一位0，得0110，不能进行模2，下一位商0

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image012.jpg)

第五次XOR同第三次XOR，商0，进行第六次XOR运算，0110去掉最高并加入下一位0，得1100，最后商1除完除数，最后一次XOR后得到0001，最高位的0需消掉，最终得到余数为001. 

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image014.jpg)

在数据传送后如何进行CRC校验？其具体实现是将发送的数据101001加上CRC（001）后，变成101001001，再进行报文传送；在接收端收到发送给过去含有CRC校验的数据后，将其除以除数（即声明的多项式系数）P = 1101，若余数为000，说明数据正确无误；若余数不为0，则说明发送的数据有误。如此即完成CRC的校验。 

即发送端要发送101001，先在101001后加000，变成1111000，再除以1101得到余数001，这个001就是CRC，将001添加到发送的数据后面，变成101001001然后再发送出去。 接收端收到的数据是101001001，将它除以1101，计算得余数为000，就说明收到的数据正确。 因此原始数据后要先扩展出n位以容纳CRC值，n即为约定的生成多项式的最高次幂。

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image016.jpg)

![img](https://raw.githubusercontent.com/Discover999/TyporaPic/master/clip_image018.jpg)