# Exchange
Stock Market Simulator (Not Working yet.....)
![image](https://github.com/user-attachments/assets/3cb0016e-4d5d-4ab7-b5f0-f70b4a399b17)
![image](https://github.com/user-attachments/assets/f024f597-955a-4f18-9105-bc37bd985dc0)
![image](https://github.com/user-attachments/assets/de45be66-1153-4d64-8ac1-955bcd3a34a3)
</br>
# Building on linux for linux
git clone https://github.com/GRATHRRAM/Exchange</br>
cd Exchange</br>
mkdir Build</br>
cp ExchangeData/ Build/ -r</br>
cd Build</br>
cmake ..</br>
make</br>
# Building on linux for windows
git clone https://github.com/GRATHRRAM/Exchange</br>
cd Exchange</br>
mkdir win</br>
</br>
Now Download raylib files from https://github.com/raysan5/raylib/releases/tag/5.0 </br>
file calld raylib-5.0_win64_mingw-w64.zip </br>
And put include and lib directories in win/
</br>
mkdir Build</br>
cp ExchangeData/ Build/ -r</br>
cd Build</br>
cmake .. -DCMAKE_ARGV0="win"</br>
make</br>
